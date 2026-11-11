#pragma once

#include <array>
#include <cmath>
#include <memory>

namespace cantoyaMixquic
{
    struct Trayectoria
    {
        glm::vec3 origen;
        float vuelo, ascenso, fase, escala;
    };

    const std::array<Trayectoria,5> Rutas = {{
        {{-16.7f,10.8f,-36.5f},31,22,8,1.f},
        {{-24.5f,12.8f,-42.0f},41,26,13,1.12f},
        {{ 16.6f,10.5f,-36.7f},36,23,7,.96f},
        {{ 22.5f,12.1f,-40.5f},45,27,17,1.06f},
        {{ 28.5f,15.2f,-47.0f},52,31,11,1.18f}
    }};
    const glm::vec3 OjoDemo(0,1.7f,14);
    const glm::vec3 CentroDemo(0,16,-39);

    struct Estado
    {
        glm::vec3 posicion;
        float visibilidad, guiñada, inclinacion, brillo;
    };

    inline Estado Evaluar(const Trayectoria& ruta,float tiempo)
    {
        const float edad = std::fmod(tiempo+ruta.fase,ruta.vuelo+3.f);
        const float p = glm::min(edad/ruta.vuelo,1.f);
        const float visible = glm::smoothstep(0.f,.12f,p)*(1.f-glm::smoothstep(.85f,1.f,p));
        const float deriva = p*ruta.vuelo;
        return {
            ruta.origen + glm::vec3(.78f*std::sin(.43f*deriva+ruta.fase),
                ruta.ascenso*(.18f*p+.82f*glm::smoothstep(0.f,1.f,p)),
                .58f*std::sin(.30f*deriva-.5f*ruta.fase)),
            visible, .23f*std::sin(.28f*deriva+ruta.fase),
            .075f*std::sin(.43f*deriva+.4f*ruta.fase),
            .93f+.07f*std::sin(3.3f*deriva+ruta.fase)
        };
    }

    enum class Modelo { V1, V2 };

    class Faroles
    {
    public:
        bool Crear(Modelo modelo)
        {
            if(modelo==Modelo::V2)
            {
                modeloV2=std::make_unique<Model>("Models/Cantoya_V2/cantoya_v2.obj",true);
                return ValidarV2();
            }
            const int lados = 16;
            const std::array<glm::vec2,8> perfil = {{
                {0,.24f},{.12f,.39f},{.33f,.54f},{.70f,.62f},
                {1.07f,.59f},{1.34f,.42f},{1.45f,.22f},{1.47f,0}
            }};
            std::array<std::vector<Vertex>,3> vertices;
            for(int lado=0;lado<lados;++lado)
            {
                auto& papel = vertices[(lado/2)%2];
                for(size_t i=0;i+1<perfil.size();++i)
                {
                    const auto a = Punto(lado,lados,perfil[i]);
                    const auto b = Punto(lado+1,lados,perfil[i]);
                    const auto c = Punto(lado,lados,perfil[i+1]);
                    const auto d = Punto(lado+1,lados,perfil[i+1]);
                    Triangulo(papel,a,c,b);
                    if(i+2<perfil.size()) Triangulo(papel,b,c,d);
                }
                Triangulo(vertices[2],glm::vec3(0,.14f,0),
                    Punto(lado,lados,{.09f,.214f}),Punto(lado+1,lados,{.09f,.214f}));
            }
            for(size_t i=0;i<piezas.size();++i)
            {
                std::vector<GLuint> indices;
                for(GLuint v=0;v<vertices[i].size();++v) indices.push_back(v);
                piezas[i] = std::make_unique<Mesh>(vertices[i],indices,std::vector<Texture>{},glm::vec3(1));
            }
            return true;
        }

        unsigned Dibujar(const Shader& shader,GLint modelo,float tiempo,GLint pulsoLoc,float pulso)
        {
            const std::array<glm::vec3,3> papel = {{
                {.50f,.21f,.047f},{.35f,.13f,.025f},{.64f,.32f,.058f}
            }};
            const std::array<glm::vec3,3> luz = {{
                {.80f,.38f,.107f},{.56f,.225f,.054f},{1.05f,.63f,.21f}
            }};
            unsigned visibles = 0;
            for(const auto& ruta:Rutas)
            {
                const Estado actual = Evaluar(ruta,tiempo);
                if(actual.visibilidad<=0) continue;
                ++visibles;
                auto matriz = glm::translate(glm::mat4(1),actual.posicion);
                matriz = glm::rotate(matriz,actual.guiñada,glm::vec3(0,1,0));
                matriz = glm::rotate(matriz,actual.inclinacion,glm::vec3(0,0,1));
                matriz = glm::scale(matriz,glm::vec3(ruta.escala*actual.visibilidad));
                glUniformMatrix4fv(modelo,1,GL_FALSE,glm::value_ptr(matriz));
                if(modeloV2)
                {
                    glUniform1f(pulsoLoc,pulso*actual.brillo);
                    modeloV2->Draw(shader);
                }
                else
                {
                    for(size_t i=0;i<piezas.size();++i)
                    {
                        piezas[i]->materialColor = papel[i];
                        piezas[i]->materialEmission = luz[i]*actual.brillo;
                        piezas[i]->Draw(shader);
                    }
                }
            }
            if(modeloV2 && visibles) glUniform1f(pulsoLoc,pulso);
            return visibles;
        }

        unsigned TriangulosPorGlobo() const
        {
            if(modeloV2) return static_cast<unsigned>(modeloV2->TriangleCount());
            unsigned total = 0;
            for(const auto& pieza:piezas) total += static_cast<unsigned>(pieza->indices.size()/3);
            return total;
        }

        unsigned DibujosPorGlobo() const
        {
            return static_cast<unsigned>(modeloV2 ? modeloV2->Meshes().size() : piezas.size());
        }

        void Liberar()
        {
            modeloV2.reset();
            for(auto& pieza:piezas)
            {
                if(pieza) pieza->ReleaseGpu();
                pieza.reset();
            }
        }

    private:
        std::array<std::unique_ptr<Mesh>,3> piezas;
        std::unique_ptr<Model> modeloV2;

        bool ValidarV2() const
        {
            if(!modeloV2->IsLoaded() || modeloV2->MaterialCount()!=6 || modeloV2->Meshes().size()!=6) return false;
            size_t materialesTexturados=0;
            GLuint texturaPapel=0;
            float radioMaximo=0;
            for(const auto& pieza:modeloV2->Meshes())
            {
                if(glm::length(pieza.materialEmission)<=0) return false;
                for(const auto& vertice:pieza.vertices)
                    radioMaximo=glm::max(radioMaximo,glm::length(vertice.Position));
                if(pieza.textures.empty()) continue;
                if(pieza.textures.size()!=1 || !glIsTexture(pieza.textures[0].id)) return false;
                if(texturaPapel && texturaPapel!=pieza.textures[0].id) return false;
                texturaPapel=pieza.textures[0].id;
                ++materialesTexturados;
            }
            if(materialesTexturados!=3 || radioMaximo>1.62f) return false;
            GLint previa=0,ancho=0,alto=0;
            glGetIntegerv(GL_TEXTURE_BINDING_2D,&previa);
            glBindTexture(GL_TEXTURE_2D,texturaPapel);
            glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_WIDTH,&ancho);
            glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_HEIGHT,&alto);
            glBindTexture(GL_TEXTURE_2D,static_cast<GLuint>(previa));
            if(ancho!=512 || alto!=256) return false;
            std::cout << "CANTOYA ASSET: submallas=" << DibujosPorGlobo() << " triangulos=" << TriangulosPorGlobo()
                << " materiales=6 textura_compartida=" << ancho << "x" << alto
                << " radio=" << radioMaximo << std::endl;
            return true;
        }

        static glm::vec3 Punto(int lado,int lados,glm::vec2 perfil)
        {
            const float a = glm::radians(360.f)*lado/lados;
            const float x = std::cos(a), z = std::sin(a);
            return {perfil.y*std::copysign(std::pow(std::abs(x),.68f),x),perfil.x,
                    perfil.y*std::copysign(std::pow(std::abs(z),.68f),z)};
        }

        static void Triangulo(std::vector<Vertex>& vertices,glm::vec3 a,glm::vec3 b,glm::vec3 c)
        {
            const auto normal = glm::normalize(glm::cross(b-a,c-a));
            vertices.push_back({a,normal,{0,0}});
            vertices.push_back({b,normal,{0,0}});
            vertices.push_back({c,normal,{0,0}});
        }
    };
}
