#pragma once

namespace alumbrada4g
{
const glm::vec3 direccion(-.56f,-.84f,-.38f);

struct Luz
{
    glm::vec3 ambiente,difusa,especular;
    float lineal,cuadratica;
};

const Luz luna = {{.004f,.007f,.015f},{.018f,.029f,.063f},{.023f,.032f,.057f},0,0};
const Luz principal = {{.022f,.033f,.064f},{.071f,.105f,.183f},{.037f,.056f,.093f},0,0};
const Luz puntuales[] = {
    {{.085f,.040f,.012f},{2.05f,1.06f,.36f},{.43f,.22f,.072f},.155f,.070f},
    {{.065f,.039f,.017f},{1.72f,.89f,.36f},{.24f,.12f,.05f},.120f,.092f},
    {{.031f,.078f,.013f},{.28f,.70f,.11f},{.21f,.40f,.06f},.38f,.52f},
    {{.058f,.038f,.017f},{1.79f,1.02f,.42f},{.28f,.19f,.09f},.115f,.052f},
    {{.065f,.026f,.009f},{3.30f,1.75f,.53f},{.43f,.20f,.060f},.108f,.048f}
};
const Luz luna6c = {{.005f,.009f,.019f},{.022f,.034f,.076f},{.023f,.032f,.057f},0,0};
const Luz principal6c = {{.019f,.030f,.056f},{.084f,.118f,.197f},{.037f,.056f,.093f},0,0};
const Luz puntuales6c[] = {
    {{.085f,.039f,.011f},{2.10f,1.03f,.34f},{.43f,.22f,.072f},.155f,.070f},
    {{.065f,.039f,.017f},{1.72f,.89f,.36f},{.24f,.12f,.05f},.120f,.092f},
    {{.031f,.078f,.013f},{.28f,.70f,.11f},{.21f,.40f,.06f},.38f,.52f},
    {{.059f,.035f,.014f},{1.62f,.95f,.39f},{.28f,.19f,.09f},.165f,.095f},
    {{.070f,.028f,.009f},{3.45f,1.74f,.52f},{.43f,.20f,.060f},.100f,.045f}
};
const Luz foco = {{.009f,.013f,.026f},{.29f,.36f,.48f},{.070f,.083f,.118f},.115f,.048f};
const float corteFoco=15.f, bordeFoco=25.f, exposicion=.93f, emision=.92f;

class Perfil
{
public:
    explicit Perfil(GLuint program)
        : lunar(Leer(program,"moon")), direct(Leer(program,"dirLight")), cam(Leer(program,"spotLight")),
          dir(Loc(program,"dirLight.direction")), focoDir(Loc(program,"spotLight.direction")),
          interior(Loc(program,"spotLight.cutOff")), exterior(Loc(program,"spotLight.outerCutOff"))
    {
        for(size_t i=0;i<5;++i) puntos[i]=Leer(program,"pointLights["+std::to_string(i)+"]");
    }

    void Aplicar(glm::vec3 posicionLuna,const glm::vec3 (&posiciones)[5],const float (&pulso)[5],
                 glm::vec3 ojo,glm::vec3 rumbo,bool nueva) const
    {
        glUniform3fv(dir,1,glm::value_ptr(direccion));
        glUniform3fv(lunar.posicion,1,glm::value_ptr(posicionLuna));
        Color(direct,nueva ? principal6c : principal,1.f);
        Color(lunar,nueva ? luna6c : luna,1.f);
        const auto& luces=nueva ? puntuales6c : puntuales;
        for(size_t i=0;i<5;++i) Puntual(puntos[i],luces[i],posiciones[i],pulso[i]);
        Puntual(cam,foco,ojo,1.f);
        glUniform3fv(focoDir,1,glm::value_ptr(rumbo));
        glUniform1f(interior,std::cos(glm::radians(corteFoco)));
        glUniform1f(exterior,std::cos(glm::radians(bordeFoco)));
    }

private:
    struct Uniformes { GLint posicion,ambiente,difusa,especular,constante,lineal,cuadratica; };
    Uniformes lunar,direct,cam,puntos[5];
    GLint dir,focoDir,interior,exterior;

    static GLint Loc(GLuint program,const std::string& name) { return glGetUniformLocation(program,name.c_str()); }
    static Uniformes Leer(GLuint p,const std::string& n)
    {
        return {Loc(p,n+".position"),Loc(p,n+".ambient"),Loc(p,n+".diffuse"),Loc(p,n+".specular"),
            Loc(p,n+".constant"),Loc(p,n+".linear"),Loc(p,n+".quadratic")};
    }
    static void Color(const Uniformes& u,const Luz& luz,float pulso)
    {
        glUniform3fv(u.ambiente,1,glm::value_ptr(luz.ambiente*pulso));
        glUniform3fv(u.difusa,1,glm::value_ptr(luz.difusa*pulso));
        glUniform3fv(u.especular,1,glm::value_ptr(luz.especular*pulso));
    }
    static void Puntual(const Uniformes& u,const Luz& luz,glm::vec3 pos,float pulso)
    {
        Color(u,luz,pulso);
        glUniform3fv(u.posicion,1,glm::value_ptr(pos));
        glUniform1f(u.constante,1.f);
        glUniform1f(u.lineal,luz.lineal);
        glUniform1f(u.cuadratica,luz.cuadratica);
    }
};

class Sombras
{
public:
    static constexpr int dimension=2048;
    static constexpr int unidad=7;

    bool Crear(const std::vector<Placement>& tumbas,const Placement& v1,const Placement& v2)
    {
        shader=std::make_unique<Shader>("Shader/SombraDir.vs","Shader/SombraDir.frag");
        GLint linked=0;
        glGetProgramiv(shader->Program,GL_LINK_STATUS,&linked);
        if(!linked) return false;
        std::vector<glm::vec3> vertices;
        for(const auto& item:tumbas) Anexar(vertices,item,false);
        loteTumbas=static_cast<GLsizei>(vertices.size());
        Anexar(vertices,v1,false);
        loteV1=static_cast<GLsizei>(vertices.size())-loteTumbas;
        Anexar(vertices,v2,true);
        loteV2=static_cast<GLsizei>(vertices.size())-loteTumbas-loteV1;
        glGenVertexArrays(1,&vao);
        glGenBuffers(1,&vbo);
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER,vbo);
        glBufferData(GL_ARRAY_BUFFER,vertices.size()*sizeof(glm::vec3),vertices.data(),GL_STATIC_DRAW);
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(glm::vec3),nullptr);
        glEnableVertexAttribArray(0);
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER,0);
        glGenTextures(1,&profundidad);
        glBindTexture(GL_TEXTURE_2D,profundidad);
        glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH_COMPONENT24,dimension,dimension,0,GL_DEPTH_COMPONENT,GL_FLOAT,nullptr);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_MODE,GL_COMPARE_REF_TO_TEXTURE);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_FUNC,GL_LEQUAL);
        const float borde[]={1,1,1,1};
        glTexParameterfv(GL_TEXTURE_2D,GL_TEXTURE_BORDER_COLOR,borde);
        glBindTexture(GL_TEXTURE_2D,0);
        GLint framebuffer=0;
        glGetIntegerv(GL_FRAMEBUFFER_BINDING,&framebuffer);
        glGenFramebuffers(1,&fbo);
        glBindFramebuffer(GL_FRAMEBUFFER,fbo);
        glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D,profundidad,0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        const bool completo=glCheckFramebufferStatus(GL_FRAMEBUFFER)==GL_FRAMEBUFFER_COMPLETE;
        glBindFramebuffer(GL_FRAMEBUFFER,static_cast<GLuint>(framebuffer));
        const glm::vec3 centro(0,1,0);
        luzClip=glm::ortho(-45.f,45.f,-47.f,47.f,4.f,144.f)*
            glm::lookAt(centro-glm::normalize(direccion)*74.f,centro,glm::vec3(0,1,0));
        std::cout<<"SOMBRAS FBO: completo="<<completo<<" resolucion="<<dimension<<"x"<<dimension
            <<" lotes=2 tumbas="<<tumbas.size()<<" v2_triangulos="<<loteV2/3<<" tumbas_triangulos="<<loteTumbas/3<<std::endl;
        return completo && glGetError()==GL_NO_ERROR;
    }

    bool Actualizar(bool v2,const std::string& archivo)
    {
        if(listo && v2==temploV2) return true;
        GLint viewport[4],framebuffer=0,program=0,vertexArray=0;
        glGetIntegerv(GL_VIEWPORT,viewport);
        glGetIntegerv(GL_FRAMEBUFFER_BINDING,&framebuffer);
        glGetIntegerv(GL_CURRENT_PROGRAM,&program);
        glGetIntegerv(GL_VERTEX_ARRAY_BINDING,&vertexArray);
        glBindFramebuffer(GL_FRAMEBUFFER,fbo);
        glViewport(0,0,dimension,dimension);
        glClear(GL_DEPTH_BUFFER_BIT);
        shader->Use();
        glUniformMatrix4fv(glGetUniformLocation(shader->Program,"luzClip"),1,GL_FALSE,glm::value_ptr(luzClip));
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES,0,loteTumbas);
        glDrawArrays(GL_TRIANGLES,loteTumbas+(v2?loteV1:0),v2?loteV2:loteV1);
        const bool evidencia=archivo.empty() || Guardar(archivo);
        glBindVertexArray(static_cast<GLuint>(vertexArray));
        glUseProgram(static_cast<GLuint>(program));
        glBindFramebuffer(GL_FRAMEBUFFER,static_cast<GLuint>(framebuffer));
        glViewport(viewport[0],viewport[1],viewport[2],viewport[3]);
        std::cout<<"SOMBRAS MAPA: iglesia="<<(v2?2:1)<<" llamadas=2 triangulos="
            <<(loteTumbas+(v2?loteV2:loteV1))/3<<std::endl;
        temploV2=v2;
        listo=evidencia && glGetError()==GL_NO_ERROR;
        return listo;
    }

    void Enlazar(const Shader& lighting) const
    {
        glUniformMatrix4fv(glGetUniformLocation(lighting.Program,"shadowClip"),1,GL_FALSE,glm::value_ptr(luzClip));
        glActiveTexture(GL_TEXTURE0+unidad);
        glBindTexture(GL_TEXTURE_2D,profundidad);
        glActiveTexture(GL_TEXTURE0);
    }

    void Liberar()
    {
        if(shader) glDeleteProgram(shader->Program);
        glDeleteTextures(1,&profundidad);
        glDeleteFramebuffers(1,&fbo);
        glDeleteVertexArrays(1,&vao);
        glDeleteBuffers(1,&vbo);
    }

private:
    GLuint vao=0,vbo=0,fbo=0,profundidad=0;
    GLsizei loteTumbas=0,loteV1=0,loteV2=0;
    glm::mat4 luzClip{1};
    bool listo=false,temploV2=false;
    std::unique_ptr<Shader> shader;

    static void Anexar(std::vector<glm::vec3>& vertices,const Placement& placement,bool campanario)
    {
        const auto& meshes=placement.model->Meshes();
        for(size_t i=0;i<meshes.size();++i)
        {
            const Mesh& mesh=meshes[i];
            // La campana y los materiales de llama no forman parte del mapa estático.
            if((campanario && i>=256 && i<=258) || glm::length(mesh.materialEmission)>.25f) continue;
            for(auto index:mesh.indices)
                vertices.push_back(glm::vec3(placement.matrix*glm::vec4(mesh.vertices[index].Position,1)));
        }
    }

    static bool Guardar(const std::string& archivo)
    {
        std::vector<float> pixeles(dimension*dimension);
        glReadPixels(0,0,dimension,dimension,GL_DEPTH_COMPONENT,GL_FLOAT,pixeles.data());
        size_t ocupados=0;
        float menor=1.f, mayor=0.f;
        for(float z:pixeles)
            if(z<.999999f) { ++ocupados; menor=glm::min(menor,z); mayor=glm::max(mayor,z); }
        std::cout<<"SOMBRAS PROFUNDIDAD: texeles="<<ocupados<<" min="<<menor<<" max="<<mayor<<std::endl;
        if(ocupados==0 || mayor<=menor) return false;
        std::ofstream salida(archivo,std::ios::binary);
        salida<<"P5\n"<<dimension/2<<" "<<dimension/2<<"\n255\n";
        for(int y=dimension-1;y>=0;y-=2)
            for(int x=0;x<dimension;x+=2)
            {
                const float z=pixeles[y*dimension+x];
                const int gris=z>=.999999f?255:30+static_cast<int>(190*(z-menor)/(mayor-menor));
                salida.put(static_cast<char>(gris));
            }
        return static_cast<bool>(salida);
    }
};

class Humo
{
public:
    static constexpr int cantidad=7;

    bool Crear()
    {
        shader=std::make_unique<Shader>("Shader/HumoCopal.vs","Shader/HumoCopal.frag");
        GLint linked=0;
        glGetProgramiv(shader->Program,GL_LINK_STATUS,&linked);
        if(!linked) return false;
        glGenVertexArrays(1,&vao);
        glGenBuffers(1,&vbo);
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER,vbo);
        glBufferData(GL_ARRAY_BUFFER,sizeof(Particula)*cantidad,nullptr,GL_STREAM_DRAW);
        glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,sizeof(Particula),nullptr);
        glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,sizeof(Particula),reinterpret_cast<void*>(offsetof(Particula,apariencia)));
        for(GLuint i=0;i<2;++i)
        {
            glEnableVertexAttribArray(i);
            glVertexAttribDivisor(i,1);
        }
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER,0);
        return glGetError()==GL_NO_ERROR;
    }

    void Dibujar(glm::vec3 origen,float t,const glm::mat4& vista,const glm::mat4& proyeccion)
    {
        std::array<Particula,cantidad> particulas;
        for(int i=0;i<cantidad;++i)
        {
            const float fase=std::fmod(t/6.4f+i/static_cast<float>(cantidad),1.f);
            const float semilla=i*1.81f;
            const glm::vec3 deriva((.047f*std::sin(4.f*fase+semilla)-.091f)*fase,.59f*fase,
                (.094f+.044f*std::cos(4.f*fase+semilla))*fase);
            const float opacidad=.245f*glm::smoothstep(0.f,.13f,fase)*(1.f-glm::smoothstep(.36f,1.f,fase));
            particulas[i]={glm::vec4(origen+deriva,.063f+.132f*fase),{opacidad,semilla+fase*2.f}};
        }
        const glm::vec4 plano(vista[0][2],vista[1][2],vista[2][2],0);
        std::sort(particulas.begin(),particulas.end(),[&](const Particula& a,const Particula& b) {
            return glm::dot(plano,a.centro)<glm::dot(plano,b.centro);
        });
        const GLboolean mezcla=glIsEnabled(GL_BLEND);
        GLboolean mascara;
        GLint srcRGB,dstRGB,srcA,dstA,eqRGB,eqA;
        glGetBooleanv(GL_DEPTH_WRITEMASK,&mascara);
        glGetIntegerv(GL_BLEND_SRC_RGB,&srcRGB);
        glGetIntegerv(GL_BLEND_DST_RGB,&dstRGB);
        glGetIntegerv(GL_BLEND_SRC_ALPHA,&srcA);
        glGetIntegerv(GL_BLEND_DST_ALPHA,&dstA);
        glGetIntegerv(GL_BLEND_EQUATION_RGB,&eqRGB);
        glGetIntegerv(GL_BLEND_EQUATION_ALPHA,&eqA);
        glEnable(GL_BLEND);
        glBlendEquation(GL_FUNC_ADD);
        glBlendFuncSeparate(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA,GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
        glDepthMask(GL_FALSE);
        shader->Use();
        glUniformMatrix4fv(glGetUniformLocation(shader->Program,"vista"),1,GL_FALSE,glm::value_ptr(vista));
        glUniformMatrix4fv(glGetUniformLocation(shader->Program,"proyeccion"),1,GL_FALSE,glm::value_ptr(proyeccion));
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER,vbo);
        glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(particulas),particulas.data());
        alumbradaMedicion::Sumar(GL_TRIANGLES,6*cantidad);
        glDrawArraysInstanced(GL_TRIANGLES,0,6,cantidad);
        glBindBuffer(GL_ARRAY_BUFFER,0);
        glBindVertexArray(0);
        glDepthMask(mascara);
        glBlendEquationSeparate(eqRGB,eqA);
        glBlendFuncSeparate(srcRGB,dstRGB,srcA,dstA);
        if(!mezcla) glDisable(GL_BLEND);
    }

    void Liberar()
    {
        if(shader) glDeleteProgram(shader->Program);
        glDeleteVertexArrays(1,&vao);
        glDeleteBuffers(1,&vbo);
    }

private:
    struct Particula { glm::vec4 centro; glm::vec2 apariencia; };
    GLuint vao=0,vbo=0;
    std::unique_ptr<Shader> shader;
};
}
