#pragma once
#include "MixquicUnifiedData.h"

void UnifiedTranslate(Placement& p,const glm::vec3& d)
{
    p.matrix=glm::translate(glm::mat4(1),d)*p.matrix;
    p.bounds=WorldBounds(*p.model,p.matrix);
}

bool UnifiedOverlap3(const Bounds& a,const Bounds& b)
{
    return OverlapXZ(a,b)&&a.min.y<b.max.y-.00001f&&a.max.y>b.min.y+.00001f;
}

float UnifiedSupportPoint(float x,float z,const std::vector<Surface>& surfaces,const Model& paving)
{
    float y=0;
    for(const auto& s:surfaces)if(x>=s.center.x-s.size.x*.5f-.00001f&&x<=s.center.x+s.size.x*.5f+.00001f
        &&z>=s.center.z-s.size.z*.5f-.00001f&&z<=s.center.z+s.size.z*.5f+.00001f)y=(std::max)(y,s.center.y+s.size.y*.5f);
    return (std::max)(y,TopSurfaceY(paving,x,z));
}

bool UnifiedCheckTrajectory(const std::vector<Placement>& obstacles)
{
    // An all-time swept AABB, not only the 401 animation samples.
    const Bounds sweep={glm::vec3(3.163150f,1.418466f,1.163150f),glm::vec3(4.836850f,1.874101f,2.836850f)};
    // The generated bound is deliberately rounded OUTWARDS from the model radius.
    for(const auto& o:obstacles)if(UnifiedOverlap3(sweep,o.bounds)){
        std::cerr<<"ERROR: OPCION_A_NUEVA_COLISION. Detener antes de aprobar."<<std::endl;return false;
    }
    if(sweep.min.y<=.1f)return false;
    std::cout<<"LUCIERNAGA_CONTINUA: ancla=(4,1.65,2); envolvente para todo t separada de arquitectura, tumbas, adornos y terreno."<<std::endl;
    return true;
}

bool PrepareUnifiedScene(Placement& churchV1,Placement& churchV2,Placement& church,Placement& ground,Placement& altar,
    Placement& perchedCrow,std::vector<Placement>& graves,std::vector<Placement>& groundProps,
    std::vector<AttachedProp>& attached,std::vector<Placement>& allProps,std::vector<Surface>& surfaces,
    Model& floorModel,Model& pavingModel,Placement& paving,Model& fogata,Model& vela,Model& farol,Model& veladora,bool verbose)
{
    if(graves.size()!=77||groundProps.size()!=297||attached.size()!=99||allProps.size()!=396)return false;
    for(size_t i=0;i<77;++i)if(glm::length(graves[i].bounds.min-unifiedOriginalGraves[i].min)>.002f
        ||glm::length(graves[i].bounds.max-unifiedOriginalGraves[i].max)>.002f)return false;
    for(size_t i=0;i<396;++i)if(glm::length(allProps[i].bounds.min-unifiedOriginalProps[i].min)>.002f
        ||glm::length(allProps[i].bounds.max-unifiedOriginalProps[i].max)>.002f){
        std::cerr<<"ERROR: inventario distinto de main en D"<<i+1<<std::endl;return false;}
    if(useExpandedTerrain){
        UnifiedTranslate(churchV1,{0,0,-1});UnifiedTranslate(churchV2,{0,0,-1});
        church=useIglesiaV2?churchV2:churchV1;
        UnifiedTranslate(altar,{0,0,-6.25f});UnifiedTranslate(graves[76],{0,0,-6.25f});
        ground=Grounded(floorModel,{0,0,0},{10,1,12.8f});
        posFogata.z-=6.25f;posVela.z-=1;posFarol.z+=11;posVeladora.z-=6.25f;
        UnifiedTranslate(perchedCrow,{0,0,11});
    }
    const glm::vec3* offsets=useExpandedTerrain?unifiedExpandedOffsets:unifiedBaseOffsets;
    for(size_t i=0;i<groundProps.size();++i)UnifiedTranslate(groundProps[i],offsets[i]);
    for(size_t i=0;i<attached.size();++i)UnifiedTranslate(attached[i].item,offsets[groundProps.size()+i]);
    allProps=groundProps;for(const auto& a:attached)allProps.push_back(a.item);
    std::vector<Surface> retained;
    for(auto s:surfaces)if(s.size.y>.05f){
        if(useExpandedTerrain){if(s.size.y>.6f)s.center.z+=11;else if(s.size.y>.09f&&s.size.y<.11f)s.center.z-=6.25f;}
        retained.push_back(s);
    }
    surfaces.swap(retained);if(surfaces.size()!=79)return false;
    paving={&pavingModel,glm::mat4(1),WorldBounds(pavingModel,glm::mat4(1))};
    const size_t expectedTriangles=useExpandedTerrain?1982u:2084u;
    if(!pavingModel.IsLoaded()||pavingModel.Meshes().size()!=1||pavingModel.MaterialCount()!=1||pavingModel.TriangleCount()!=expectedTriangles)return false;
    const Bounds* expectedProps=useExpandedTerrain?unifiedExpandedProps:unifiedBaseProps;
    for(size_t i=0;i<allProps.size();++i){
        const Bounds& b=allProps[i].bounds;
        if(glm::length(b.min-expectedProps[i].min)>.003f||glm::length(b.max-expectedProps[i].max)>.003f)return false;
        if(b.min.x<-(useExpandedTerrain?25.f:17.f)||b.max.x>(useExpandedTerrain?25.f:17.f)
            ||b.min.z<-(useExpandedTerrain?32.f:21.f)||b.max.z>(useExpandedTerrain?32.f:21.f))return false;
        if(i<groundProps.size()){
            const float offset=groundProps[i].model->BoundsMax().y-groundProps[i].model->BoundsMin().y<.01f?.002f:0;
            for(int x=0;x<3;++x)for(int z=0;z<3;++z){
                const float px=b.min.x+(b.max.x-b.min.x)*x*.5f,pz=b.min.z+(b.max.z-b.min.z)*z*.5f;
                const float y=UnifiedSupportPoint(px,pz,surfaces,pavingModel);
                if(fabs(b.min.y-y-offset)>.0025f){std::cerr<<"ERROR: apoyo unificado D"<<i+1<<" actual="<<b.min.y<<" soporte="<<y<<std::endl;return false;}
            }
        }
        if(verbose)std::cout<<"UNIFIED_PROP "<<i<<" "<<b.min.x<<" "<<b.min.y<<" "<<b.min.z<<" "<<b.max.x<<" "<<b.max.y<<" "<<b.max.z<<std::endl;
    }
    for(size_t i=0;i<graves.size();++i){
        if(OverlapXZ(graves[i].bounds,church.bounds)||OverlapXZ(graves[i].bounds,altar.bounds))return false;
        for(size_t j=i+1;j<graves.size();++j)if(OverlapXZ(graves[i].bounds,graves[j].bounds))return false;
        if(verbose){const Bounds& b=graves[i].bounds;std::cout<<"UNIFIED_GRAVE "<<i<<" "<<b.min.x<<" "<<b.min.y<<" "<<b.min.z<<" "<<b.max.x<<" "<<b.max.y<<" "<<b.max.z<<std::endl;}
    }
    if(!ValidateAttached(attached,graves,church,altar))return false;
    // Restore conservative separation for the ground decorations added by the team.
    for(size_t i=69;i<groundProps.size();++i){
        for(const auto& g:graves)if(OverlapXZ(groundProps[i].bounds,g.bounds))return false;
        for(size_t j=0;j<groundProps.size();++j)if(i!=j&&OverlapXZ(groundProps[i].bounds,groundProps[j].bounds))return false;
    }
    std::vector<Placement> staticItems={Grounded(fogata,posFogata,glm::vec3(ESC_FOGATA)),Grounded(vela,posVela,glm::vec3(ESC_VELA)),
        Grounded(farol,posFarol,glm::vec3(ESC_FAROL)),Grounded(veladora,posVeladora,glm::vec3(ESC_VELADORA)),perchedCrow};
    std::vector<Placement> architecture={church,altar};architecture.insert(architecture.end(),graves.begin(),graves.end());
    architecture.insert(architecture.end(),allProps.begin(),allProps.end());architecture.insert(architecture.end(),staticItems.begin(),staticItems.end());
    if(!UnifiedCheckTrajectory(architecture))return false;
    std::vector<Bounds> walkObstacles={church.bounds,altar.bounds};
    for(const auto& g:graves)walkObstacles.push_back(g.bounds);
    for(const auto& d:allProps)if(d.model->BoundsMax().y-d.model->BoundsMin().y>=.01f)walkObstacles.push_back(d.bounds);
    for(const auto& d:staticItems)walkObstacles.push_back(d.bounds);
    for(const auto& s:surfaces)if(s.size.y>.15f)walkObstacles.push_back({s.center-s.size*.5f,s.center+s.size*.5f});
    const UnifiedSegment* segments=useExpandedTerrain?unifiedExpandedSegments:unifiedBaseSegments;
    const size_t count=useExpandedTerrain?sizeof(unifiedExpandedSegments)/sizeof(unifiedExpandedSegments[0]):sizeof(unifiedBaseSegments)/sizeof(unifiedBaseSegments[0]);size_t samples=0;
    for(size_t i=0;i<count;++i){
        const auto& s=segments[i];const int steps=(std::max)(1,int(ceil(glm::length(s.b-s.a)/.05f)));
        for(int j=0;j<=steps;++j){glm::vec2 p=glm::mix(s.a,s.b,float(j)/steps);Bounds body={glm::vec3(p.x-.35f,0,p.y-.35f),glm::vec3(p.x+.35f,EYE_HEIGHT,p.y+.35f)};
            for(const auto& o:walkObstacles)if(OverlapXZ(body,o)){std::cerr<<"ERROR: ruta unificada "<<i<<" bloqueada en "<<p.x<<","<<p.y<<std::endl;return false;}++samples;
        }
    }
    const float hx=useExpandedTerrain?25.f:17.f,hz=useExpandedTerrain?32.f:21.f;
    if(glm::length(ground.bounds.min-glm::vec3(-hx,0,-hz))>.002f||glm::length(ground.bounds.max-glm::vec3(hx,0,hz))>.002f)return false;
    for(const Mesh& m:pavingModel.Meshes())for(const Vertex& v:m.vertices)if(!std::isfinite(v.TexCoords.x)||!std::isfinite(v.TexCoords.y)||fabs(glm::length(v.Normal)-1)>.02f)return false;
    std::cout<<"UNIFICADA: terreno="<<(useExpandedTerrain?"50x64":"34x42")<<"; 77 tumbas; 396 decoraciones (297 suelo,99 tapas); categorias A=24 B=32 C=21."<<std::endl;
    std::cout<<"NAVEGACION_UNIFICADA: "<<count<<" tramos; "<<samples<<" muestras <=0.05; 77 destinos accesibles, ceremonial con observacion compartida; radio de prueba=0.35. No es colision fisica."<<std::endl;
    return true;
}
