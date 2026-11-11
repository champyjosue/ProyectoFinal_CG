#pragma once

namespace alumbrada6c
{
class Ambiente
{
public:
    bool Crear(GLuint programa, const Placement* camino, const Placement& ofrenda,
               const std::vector<Placement>& adornos, const std::vector<Placement>& fuentesFijas,
               const Model& farol, const Model& vela, const Model& veladora, bool ampliado, bool revisar, bool ligera)
    {
        revision=revisar;
        extension = ampliado ? glm::vec2(25,32) : glm::vec2(17,21);
        locFuente=glGetUniformLocation(programa,"fuenteDecorativa");
        locTierra=glGetUniformLocation(programa,"tierraMixquic");
        std::vector<float> huella(lado*lado,0), calidez(lado*lado,0), calidezVeladoras(lado*lado,0);
        std::vector<VerticeHalo> halos;
        if(camino)
        {
            for(const auto& m:camino->model->Meshes())
                for(size_t i=0;i<m.indices.size();i+=3)
                    Marcar(huella,glm::vec3(camino->matrix*glm::vec4(m.vertices[m.indices[i]].Position,1)),
                                   glm::vec3(camino->matrix*glm::vec4(m.vertices[m.indices[i+1]].Position,1)),
                                   glm::vec3(camino->matrix*glm::vec4(m.vertices[m.indices[i+2]].Position,1)));
            Suavizar(huella);
        }
        int postes=0, cirios=0, vasos=0;
        const auto anexar = [&](const Placement& p)
        {
            const bool poste=p.model==&farol;
            if(!poste && p.model!=&vela && p.model!=&veladora) return;
            if(poste) ++postes;
            else if(p.model==&vela) ++cirios;
            else ++vasos;
            for(const auto& m:p.model->Meshes())
            {
                // El vidrio de la veladora también emite, pero el halo se centra en la llama.
                if(m.materialColor.r<=1.7f || glm::length(m.materialEmission)<.001f) continue;
                glm::vec3 centro(0);
                for(const auto& v:m.vertices) centro+=glm::vec3(p.matrix*glm::vec4(v.Position,1));
                centro/=float(m.vertices.size());
                const float ancho=(std::max)(p.bounds.max.x-p.bounds.min.x,p.bounds.max.z-p.bounds.min.z);
                const float radio=poste ? glm::clamp(ancho*.93f,.23f,.48f) : glm::clamp(ancho*.56f,.075f,.22f);
                Calentar(calidez,centro,poste?3.1f:1.24f,poste?.48f:.14f);
                const bool veladoraRevisada=revision && p.model==&veladora;
                if(veladoraRevisada)
                {
                    Calentar(calidezVeladoras,centro,1.42f,.23f);
                    AgregarHalo(halos,centro,glm::clamp(ancho*1.16f,.105f,.23f),.40f,true);
                }
                else AgregarHalo(halos,centro,radio,poste ? .20f : .28f,false);
            }
        };
        for(const auto& p:adornos) anexar(p);
        for(const auto& p:fuentesFijas) anexar(p);
        Calentar(calidez,(ofrenda.bounds.min+ofrenda.bounds.max)*.5f,4.1f,.78f);
        const int canales=revision ? 3 : 2;
        std::vector<unsigned char> datos(lado*lado*canales);
        for(size_t i=0;i<huella.size();++i)
        {
            datos[i*canales]=static_cast<unsigned char>(glm::clamp(huella[i],0.f,1.f)*255.f+.5f);
            datos[i*canales+1]=static_cast<unsigned char>(glm::clamp(calidez[i],0.f,1.f)*255.f+.5f);
            if(revision) datos[i*canales+2]=static_cast<unsigned char>(glm::clamp(calidezVeladoras[i],0.f,1.f)*255.f+.5f);
        }
        glActiveTexture(GL_TEXTURE0);
        glGenTextures(1,&mapa);
        glBindTexture(GL_TEXTURE_2D,mapa);
        glTexImage2D(GL_TEXTURE_2D,0,revision?GL_RGB8:GL_RG8,lado,lado,0,revision?GL_RGB:GL_RG,GL_UNSIGNED_BYTE,datos.data());
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
        glBindTexture(GL_TEXTURE_2D,0);
        const char* rutaTierra=revision ? "images/tierra_mixquic_6c1.png" : "images/tierra_mixquic_6c.png";
        tierra=SOIL_load_OGL_texture(rutaTierra,revision?SOIL_LOAD_RGBA:SOIL_LOAD_RGB,SOIL_CREATE_NEW_ID,SOIL_FLAG_MIPMAPS);
        if(!tierra || !mapa) return false;
        glBindTexture(GL_TEXTURE_2D,tierra);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
        if(revision && !ligera && GLEW_EXT_texture_filter_anisotropic)
        {
            GLfloat maximo=1;
            glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT,&maximo);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAX_ANISOTROPY_EXT,(std::min)(4.f,maximo));
        }
        glBindTexture(GL_TEXTURE_2D,0);
        glUniform1i(glGetUniformLocation(programa,"revision6c1"),revision);
        glUniform1i(glGetUniformLocation(programa,"tierraLigera6c1"),ligera);
        glUniform1i(glGetUniformLocation(programa,"mapaAlumbrada"),8);
        glUniform1i(glGetUniformLocation(programa,"muestraTierra"),9);
        glUniform2fv(glGetUniformLocation(programa,"extensionAlumbrada"),1,glm::value_ptr(extension));
        glUniform1i(glGetUniformLocation(programa,"alumbrada6c"),1);
        if(!halos.empty() && !CrearHalos(halos)) return false;
        std::cout<<"ALUMBRADA 6C: faroles="<<postes<<" velas="<<cirios<<" veladoras="<<vasos
                 <<" halos="<<vertices/6<<" mapa="<<lado<<"x"<<lado<<" plantas_extra=0"<<std::endl;
        if(revision)
            std::cout<<"ALUMBRADA 6C.1: veladoras="<<vasos<<" suelo="<<rutaTierra
                     <<" modo="<<(ligera?"ligero":"detalle")<<" luces_puntuales=5"<<std::endl;
        return true;
    }

    void Enlazar() const
    {
        if(!mapa) return;
        glActiveTexture(GL_TEXTURE8);
        glBindTexture(GL_TEXTURE_2D,mapa);
        glActiveTexture(GL_TEXTURE9);
        glBindTexture(GL_TEXTURE_2D,tierra);
        glActiveTexture(GL_TEXTURE0);
    }

    void Tierra(bool habilitada) const { if(locTierra>=0) glUniform1i(locTierra,habilitada); }
    void Fuente(const Model* p, const Model& farol, const Model& vela, const Model& veladora)
    {
        if(locFuente<0) return;
        const int valor=p==&farol ? 1 : p==&veladora && revision ? 3 : p==&vela || p==&veladora ? 2 : 0;
        if(valor!=fuenteActual)
        {
            glUniform1i(locFuente,valor);
            fuenteActual=valor;
        }
    }

    void DibujarHalos(const glm::mat4& view,const glm::mat4& projection,float t) const
    {
        if(!vertices) return;
        // El pase se ejecuta al terminar las transparencias de la escena.
        GLint program=0, previoVao=0;
        glGetIntegerv(GL_CURRENT_PROGRAM,&program);
        glGetIntegerv(GL_VERTEX_ARRAY_BINDING,&previoVao);
        const bool blend=glIsEnabled(GL_BLEND)!=0;
        GLboolean profundidad=GL_TRUE;
        glGetBooleanv(GL_DEPTH_WRITEMASK,&profundidad);
        GLint srcRgb=0,dstRgb=0,srcA=0,dstA=0,ecuacionRgb=0,ecuacionA=0;
        glGetIntegerv(GL_BLEND_SRC_RGB,&srcRgb);
        glGetIntegerv(GL_BLEND_DST_RGB,&dstRgb);
        glGetIntegerv(GL_BLEND_SRC_ALPHA,&srcA);
        glGetIntegerv(GL_BLEND_DST_ALPHA,&dstA);
        glGetIntegerv(GL_BLEND_EQUATION_RGB,&ecuacionRgb);
        glGetIntegerv(GL_BLEND_EQUATION_ALPHA,&ecuacionA);
        glEnable(GL_BLEND);
        glBlendEquation(GL_FUNC_ADD);
        glBlendFuncSeparate(GL_ONE,GL_ONE,GL_ZERO,GL_ONE);
        glDepthMask(GL_FALSE);
        shader->Use();
        glUniformMatrix4fv(vista,1,GL_FALSE,glm::value_ptr(view));
        glUniformMatrix4fv(proy,1,GL_FALSE,glm::value_ptr(projection));
        glUniform1f(tiempo,t);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES,0,vertices);
        glBindVertexArray(previoVao);
        glUseProgram(program);
        glDepthMask(profundidad);
        glBlendEquationSeparate(ecuacionRgb,ecuacionA);
        glBlendFuncSeparate(srcRgb,dstRgb,srcA,dstA);
        if(!blend) glDisable(GL_BLEND);
    }

    void Liberar()
    {
        if(shader) glDeleteProgram(shader->Program);
        glDeleteVertexArrays(1,&vao);
        glDeleteBuffers(1,&vbo);
        glDeleteTextures(1,&mapa);
        glDeleteTextures(1,&tierra);
    }

private:
    static constexpr int lado=512;
    struct VerticeHalo { glm::vec3 centro; glm::vec2 esquina; glm::vec3 parametros; };
    bool revision=false;
    glm::vec2 extension{25,32};
    GLuint mapa=0,tierra=0,vao=0,vbo=0;
    GLint locTierra=-1,locFuente=-1,vista=-1,proy=-1,tiempo=-1;
    int fuenteActual=0;
    GLsizei vertices=0;
    std::unique_ptr<Shader> shader;

    glm::vec2 Pixel(glm::vec3 p) const
    {
        return (glm::vec2(p.x,p.z)/extension*.5f+.5f)*float(lado);
    }

    static float Cruz(glm::vec2 a, glm::vec2 b) { return a.x*b.y-a.y*b.x; }

    void Marcar(std::vector<float>& imagen,glm::vec3 a,glm::vec3 b,glm::vec3 c) const
    {
        const auto p=Pixel(a),q=Pixel(b),r=Pixel(c);
        const float area=Cruz(q-p,r-p);
        if(std::abs(area)<.001f) return;
        const auto min=glm::min(p,glm::min(q,r)),max=glm::max(p,glm::max(q,r));
        for(int y=glm::max(0,int(min.y));y<=glm::min(lado-1,int(max.y));++y)
            for(int x=glm::max(0,int(min.x));x<=glm::min(lado-1,int(max.x));++x)
            {
                const glm::vec2 muestra(x+.5f,y+.5f);
                const float u=Cruz(q-p,muestra-p)/area,v=Cruz(r-q,muestra-q)/area;
                if(u>=0 && v>=0 && u+v<=1) imagen[y*lado+x]=1;
            }
    }

    static void Suavizar(std::vector<float>& imagen)
    {
        std::vector<float> temp(imagen.size(),0);
        const float pesos[]={.24f,.19f,.12f,.055f,.015f};
        for(int y=0;y<lado;++y) for(int x=0;x<lado;++x)
            for(int i=-4;i<=4;++i) temp[y*lado+x]+=imagen[y*lado+glm::clamp(x+i,0,lado-1)]*pesos[std::abs(i)];
        for(int y=0;y<lado;++y) for(int x=0;x<lado;++x)
        {
            float valor=0;
            for(int i=-4;i<=4;++i) valor+=temp[glm::clamp(y+i,0,lado-1)*lado+x]*pesos[std::abs(i)];
            imagen[y*lado+x]=valor;
        }
    }

    void Calentar(std::vector<float>& imagen,glm::vec3 p,float radio,float fuerza) const
    {
        const auto c=Pixel(p),r=glm::vec2(radio)/extension*.5f*float(lado);
        for(int y=glm::max(0,int(c.y-r.y));y<=glm::min(lado-1,int(c.y+r.y));++y)
            for(int x=glm::max(0,int(c.x-r.x));x<=glm::min(lado-1,int(c.x+r.x));++x)
            {
                const glm::vec2 d=(glm::vec2(x+.5f,y+.5f)-c)/r;
                const float peso=glm::max(0.f,1.f-glm::dot(d,d));
                imagen[y*lado+x]+=fuerza*peso*peso;
            }
    }

    static void AgregarHalo(std::vector<VerticeHalo>& buffer,glm::vec3 c,float r,float fuerza,bool veladora)
    {
        const glm::vec2 esquinas[]={{-1,-1},{1,-1},{1,1},{-1,-1},{1,1},{-1,1}};
        for(auto esquina:esquinas) buffer.push_back({c,esquina,{r,fuerza,veladora?1.f:0.f}});
    }

    bool CrearHalos(const std::vector<VerticeHalo>& buffer)
    {
        shader=std::make_unique<Shader>("Shader/HaloMixquic6C.vs","Shader/HaloMixquic6C.frag");
        GLint enlazado=0;
        glGetProgramiv(shader->Program,GL_LINK_STATUS,&enlazado);
        if(!enlazado) return false;
        vista=glGetUniformLocation(shader->Program,"vista");
        proy=glGetUniformLocation(shader->Program,"proyeccion");
        tiempo=glGetUniformLocation(shader->Program,"tiempo");
        glGenVertexArrays(1,&vao);
        glGenBuffers(1,&vbo);
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER,vbo);
        glBufferData(GL_ARRAY_BUFFER,buffer.size()*sizeof(VerticeHalo),buffer.data(),GL_STATIC_DRAW);
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(VerticeHalo),nullptr);
        glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,sizeof(VerticeHalo),reinterpret_cast<void*>(offsetof(VerticeHalo,esquina)));
        glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,sizeof(VerticeHalo),reinterpret_cast<void*>(offsetof(VerticeHalo,parametros)));
        for(GLuint i=0;i<3;++i) glEnableVertexAttribArray(i);
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER,0);
        vertices=static_cast<GLsizei>(buffer.size());
        return true;
    }
};
}
