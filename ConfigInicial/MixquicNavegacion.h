#pragma once

#include "MixquicNavegacionDatos.h"

namespace navegacion4e
{
inline bool Retirada(size_t index)
{
    return std::find(std::begin(tumbasRetiradas), std::end(tumbasRetiradas), static_cast<int>(index))
        != std::end(tumbasRetiradas);
}

inline bool Reducir(const std::vector<Placement>& graves, std::vector<Placement>& visible,
    std::vector<Placement>& groundProps, std::vector<AttachedProp>& attached,
    std::vector<Placement>& allProps, std::vector<Surface>& surfaces, const Model& paving)
{
    if (graves.size() != 77 || groundProps.size() != 297 || surfaces.size() != 79) return false;
    visible.clear();
    for (size_t i = 0; i < graves.size(); ++i)
        if (!Retirada(i)) visible.push_back(graves[i]);
    std::vector<Surface> keptSurfaces;
    for (size_t i = 0; i < surfaces.size(); ++i)
        if (i < 2 || i == 78 || !Retirada(i - 2)) keptSurfaces.push_back(surfaces[i]);
    surfaces.swap(keptSurfaces);
    std::vector<Placement> keptProps;
    for (size_t i = 0; i < groundProps.size(); ++i)
        if (std::find(std::begin(adornosSueloRetirados), std::end(adornosSueloRetirados), static_cast<int>(i)) ==
            std::end(adornosSueloRetirados)) keptProps.push_back(groundProps[i]);
    groundProps.swap(keptProps);
    attached.erase(std::remove_if(attached.begin(), attached.end(),
        [](const AttachedProp& item) { return Retirada(item.owner); }), attached.end());
    allProps = groundProps;
    for (const auto& item : attached) allProps.push_back(item.item);
    for (const Placement& item : groundProps)
    {
        const float offset = item.model->BoundsMax().y - item.model->BoundsMin().y < .01f ? .002f : 0;
        for (int x = 0; x < 3; ++x)
            for (int z = 0; z < 3; ++z)
            {
                const float px = glm::mix(item.bounds.min.x, item.bounds.max.x, x * .5f);
                const float pz = glm::mix(item.bounds.min.z, item.bounds.max.z, z * .5f);
                if (fabs(item.bounds.min.y - UnifiedSupportPoint(px,pz,surfaces,paving) - offset) > .0025f)
                {
                    std::cerr << "ERROR 4E: adorno sin apoyo en " << px << "," << pz << std::endl;
                    return false;
                }
            }
    }
    return visible.size() == 62 && allProps.size() == adornos62 && surfaces.size() == 64;
}

class Navegacion
{
public:
    static constexpr float radio = .35f;
    static constexpr float radioVisitante = .34f;
    std::vector<glm::vec2> visitantes;
    Bounds iglesia;

    void Agregar(const Bounds& obstacle)
    {
        if (obstacle.max.y > .09f && obstacle.min.y < EYE_HEIGHT + radio) solidos.push_back(obstacle);
    }

    static bool Toca(glm::vec2 p, const Bounds& b)
    {
        const glm::vec2 delta = p - glm::clamp(p, glm::vec2(b.min.x,b.min.z), glm::vec2(b.max.x,b.max.z));
        return glm::dot(delta,delta) < radio*radio;
    }

    bool Libre(glm::vec2 p, const MixquicPerimeter* perimeter) const
    {
        if (Toca(p, iglesia) || (perimeter && !perimeter->PasoLibre(p))) return false;
        for (const auto& box : solidos)
            if (Toca(p,box)) return false;
        return true;
    }

    glm::vec2 Desplazar(glm::vec2 from, glm::vec2 to, const MixquicPerimeter* perimeter) const
    {
        const glm::vec2 travel = to - from;
        const int steps = (std::max)(1,static_cast<int>(std::ceil(glm::length(travel)/.05f)));
        const glm::vec2 step = travel/static_cast<float>(steps);
        const auto allowed = [&](glm::vec2 candidate, glm::vec2 previous) {
            if (!Libre(candidate,perimeter)) return false;
            const float limit = (radio+radioVisitante)*(radio+radioVisitante);
            for (glm::vec2 actor : visitantes)
            {
                const glm::vec2 current = candidate-actor, before = previous-actor;
                const float distance = glm::dot(current,current);
                if (distance < limit && distance <= glm::dot(before,before)) return false;
            }
            return true;
        };
        for (int i=0; i<steps; ++i)
        {
            const glm::vec2 x(from.x+step.x,from.y);
            if (allowed(x,from)) from=x;
            const glm::vec2 z(from.x,from.y+step.y);
            if (allowed(z,from)) from=z;
        }
        return from;
    }

    bool ValidarRutas(bool reducida, const MixquicPerimeter& perimeter) const
    {
        // Envolvente conservadora del carril y los cuatro puestos fijos.
        const Bounds actores[] = {
            {{9.86f,0,5.76f},{10.54f,2,6.44f}},{{7.16f,0,-6.04f},{7.84f,2,-5.36f}},
            {{-10.49f,0,-3.04f},{-9.81f,2,-2.36f}},{{-7.94f,0,11.96f},{-7.26f,2,12.64f}},
            {{5.36f,0,16.89f},{9.24f,2,17.57f}}
        };
        const auto& plan = reducida ? rutas62 : rutas77;
        size_t samples=0;
        for (const auto& route : plan)
            for (size_t i=1; i<route.puntos.size(); ++i)
            {
                const auto a=route.puntos[i-1], b=route.puntos[i];
                const int steps=(std::max)(1,static_cast<int>(std::ceil(glm::length(b-a)/.05f)));
                for (int j=0; j<=steps; ++j)
                {
                    const auto p=glm::mix(a,b,j/static_cast<float>(steps));
                    bool free=Libre(p,&perimeter);
                    for (const auto& actor : actores) free=free && !Toca(p,actor);
                    if (!free)
                    {
                        std::cerr << "ERROR 4E: ruta G" << route.destino << " en " << p.x << "," << p.y << std::endl;
                        return false;
                    }
                    ++samples;
                }
            }
        std::cout << "NAVEGACION 4E: destinos=" << plan.size()-1 << " alumbrada=1 muestras=" << samples
            << " radio=0.35 personajes_envolvente=1" << std::endl;
        return true;
    }

private:
    std::vector<Bounds> solidos;
};
}
