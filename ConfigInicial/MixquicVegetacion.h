#pragma once

#include "MixquicVegetacionDatos.h"

namespace vegetacion4f
{
struct Dibujo
{
    unsigned llamadas=0;
    unsigned triangulos=0;
};

class Vegetacion
{
public:
    bool Cargar(const Model& pavimento, const std::vector<Bounds>& protegidos)
    {
        malla=std::make_unique<Model>("Models/Vegetacion_Mixquic/vegetacion_mixquic.obj");
        const auto& prototipos=malla->Meshes();
        const std::array<size_t,4> esperado={{1032,1376,360,66}};
        if(prototipos.size()!=esperado.size() || malla->MaterialCount()!=1) return Error("grupos OBJ o material");
        std::array<float,4> radios={}, alturasBase={};
        GLuint atlas=0;
        for(size_t i=0;i<prototipos.size();++i)
        {
            const Mesh& mesh=prototipos[i];
            if(mesh.indices.size()!=esperado[i]*3 || mesh.textures.size()!=1 || !glIsTexture(mesh.textures[0].id))
                return Error("geometria o textura");
            if(atlas && atlas!=mesh.textures[0].id) return Error("se esperaba un solo atlas");
            atlas=mesh.textures[0].id;
            for(const auto& v:mesh.vertices)
            {
                radios[i]=glm::max(radios[i],glm::length(glm::vec2(v.Position.x,v.Position.z)));
                alturasBase[i]=glm::min(alturasBase[i],v.Position.y);
                if(std::abs(glm::length(v.Normal)-1.f)>.005f || !std::isfinite(v.TexCoords.x) ||
                   !std::isfinite(v.TexCoords.y)) return Error("normales o UV");
            }
        }
        GLint anterior=0, ancho=0, alto=0;
        glGetIntegerv(GL_TEXTURE_BINDING_2D,&anterior);
        glBindTexture(GL_TEXTURE_2D,atlas);
        glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_WIDTH,&ancho);
        glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_HEIGHT,&alto);
        glBindTexture(GL_TEXTURE_2D,static_cast<GLuint>(anterior));
        if(ancho!=256 || alto!=256) return Error("resolucion del atlas");

        std::vector<Bounds> baldosas;
        for(const auto& mesh:pavimento.Meshes())
            for(size_t i=0;i<mesh.indices.size();i+=3)
            {
                const auto a=mesh.vertices[mesh.indices[i]].Position;
                const auto b=mesh.vertices[mesh.indices[i+1]].Position;
                const auto c=mesh.vertices[mesh.indices[i+2]].Position;
                baldosas.push_back({glm::min(a,glm::min(b,c)),glm::max(a,glm::max(b,c))});
            }
        std::array<unsigned,4> cuenta={};
        for(const auto& semilla:distribucion)
        {
            const glm::vec2 centro(semilla.x,semilla.z);
            const float radio=radios[semilla.tipo]*semilla.escala;
            if(std::abs(centro.x)+radio>23.92f || centro.y-radio < -30.91f ||
               centro.y+radio>29.76f || std::abs(centro.x)-radio<6.15f ||
               (centro.y < -18.f && std::abs(centro.x)-radio<8.40f))
                return Error("perimetro o corredor visual",&semilla);
            for(const auto& b:protegidos)
                if(Distancia(centro,b)<radio+.14f) return Error("tumba, adorno, actor o arquitectura",&semilla);
            for(const auto& b:baldosas)
                if(Distancia(centro,b)<radio+.20f) return Error("pavimento",&semilla);

            auto modelo=glm::translate(glm::mat4(1),{centro.x,-alturasBase[semilla.tipo]*semilla.escala,centro.y});
            modelo=glm::rotate(modelo,glm::radians(semilla.giro),{0,1,0});
            modelo=glm::scale(modelo,glm::vec3(semilla.escala));
            Bounds caja{glm::vec3(1e6f),glm::vec3(-1e6f)};
            for(const auto& v:prototipos[semilla.tipo].vertices)
            {
                const auto p=glm::vec3(modelo*glm::vec4(v.Position,1));
                caja.min=glm::min(caja.min,p);
                caja.max=glm::max(caja.max,p);
            }
            plantas.push_back({semilla.tipo,modelo,caja});
            if(semilla.tipo<2)
            {
                const float anchoTronco=(semilla.tipo==0?.20f:.27f)*semilla.escala;
                troncos.push_back({{centro.x-anchoTronco,0,centro.y-anchoTronco},
                    {centro.x+anchoTronco,2.1f,centro.y+anchoTronco}});
            }
            ++cuenta[semilla.tipo];
            maximo.triangulos+=static_cast<unsigned>(esperado[semilla.tipo]);
            ++maximo.llamadas;
        }
        std::cout<<"VEGETACION INVENTARIO: cipreses="<<cuenta[0]<<" fresnos="<<cuenta[1]
            <<" arbustos="<<cuenta[2]<<" macollos="<<cuenta[3]
            <<" atlas="<<ancho<<"x"<<alto<<" llamadas_max="<<maximo.llamadas
            <<" triangulos_max="<<maximo.triangulos<<std::endl;
        return true;
    }

    void AgregarPerimetro(std::vector<Bounds>& obstaculos) const
    {
        for(const auto& planta:plantas) obstaculos.push_back(planta.caja);
    }

    void AgregarNavegacion(navegacion4e::Navegacion& navegacion) const
    {
        for(const auto& tronco:troncos) navegacion.Agregar(tronco);
    }

    bool ValidarTroncos(const navegacion4e::Navegacion& nav,const MixquicPerimeter& perimetro) const
    {
        for(const auto& tronco:troncos)
        {
            const glm::vec3 p=(tronco.min+tronco.max)*.5f;
            const glm::vec2 centro(p.x,p.z);
            if(nav.Libre(centro,&perimetro)) return Error("tronco sin colision");
            bool probado=false;
            for(const glm::vec2 eje: {glm::vec2(1,0),glm::vec2(-1,0),glm::vec2(0,1),glm::vec2(0,-1)})
            {
                const auto inicio=centro+eje*1.55f;
                if(!nav.Libre(inicio,&perimetro)) continue;
                const auto final=nav.Desplazar(inicio,centro-eje*.9f,&perimetro);
                const float recorrido=glm::dot(final-centro,eje);
                const float limite=(tronco.max.x-tronco.min.x)*.5f+navegacion4e::Navegacion::radio;
                if(recorrido>=limite-.001f && recorrido<=limite+.052f) probado=true;
            }
            if(!probado) return Error("acercamiento al tronco sin prueba valida");
        }
        std::cout<<"VEGETACION COLISION: troncos="<<troncos.size()<<" paso_largo_bloqueado=1 arbustos_y_hierbas_transitables=1"<<std::endl;
        return true;
    }

    Dibujo Dibujar(const Shader& shader,GLint modelo,const glm::mat4& clip)
    {
        const glm::mat4 row=glm::transpose(clip);
        const glm::vec4 planes[]={row[3]+row[0],row[3]-row[0],row[3]+row[1],row[3]-row[1],row[3]+row[2],row[3]-row[2]};
        Dibujo conteo;
        for(const auto& planta:plantas)
        {
            if(!Visible(planta.caja,planes)) continue;
            glUniformMatrix4fv(modelo,1,GL_FALSE,glm::value_ptr(planta.modelo));
            malla->DrawMesh(planta.tipo,shader);
            ++conteo.llamadas;
            conteo.triangulos+=static_cast<unsigned>(malla->Meshes()[planta.tipo].indices.size()/3);
        }
        return conteo;
    }

private:
    struct Planta { size_t tipo; glm::mat4 modelo; Bounds caja; };
    std::unique_ptr<Model> malla;
    std::vector<Planta> plantas;
    std::vector<Bounds> troncos;
    Dibujo maximo;

    static float Distancia(glm::vec2 p,const Bounds& b)
    {
        return glm::length(p-glm::clamp(p,glm::vec2(b.min.x,b.min.z),glm::vec2(b.max.x,b.max.z)));
    }

    static bool Visible(const Bounds& caja,const glm::vec4 (&planes)[6])
    {
        for(const auto& plano:planes)
        {
            const glm::vec3 esquina(plano.x>=0?caja.max.x:caja.min.x,
                plano.y>=0?caja.max.y:caja.min.y,plano.z>=0?caja.max.z:caja.min.z);
            if(glm::dot(plano,glm::vec4(esquina,1))<0) return false;
        }
        return true;
    }

    static bool Error(const char* detalle,const Semilla* semilla=nullptr)
    {
        std::cerr<<"ERROR VEGETACION: "<<detalle;
        if(semilla) std::cerr<<" en "<<semilla->x<<","<<semilla->z;
        std::cerr<<std::endl;
        return false;
    }
};
}
