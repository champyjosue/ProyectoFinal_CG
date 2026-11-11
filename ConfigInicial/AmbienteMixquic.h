#pragma once

namespace ambienteMixquic
{
enum class Demo { Ninguna, Campana, Insecto, Globos };

inline glm::mat4 Alrededor(glm::vec3 pivot, const glm::mat4& rotation)
{
    return glm::translate(glm::mat4(1),pivot)*rotation*glm::translate(glm::mat4(1),-pivot);
}

class CampanaInsecto
{
public:
    bool Preparar(const Model& temple, const Model& fly)
    {
        if (temple.Meshes().size() != 319 || fly.Meshes().size() != 6) return false;
        const size_t bellTriangles[] = {512,36,168};
        for (size_t part=0;part<3;++part)
        {
            const auto& mesh=temple.Meshes()[campanaPrimera+part];
            if (mesh.indices.size()!=bellTriangles[part]*3) return false;
            for (const auto& vertex : mesh.vertices)
                if (vertex.Position.y<4.53f || vertex.Position.y>5.49f ||
                    vertex.Position.x < -3.66f || vertex.Position.x > -2.66f ||
                    vertex.Position.z<2.85f || vertex.Position.z>3.85f) return false;
        }
        for (size_t part=0;part<2;++part)
        {
            const Mesh& source=fly.Meshes()[4+part];
            if (source.indices.size()!=288 || !source.textures.empty()) return false;
            for (size_t sideIndex=0;sideIndex<2;++sideIndex)
            {
                const float side=sideIndex==0?-1.f:1.f;
                const glm::vec3 pivot(side*.015f,.019f,0);
                std::vector<Vertex> vertices;
                std::vector<GLuint> indices;
                for (size_t i=0;i<source.indices.size();i+=3)
                {
                    if (source.vertices[source.indices[i]].Position.x*side<=0) continue;
                    for (size_t k=0;k<3;++k)
                    {
                        const auto& vertex=source.vertices[source.indices[i+k]];
                        if (vertex.Position.x*side<=0 ||
                            (glm::length(pivot)+glm::length(vertex.Position-pivot))*ESC_LUCIERNAGA>.20f)
                            return false;
                        indices.push_back(static_cast<GLuint>(vertices.size()));
                        vertices.push_back(vertex);
                    }
                }
                if (indices.size()!=144) return false;
                wings[part*2+sideIndex].reset(new Mesh(vertices,indices,{},source.materialColor,source.materialEmission));
            }
        }
        for (size_t part=0;part<4;++part)
            for (const auto& vertex : fly.Meshes()[part].vertices)
                if (glm::length(vertex.Position)*ESC_LUCIERNAGA>.20f) return false;
        std::cout << "AMBIENTE A: campana=716 triangulos articulados; pasador=36 triangulos reutilizados; insecto=784 triangulos, 8 llamadas; extra_llamadas=3 extra_triangulos=36" << std::endl;
        return true;
    }

    static float AnguloCampana(float t) { return 16.f*sin(6.283185307f*t/2.8f); }
    static float AnguloAla(float t) { return 34.f*sin(6.283185307f*4.5f*t); }

    static bool VueloLibre(const std::vector<Bounds>& obstacles)
    {
        const Bounds sweep={posLuciernaga-glm::vec3(.90f,.38f,.90f),posLuciernaga+glm::vec3(.90f,.38f,.90f)};
        for (const auto& box : obstacles)
            if (UnifiedOverlap3(sweep,box)) return false;
        std::cout << "AMBIENTE INSECTO: envolvente conservadora 1.80 x 0.76 x 1.80; trayecto libre." << std::endl;
        return true;
    }

    void DibujarTemplo(Model& temple, const glm::mat4& base, Shader& shader, float t) const
    {
        const GLint location=glGetUniformLocation(shader.Program,"model");
        glUniformMatrix4fv(location,1,GL_FALSE,glm::value_ptr(base));
        const glm::mat4 moving=base*Alrededor({-3.16f,5.52f,3.35f},
            glm::rotate(glm::mat4(1),glm::radians(AnguloCampana(t)),{0,0,1}));
        for (size_t i=0;i<temple.Meshes().size();++i)
        {
            if (i==campanaPrimera) glUniformMatrix4fv(location,1,GL_FALSE,glm::value_ptr(moving));
            if (i==campanaPrimera+3) glUniformMatrix4fv(location,1,GL_FALSE,glm::value_ptr(base));
            temple.DrawMesh(i,shader);
        }
        // Reutiliza el vástago de hierro para cerrar la holgura original en el punto de suspensión.
        const glm::mat4 pin=glm::translate(glm::mat4(1),{-3.16f,5.49f,3.35f})*
            glm::scale(glm::mat4(1),{1.35f,.24f,1.35f})*
            glm::translate(glm::mat4(1),{3.16f,-4.88f,-3.35f});
        const glm::mat4 attachedPin=moving*pin;
        glUniformMatrix4fv(location,1,GL_FALSE,glm::value_ptr(attachedPin));
        temple.DrawMesh(campanaPrimera+1,shader);
    }

    void DibujarInsecto(Model& fly, const glm::mat4& base, Shader& shader, float t)
    {
        const GLint location=glGetUniformLocation(shader.Program,"model");
        glUniformMatrix4fv(location,1,GL_FALSE,glm::value_ptr(base));
        for (size_t part=0;part<4;++part) fly.DrawMesh(part,shader);
        for (size_t i=0;i<wings.size();++i)
        {
            const float side=i%2==0?-1.f:1.f;
            const float flap=i<2?7.f+.25f*AnguloAla(t):AnguloAla(t);
            const glm::mat4 rotation=glm::rotate(glm::mat4(1),glm::radians(side*flap),{0,0,1})*
                glm::rotate(glm::mat4(1),glm::radians(-side*(i<2?16.f:34.f)),{0,1,0});
            const glm::mat4 matrix=base*Alrededor({side*.015f,.019f,0},rotation);
            glUniformMatrix4fv(location,1,GL_FALSE,glm::value_ptr(matrix));
            wings[i]->Draw(shader);
        }
    }

    void Liberar()
    {
        for (auto& wing : wings)
        {
            if (wing) wing->ReleaseGpu();
            wing.reset();
        }
    }

private:
    static constexpr size_t campanaPrimera=256;
    std::array<std::unique_ptr<Mesh>,4> wings;
};
}
