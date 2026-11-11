#pragma once

#include <array>
#include <memory>
#include <glm/gtc/quaternion.hpp>
#include "VisitanteDatos.h"
#include "VisitanteKeyframes.h"
#include "VisitanteApariencia.h"

namespace visitanteCiclo
{
class Reloj
{
public:
    explicit Reloj(double esperaInicial=0) : espera(esperaInicial) {}
    float Fase(double ahora,float duracion) const
    {
        return static_cast<float>(std::fmod((std::max)(0.0,ahora-inicio-espera),duracion));
    }
    void Reiniciar(double ahora) { inicio=ahora; espera=0; }
private:
    double inicio=0, espera;
};

struct Muestra { float tiempo; bool regreso; };

inline Muestra IdaYVuelta(float fase,float duracion,float pausa)
{
    const float regreso=fase-duracion-pausa;
    return regreso>0 ? Muestra{(std::max)(0.f,duracion-regreso),true}
                     : Muestra{(std::min)(fase,duracion),false};
}
}

// OBJ aporta vertices locales. Esta jerarquia reconstruye los pivotes de Blender.
class VisitanteAnimado
{
public:
    using Matrices = std::array<glm::mat4, visitanteDatos::BodyCount>;

    bool Load(const std::string& directory)
    {
        size_t triangles = 0, meshes = 0;
        std::set<std::string> palette;
        for (int i = 0; i < visitanteDatos::PartCount; ++i)
        {
            const auto& spec = visitanteDatos::parts[i];
            models[i].reset(new Model((directory + "/" + spec.file).c_str()));
            const Model& model = *models[i];
            if (!model.IsLoaded() || model.TriangleCount() != spec.triangles ||
                model.MaterialCount() != spec.materials ||
                glm::length(model.BoundsMin() - spec.minimum) > 0.00001f ||
                glm::length(model.BoundsMax() - spec.maximum) > 0.00001f)
                return false;
            for (const Mesh& mesh : model.Meshes())
                for (const Vertex& vertex : mesh.vertices)
                    if (!std::isfinite(vertex.Normal.x) ||
                        fabs(glm::length(vertex.Normal) - 1.0f) > 0.0001f)
                        return false;
            for (const auto& material : model.MaterialColors()) palette.insert(material.first);
            triangles += model.TriangleCount();
            meshes += model.Meshes().size();
            std::cout << "VISITANTE ASSET " << spec.file << " tri=" << model.TriangleCount()
                << " submallas=" << model.Meshes().size() << " materiales=" << model.MaterialCount() << std::endl;
        }
        std::cout << "VISITANTE CARGA: OBJ=17 triangulos=" << triangles
            << " submallas=" << meshes << " materiales=" << palette.size() << std::endl;
        return triangles == 4897 && meshes == 48 && palette.size() == 28 && ValidatePivots();
    }

    VisitanteAnimado CompartirPiezas() const
    {
        VisitanteAnimado instance;
        instance.models = models;
        return instance;
    }

    Model& Pieza(int index) { return *models[index]; }

    Matrices Articular(const visitanteDatos::Pose& pose, float forward) const
    {
        return ComposeSupported(pose, forward);
    }

    bool ComprobarArticulacion(const Matrices& matrices, const std::vector<Bounds>& obstacles,
        const Placement& grave, const std::vector<UnifiedSegment>& routes) const
    {
        return ValidateBody(matrices, obstacles, grave, routes);
    }

    void Place(const glm::vec3& position, float yawDegrees, const std::vector<Surface>& surfaces)
    {
        root = glm::rotate(glm::translate(glm::mat4(1), position),
            glm::radians(yawDegrees), glm::vec3(0, 1, 0));
        supports.clear();
        const Bounds area = {position - glm::vec3(1.5f), position + glm::vec3(1.5f)};
        for (const auto& surface : surfaces)
        {
            const Bounds bounds = {surface.center - surface.size * .5f, surface.center + surface.size * .5f};
            if (OverlapXZ(area, bounds)) supports.push_back(bounds);
        }
    }

    Matrices Compose(const visitanteDatos::Pose& pose, float forward = 0) const
    {
        Matrices result;
        const glm::mat4 base = root * glm::translate(glm::mat4(1), glm::vec3(0, pose.rootY, forward));
        for (int i = 0; i < visitanteDatos::BodyCount; ++i)
        {
            const auto& part = visitanteDatos::parts[i];
            glm::mat4 local = glm::translate(glm::mat4(1), part.offset);
            local = glm::rotate(local, glm::radians(pose.angles[i].z), glm::vec3(0, 0, 1));
            local = glm::rotate(local, glm::radians(pose.angles[i].y), glm::vec3(0, 1, 0));
            local = glm::rotate(local, glm::radians(pose.angles[i].x), glm::vec3(1, 0, 0));
            result[i] = (part.parent < 0 ? base : result[part.parent]) * local;
        }
        return result;
    }

    glm::mat4 HandFlower(const Matrices& matrices) const
    {
        return glm::translate(matrices[visitanteDatos::ManoDerecha], glm::vec3(0, -0.065f, 0.020f));
    }

    void Draw(Shader& shader, int poseIndex)
    {
        const Matrices matrices = ComposeSupported(visitanteDatos::poses[poseIndex], 0);
        DrawMatrices(shader, matrices, HandFlower(matrices));
    }

    void ElegirAtuendo(size_t numero)
    {
        const auto& atuendo=visitanteApariencia::atuendos[numero];
        escalaCabeza=atuendo.cabeza;
        for(int parte=0;parte<visitanteDatos::BodyCount;++parte)
        {
            const auto& modelo=*models[parte];
            for(const auto& mesh:modelo.Meshes())
            {
                glm::vec3 color=mesh.materialColor;
                for(const auto& material:modelo.MaterialColors())
                {
                    if(glm::length(material.second-mesh.materialColor)<.00001f)
                        color=visitanteApariencia::Color(atuendo,material.first,color);
                }
                colores[parte].push_back(color);
            }
        }
        complemento=visitanteApariencia::CrearComplemento(atuendo.complemento,atuendo.pelo);
    }

    struct ConteoPieza { size_t llamadas, triangulos; };

    ConteoPieza DibujarPieza(const Shader& shader,GLint uniform,int parte,const glm::mat4& matriz)
    {
        const auto transformacion=parte==visitanteDatos::Cabeza ? glm::scale(matriz,escalaCabeza) : matriz;
        glUniformMatrix4fv(uniform,1,GL_FALSE,glm::value_ptr(transformacion));
        Model& modelo=*models[parte];
        if(parte>=visitanteDatos::BodyCount || colores[parte].empty()) modelo.Draw(shader);
        else
            for(size_t i=0;i<colores[parte].size();++i) modelo.DrawMesh(i,shader,&colores[parte][i]);
        ConteoPieza resultado{modelo.Meshes().size(),modelo.TriangleCount()};
        if(parte==visitanteDatos::Cabeza && complemento)
        {
            complemento->Draw(shader);
            ++resultado.llamadas;
            resultado.triangulos+=complemento->indices.size()/3;
        }
        return resultado;
    }

    void DrawMatrices(Shader& shader, const Matrices& matrices, const glm::mat4& flower)
    {
        lastDrawCalls = 0;
        lastTriangles = 0;
        const GLint location = glGetUniformLocation(shader.Program, "model");
        for (int i = 0; i < visitanteDatos::BodyCount; ++i)
        {
            const auto cuenta=DibujarPieza(shader,location,i,matrices[i]);
            lastDrawCalls+=cuenta.llamadas;
            lastTriangles+=cuenta.triangulos;
        }
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(flower));
        models[visitanteDatos::Flor]->Draw(shader);
        lastDrawCalls += models[visitanteDatos::Flor]->Meshes().size();
        lastTriangles += models[visitanteDatos::Flor]->TriangleCount();
    }

    struct Sample
    {
        Matrices body;
        glm::mat4 flower;
        bool released;
    };

    void PrepareFlowerAnimation()
    {
        placedFlower = EvaluateHeld(visitanteDatos::ReleaseTime).flower;
        const glm::vec3 position(placedFlower[3]);
        std::cout << "VISITANTE FLOR FIJA: " << position.x << "," << position.y << "," << position.z
            << " contacto_t=" << visitanteDatos::ReleaseTime << std::endl;
    }

    Sample Evaluate(float time) const
    {
        Sample result = EvaluateHeld(time);
        result.released = time >= visitanteDatos::ReleaseTime;
        if (result.released) result.flower = placedFlower;
        return result;
    }

    float TiempoCiclo(double ahora) const
    {
        constexpr float pausaFlor=1.6f, pausaInicial=1.15f;
        const float duracion=visitanteDatos::Duration;
        return visitanteCiclo::IdaYVuelta(reloj.Fase(ahora,2.f*duracion+pausaFlor+pausaInicial),
                                         duracion,pausaFlor).tiempo;
    }
    void ReiniciarCiclo(double ahora) { reloj.Reiniciar(ahora); }

    void DrawAnimation(Shader& shader, float time)
    {
        const Sample sample = Evaluate(time);
        DrawMatrices(shader, sample.body, sample.flower);
    }

    size_t LastDrawCalls() const { return lastDrawCalls; }
    size_t LastTriangles() const { return lastTriangles; }

    void WriteEvidence(std::ostream& stream, float time) const
    {
        const Sample sample = Evaluate(time);
        for (int i = 0; i <= visitanteDatos::BodyCount; ++i)
        {
            const bool flower = i == visitanteDatos::BodyCount;
            const glm::mat4& matrix = flower ? sample.flower : sample.body[i];
            stream << time << "," << (flower ? "flor" : visitanteDatos::parts[i].file) << ","
                << (flower ? (sample.released ? -1 : visitanteDatos::ManoDerecha) : visitanteDatos::parts[i].parent)
                << "," << sample.released;
            for (int row = 0; row < 4; ++row)
                for (int column = 0; column < 4; ++column)
                    stream << "," << matrix[column][row];
            stream << "\n";
        }
    }

    bool ValidateAnimation(const std::vector<Bounds>& obstacles, const Placement& grave,
        const std::vector<UnifiedSegment>& routes) const
    {
        const glm::mat4 inverseGrave = glm::inverse(grave.matrix);
        float smallestClearance = 100, largestStep = 0;
        glm::vec3 previousFlower(Evaluate(0).flower[3]);
        for (int frame = 0; frame <= 270; ++frame)
        {
            const float time = frame * .05f;
            const Sample sample = Evaluate(time);
            if (!ValidateBody(sample.body, obstacles, grave, routes))
            {
                std::cerr << "ERROR VISITANTE: muestra t=" << time << std::endl;
                return false;
            }
            for (const Mesh& mesh : models[visitanteDatos::Flor]->Meshes())
                for (const Vertex& vertex : mesh.vertices)
                {
                    const glm::vec3 world = glm::vec3(sample.flower * glm::vec4(vertex.Position, 1));
                    if (world.y < SupportHeight(world) - .002f)
                    {
                        std::cerr << "ERROR VISITANTE: flor bajo suelo t=" << time << std::endl;
                        return false;
                    }
                    for (const Bounds& obstacle : obstacles)
                        if (world.x > obstacle.min.x && world.x < obstacle.max.x &&
                            world.y > obstacle.min.y && world.y < obstacle.max.y &&
                            world.z > obstacle.min.z && world.z < obstacle.max.z)
                        {
                            std::cerr << "ERROR VISITANTE: flor cruza adorno t=" << time << std::endl;
                            return false;
                        }
                    const glm::vec3 local = glm::vec3(inverseGrave * glm::vec4(world, 1));
                    if (local.x < grave.model->BoundsMin().x || local.x > grave.model->BoundsMax().x ||
                        local.z < grave.model->BoundsMin().z || local.z > grave.model->BoundsMax().z) continue;
                    const float top = TopSurfaceY(*grave.model, local.x, local.z);
                    if (top < grave.model->BoundsMin().y) continue;
                    const glm::vec3 surface = glm::vec3(grave.matrix * glm::vec4(local.x, top, local.z, 1));
                    if (world.y < surface.y - .002f)
                    {
                        std::cerr << "ERROR VISITANTE: flor cruza tumba t=" << time << std::endl;
                        return false;
                    }
                    if (sample.released) smallestClearance = (std::min)(smallestClearance, world.y - surface.y);
                }
            const glm::vec3 flower(sample.flower[3]);
            largestStep = (std::max)(largestStep, glm::length(flower - previousFlower));
            previousFlower = flower;
        }
        float releaseError = 0;
        const auto before = EvaluateHeld(visitanteDatos::ReleaseTime);
        for (int column = 0; column < 4; ++column)
            for (int row = 0; row < 4; ++row)
                releaseError = (std::max)(releaseError, fabs(before.flower[column][row] - placedFlower[column][row]));
        std::cout << "VISITANTE ANIMACION: muestras=271 dt=0.05 sin_intersecciones=1"
            << " flor_despeje_min=" << smallestClearance << " salto_release=" << releaseError
            << " paso_max_origen=" << largestStep << std::endl;
        return smallestClearance >= -.002f && smallestClearance <= .005f && releaseError < .00001f;
    }

    bool ValidateScene(const std::vector<Bounds>& obstacles, const Placement& grave,
        const std::vector<UnifiedSegment>& routes) const
    {
        for (int pose = 0; pose < 4; ++pose)
        {
            const auto matrices = ComposeSupported(visitanteDatos::poses[pose], 0);
            if (!ValidateBody(matrices, obstacles, grave, routes)) return false;
            std::cout << "VISITANTE POSE " << pose << " sin_intersecciones=1" << std::endl;
        }
        return true;
    }

private:
    std::array<std::shared_ptr<Model>, visitanteDatos::PartCount> models;
    glm::mat4 root = glm::mat4(1);
    std::array<std::vector<glm::vec3>,visitanteDatos::BodyCount> colores;
    glm::vec3 escalaCabeza{1.f};
    std::unique_ptr<Mesh> complemento;
    visitanteCiclo::Reloj reloj{.45};
    glm::mat4 placedFlower = glm::mat4(1);
    std::vector<Bounds> supports;
    size_t lastDrawCalls = 0, lastTriangles = 0;

    // Muestreo absoluto y determinista, independiente del numero de cuadros.
    Sample EvaluateHeld(float time) const
    {
        const auto& frames = visitanteDatos::keyframes;
        time = glm::clamp(time, frames.front().time, frames.back().time);
        auto next = std::upper_bound(frames.begin(), frames.end(), time,
            [](float value, const visitanteDatos::KeyFrame& frame) { return value < frame.time; });
        if (next == frames.end()) next = frames.end() - 1;
        const auto& second = *next;
        const auto& first = *(next - 1);
        float fraction = glm::clamp((time - first.time) / (second.time - first.time), 0.f, 1.f);
        fraction = fraction * fraction * (3 - 2 * fraction);
        visitanteDatos::Pose pose;
        pose.rootY = glm::mix(first.pose.rootY, second.pose.rootY, fraction);
        for (int i = 0; i < visitanteDatos::BodyCount; ++i)
        {
            glm::vec3 delta = second.pose.angles[i] - first.pose.angles[i];
            for (int axis = 0; axis < 3; ++axis)
                delta[axis] = glm::mod(delta[axis] + 180.f, 360.f) - 180.f;
            pose.angles[i] = first.pose.angles[i] + fraction * delta;
        }
        const float forward = glm::mix(first.forward, second.forward, fraction);
        const auto matrices = ComposeSupported(pose, forward);
        const glm::quat grip = glm::normalize(glm::slerp(first.flowerRotation, second.flowerRotation, fraction));
        return {matrices, HandFlower(matrices) * glm::mat4_cast(grip), false};
    }

    float SupportHeight(const glm::vec3& world) const
    {
        float height = root[3].y;
        for (const Bounds& platform : supports)
            if (world.x >= platform.min.x && world.x <= platform.max.x &&
                world.z >= platform.min.z && world.z <= platform.max.z)
                height = (std::max)(height, platform.max.y);
        return height;
    }

    Matrices ComposeSupported(visitanteDatos::Pose pose, float forward) const
    {
        const auto matrices = Compose(pose, forward);
        float clearance = 100;
        const int supportParts[] = {visitanteDatos::MusloIzquierdo, visitanteDatos::PiernaIzquierda,
            visitanteDatos::PieIzquierdo, visitanteDatos::MusloDerecho,
            visitanteDatos::PiernaDerecha, visitanteDatos::PieDerecho};
        for (int i : supportParts)
            for (const Mesh& mesh : models[i]->Meshes())
                for (const Vertex& vertex : mesh.vertices)
                {
                    const glm::vec3 world(matrices[i] * glm::vec4(vertex.Position, 1));
                    clearance = (std::min)(clearance, world.y - SupportHeight(world));
                }
        pose.rootY -= clearance;
        return Compose(pose, forward);
    }

    bool ValidateBody(const Matrices& matrices, const std::vector<Bounds>& obstacles,
        const Placement& grave, const std::vector<UnifiedSegment>& routes) const
    {
        const glm::mat4 inverseGrave = glm::inverse(grave.matrix);
        float lowest = 100;
        for (int i = 0; i < visitanteDatos::BodyCount; ++i)
        {
            const Bounds bounds = WorldBounds(*models[i], matrices[i]);
            for (const Bounds& obstacle : obstacles)
                if (UnifiedOverlap3(bounds, obstacle))
                {
                    std::cerr << "ERROR VISITANTE: obstaculo pieza=" << i << std::endl;
                    return false;
                }
            for (const Mesh& mesh : models[i]->Meshes())
                for (const Vertex& vertex : mesh.vertices)
                {
                    const glm::vec3 world = glm::vec3(matrices[i] * glm::vec4(vertex.Position, 1));
                    lowest = (std::min)(lowest, world.y - SupportHeight(world));
                    const glm::vec3 local = glm::vec3(inverseGrave * glm::vec4(world, 1));
                    if (local.x < grave.model->BoundsMin().x || local.x > grave.model->BoundsMax().x ||
                        local.z < grave.model->BoundsMin().z || local.z > grave.model->BoundsMax().z) continue;
                    if (local.y >= grave.model->BoundsMax().y) continue;
                    const float top = TopSurfaceY(*grave.model, local.x, local.z);
                    if (local.y > grave.model->BoundsMin().y + .002f && local.y < top - .002f)
                    {
                        std::cerr << "ERROR VISITANTE: tumba pieza=" << i
                            << " local=" << local.x << "," << local.y << "," << local.z << " top=" << top << std::endl;
                        return false;
                    }
                }
            for (const auto& segment : routes)
            {
                const glm::vec2 delta = segment.b - segment.a;
                const glm::vec2 center = glm::vec2((bounds.min.x + bounds.max.x) * .5f,
                    (bounds.min.z + bounds.max.z) * .5f);
                const float fraction = glm::clamp(glm::dot(center - segment.a, delta) /
                    (std::max)(glm::dot(delta, delta), .000001f), 0.f, 1.f);
                const glm::vec2 nearest = segment.a + fraction * delta;
                const Bounds pedestrian = {glm::vec3(nearest.x - .35f, 0, nearest.y - .35f),
                    glm::vec3(nearest.x + .35f, EYE_HEIGHT, nearest.y + .35f)};
                if (UnifiedOverlap3(bounds, pedestrian))
                {
                    std::cerr << "ERROR VISITANTE: sendero pieza=" << i << std::endl;
                    return false;
                }
            }
        }
        return fabs(lowest) <= .002f;
    }

    bool ValidatePivots() const
    {
        float maximum = 0;
        for (int pose = 0; pose < 4; ++pose)
        {
            const auto matrices = Compose(visitanteDatos::poses[pose]);
            for (int i = 0; i < visitanteDatos::BodyCount; ++i)
                for (int row = 0; row < 4; ++row)
                    for (int column = 0; column < 4; ++column)
                        maximum = (std::max)(maximum, fabs(matrices[i][column][row] -
                            visitanteDatos::reference[pose][i][row * 4 + column]));
        }
        std::cout << "VISITANTE PIVOTES: error_max=" << maximum << std::endl;
        return maximum < .000002f;
    }
};
