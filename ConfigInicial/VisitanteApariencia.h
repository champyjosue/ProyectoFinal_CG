#pragma once

namespace visitanteApariencia
{
enum class Complemento { Ninguno, Boina, Monyo };

struct Atuendo
{
    glm::vec3 abrigo,pantalon,panuelo,pelo,cabeza;
    Complemento complemento;
};

const std::array<Atuendo,5> atuendos = {{
    {{.51f,.185f,.105f},{.275f,.235f,.195f},{.75f,.60f,.415f},{.15f,.09f,.063f},{1.03f,1.f,1.02f},Complemento::Ninguno},
    {{.14f,.375f,.33f},{.19f,.245f,.29f},{.69f,.55f,.22f},{.095f,.085f,.115f},{.965f,1.035f,.985f},Complemento::Ninguno},
    {{.43f,.145f,.28f},{.235f,.18f,.235f},{.60f,.36f,.47f},{.255f,.195f,.142f},{1.05f,.99f,1.02f},Complemento::Ninguno},
    {{.155f,.285f,.51f},{.255f,.29f,.34f},{.54f,.66f,.67f},{.135f,.106f,.081f},{1.015f,1.025f,1.f},Complemento::Boina},
    {{.335f,.38f,.18f},{.34f,.265f,.185f},{.66f,.51f,.32f},{.19f,.135f,.085f},{.97f,1.02f,1.04f},Complemento::Monyo}
}};

inline glm::vec3 Color(const Atuendo& a,const std::string& nombre,glm::vec3 original)
{
    if(nombre=="Visitante_Abrigo") return a.abrigo;
    if(nombre=="Visitante_Solapa") return glm::mix(a.abrigo,glm::vec3(.64f,.56f,.47f),.24f);
    if(nombre=="Visitante_Puno") return a.abrigo*.67f;
    if(nombre=="Visitante_Camisa") return glm::mix(a.abrigo,a.panuelo,.31f)*.72f;
    if(nombre=="Visitante_Pantalon") return a.pantalon;
    if(nombre=="Visitante_Costura") return a.pantalon+glm::vec3(.055f);
    if(nombre=="Visitante_Panuelo") return a.panuelo;
    if(nombre=="Visitante_Tejido_claro") return glm::mix(a.panuelo,glm::vec3(.83f,.76f,.65f),.31f);
    if(nombre=="Visitante_Pelo") return a.pelo;
    if(nombre=="Visitante_Mechon") return a.pelo+glm::vec3(.052f,.038f,.026f);
    return original;
}

struct Anillo { float y,x,z,radioX,radioZ; };

inline std::unique_ptr<Mesh> CrearComplemento(Complemento tipo,glm::vec3 pelo)
{
    if(tipo==Complemento::Ninguno) return {};
    const bool boina=tipo==Complemento::Boina;
    const Anillo gorra[]={{.248f,-.005f,-.002f,.105f,.108f},{.272f,-.008f,.004f,.131f,.135f},
                          {.307f,-.012f,.005f,.127f,.128f},{.339f,-.019f,-.006f,.062f,.074f}};
    const Anillo monyo[]={{.217f,.022f,-.105f,.030f,.033f},{.247f,.026f,-.119f,.049f,.049f},
                          {.284f,.026f,-.116f,.031f,.035f}};
    const auto* perfil=boina?gorra:monyo;
    const int anillos=boina?4:3, lados=boina?10:8;
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    const auto punto=[&](int nivel,int lado) {
        const float a=6.283185307f*lado/lados;
        const auto& p=perfil[nivel];
        return glm::vec3(p.x+p.radioX*std::cos(a),p.y,p.z+p.radioZ*std::sin(a));
    };
    const auto triangulo=[&](glm::vec3 a,glm::vec3 b,glm::vec3 c) {
        const auto normal=glm::normalize(glm::cross(b-a,c-a));
        for(const auto& v:{a,b,c})
        {
            indices.push_back(static_cast<GLuint>(vertices.size()));
            vertices.push_back({v,normal,glm::vec2(0)});
        }
    };
    for(int i=0;i<lados;++i)
    {
        for(int j=0;j+1<anillos;++j)
        {
            triangulo(punto(j,i),punto(j+1,i),punto(j,i+1));
            triangulo(punto(j,i+1),punto(j+1,i),punto(j+1,i+1));
        }
        const auto& a=perfil[0];
        const auto& b=perfil[anillos-1];
        triangulo({a.x,a.y,a.z},punto(0,i),punto(0,i+1));
        triangulo({b.x,b.y,b.z},punto(anillos-1,i+1),punto(anillos-1,i));
    }
    const auto color=boina?glm::vec3(.33f,.35f,.39f):pelo;
    return std::make_unique<Mesh>(vertices,indices,std::vector<Texture>{},color);
}
}
