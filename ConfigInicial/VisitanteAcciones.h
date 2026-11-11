#pragma once

namespace visitanteAcciones
{
using visitanteDatos::Pose;
enum class Gesto { Veladora, Oracion, Caminar, Rodillas };
struct Clave { float tiempo; Pose pose; float avance; };
struct Toma { const char* nombre; float tiempo; };
struct Pista
{
    Gesto gesto;
    const char* nombre;
    size_t tumba;
    glm::vec3 raiz;
    float giro;
    glm::vec3 camara, objetivo;
    std::vector<Clave> claves;
    std::vector<Toma> tomas;
};

#include "VisitanteAccionesDatos.inl"

inline const Pista* BuscarDemostracion(const std::string& argumento)
{
    const std::string prefijo = "--demo-personaje=";
    if (argumento.compare(0, prefijo.size(), prefijo) != 0) return nullptr;
    const auto nombre = argumento.substr(prefijo.size());
    for (const Pista* pista : pistas)
        if (nombre == pista->nombre) return pista;
    return nullptr;
}

inline float Suavizar(float t)
{
    t = glm::clamp(t, 0.f, 1.f);
    return t * t * (3.f - 2.f * t);
}

inline Clave Interpolar(const std::vector<Clave>& claves, float tiempo)
{
    tiempo = glm::clamp(tiempo, claves.front().tiempo, claves.back().tiempo);
    auto siguiente = std::upper_bound(claves.begin(), claves.end(), tiempo,
        [](float t, const Clave& clave) { return t < clave.tiempo; });
    if (siguiente == claves.end()) --siguiente;
    const Clave& a = *(siguiente - 1);
    const Clave& b = *siguiente;
    const float u = Suavizar((tiempo - a.tiempo) / (b.tiempo - a.tiempo));
    Clave resultado{tiempo, a.pose, glm::mix(a.avance, b.avance, u)};
    resultado.pose.rootY = glm::mix(a.pose.rootY, b.pose.rootY, u);
    for (int i = 0; i < visitanteDatos::BodyCount; ++i)
    {
        const glm::vec3 delta = glm::mod(b.pose.angles[i] - a.pose.angles[i] + glm::vec3(180), glm::vec3(360)) - glm::vec3(180);
        resultado.pose.angles[i] += u * delta;
    }
    return resultado;
}

inline void Paso(Pose& pose, int muslo, int pierna, int pie, float frente, float elevacion)
{
    const float abajo = .810f + pose.rootY - elevacion;
    const float a = .435f, b = .375f;
    const float coseno = (abajo * abajo + frente * frente - a * a - b * b) / (2.f * a * b);
    const float rodilla = acos(glm::clamp(coseno, -1.f, 1.f));
    const float cadera = atan2(-frente, abajo) - atan2(b * sin(rodilla), a + b * cos(rodilla));
    pose.angles[muslo].x = glm::degrees(cadera);
    pose.angles[pierna].x = glm::degrees(rodilla);
    pose.angles[pie].x = -glm::degrees(cadera + rodilla);
}

inline void Triangulo(std::vector<Vertex>& vertices, std::vector<GLuint>& indices,
    const glm::vec3& a, const glm::vec3& b, const glm::vec3& c)
{
    const glm::vec3 normal = glm::normalize(glm::cross(b - a, c - a));
    for (const auto& point : {a, b, c})
    {
        indices.push_back(static_cast<GLuint>(vertices.size()));
        vertices.push_back({point, normal, glm::vec2(0)});
    }
}

inline std::unique_ptr<Mesh> CrearCerillo()
{
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    const glm::vec3 corners[] = {
        {-.004f,0,-.004f},{.004f,0,-.004f},{.004f,0,.004f},{-.004f,0,.004f},
        {-.004f,-.11f,-.004f},{.004f,-.11f,-.004f},{.004f,-.11f,.004f},{-.004f,-.11f,.004f}
    };
    const int faces[][4] = {{0,3,2,1},{4,5,6,7},{0,1,5,4},{1,2,6,5},{2,3,7,6},{3,0,4,7}};
    for (const auto& f : faces)
    {
        Triangulo(vertices, indices, corners[f[0]], corners[f[1]], corners[f[2]]);
        Triangulo(vertices, indices, corners[f[0]], corners[f[2]], corners[f[3]]);
    }
    return std::unique_ptr<Mesh>(new Mesh(vertices, indices, {}, glm::vec3(.64f,.35f,.12f)));
}

inline std::unique_ptr<Mesh> CrearLlama()
{
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    const auto ring = [](int side, float y, float radius) {
        const float angle = 6.283185307f * side / 8.f;
        return glm::vec3(radius * cos(angle), y, radius * sin(angle));
    };
    for (int i = 0; i < 8; ++i)
    {
        const glm::vec3 a = ring(i, 0, .006f), b = ring(i+1, 0, .006f);
        const glm::vec3 c = ring(i, .027f, .017f), d = ring(i+1, .027f, .017f);
        Triangulo(vertices, indices, a, c, d);
        Triangulo(vertices, indices, a, d, b);
        Triangulo(vertices, indices, c, glm::vec3(.006f,.078f,0), d);
        Triangulo(vertices, indices, a, b, glm::vec3(0));
    }
    return std::unique_ptr<Mesh>(new Mesh(vertices, indices, {}, glm::vec3(1,.44f,.085f),
        glm::vec3(1.7f,.68f,.11f)));
}

struct Cuenta { size_t llamadas = 0, triangulos = 0; };

class Accion
{
public:
    Accion(const Pista& definition, const VisitanteAnimado& loaded,
        const std::vector<Surface>& sceneSurfaces)
        : pista(definition), rig(loaded.CompartirPiezas()), surfaces(sceneSurfaces)
    {
        rig.Place(pista.raiz, pista.giro, surfaces);
        if (pista.gesto == Gesto::Veladora)
        {
            cerillo = CrearCerillo();
            llama = CrearLlama();
        }
    }

    VisitanteAnimado::Matrices Evaluar(float t)
    {
        const Clave clave = Interpolar(pista.claves, t);
        if (pista.gesto == Gesto::Caminar) return EvaluarCaminata(clave);
        return rig.Articular(clave.pose, clave.avance);
    }

    bool Comprobar(const std::vector<Bounds>& obstacles, const Placement& grave,
        const std::vector<UnifiedSegment>& routes, const Model& paving)
    {
        const bool walking = pista.gesto == Gesto::Caminar;
        if (walking && !ComprobarSendero(routes, paving)) return false;
        const std::vector<UnifiedSegment> emptyRoutes;
        const auto& pedestrianRoutes = walking ? emptyRoutes : routes;
        const int samples = static_cast<int>(std::ceil(pista.claves.back().tiempo / .05f));
        for (int i = 0; i <= samples; ++i)
        {
            const float t = (std::min)(i * .05f, pista.claves.back().tiempo);
            if (!rig.ComprobarArticulacion(Evaluar(t), obstacles, grave, pedestrianRoutes))
            {
                std::cerr << "ERROR ACCION " << pista.nombre << " t=" << t << std::endl;
                return false;
            }
        }
        const auto initial = Evaluar(0);
        Evaluar(pista.claves.back().tiempo);
        const auto restarted = Evaluar(0);
        for (int i = 0; i < visitanteDatos::BodyCount; ++i)
            if (glm::length(initial[i][3] - restarted[i][3]) > .00001f) return false;
        if (pista.gesto == Gesto::Veladora)
        {
            const glm::vec3 tip(Tip(Evaluar(instanteEncendido)));
            const float separation = glm::length(tip - mecha);
            if (separation > .035f || Encendida(0) || !Encendida(pista.claves.back().tiempo)) return false;
            std::cout << "VISITANTE VELADORA: encendido_t=" << instanteEncendido
                << " distancia_cerillo_mecha=" << separation << " luces_puntuales_extra=0" << std::endl;
        }
        std::cout << "VISITANTE ACCION: " << pista.nombre << " G" << pista.tumba + 1
            << " muestras=" << samples + 1 << " apoyo=OK reinicio=OK" << std::endl;
        return true;
    }

    Cuenta Dibujar(Shader& shader, float time)
    {
        const auto matrices = Evaluar(time);
        Cuenta cuenta;
        const GLint uniform = glGetUniformLocation(shader.Program, "model");
        const auto model = [&](int index, const glm::mat4& matrix) {
            auto& piece = rig.Pieza(index);
            glUniformMatrix4fv(uniform, 1, GL_FALSE, glm::value_ptr(matrix));
            piece.Draw(shader);
            cuenta.llamadas += piece.Meshes().size();
            cuenta.triangulos += piece.TriangleCount();
        };
        const auto mesh = [&](Mesh& piece, const glm::mat4& matrix) {
            glUniformMatrix4fv(uniform, 1, GL_FALSE, glm::value_ptr(matrix));
            piece.Draw(shader);
            ++cuenta.llamadas;
            cuenta.triangulos += piece.indices.size() / 3;
        };
        for (int i = 0; i < visitanteDatos::BodyCount; ++i) model(i, matrices[i]);
        if (pista.gesto == Gesto::Veladora)
        {
            model(visitanteDatos::Veladora, glm::translate(glm::mat4(1), baseVeladora) * glm::mat4_cast(giroVeladora));
            mesh(*cerillo, rig.HandFlower(matrices));
            if (time >= 4.9f && time < 7.3f)
                mesh(*llama, glm::scale(glm::translate(glm::mat4(1), Tip(matrices)), glm::vec3(.42f)));
            if (Encendida(time)) mesh(*llama, glm::translate(glm::mat4(1), mecha));
        }
        return cuenta;
    }

    void Evidencia(std::ostream& stream, float tiempo)
    {
        const auto matrices = Evaluar(tiempo);
        for (int i = 0; i < visitanteDatos::BodyCount; ++i)
        {
            stream << tiempo << "," << visitanteDatos::parts[i].file << "," << visitanteDatos::parts[i].parent;
            for (int row = 0; row < 4; ++row)
                for (int column = 0; column < 4; ++column) stream << "," << matrices[i][column][row];
            stream << "\n";
        }
    }

    const Pista& pista;

private:
    VisitanteAnimado rig;
    const std::vector<Surface>& surfaces;
    std::unique_ptr<Mesh> cerillo, llama;

    static bool Encendida(float t) { return t >= instanteEncendido; }
    glm::vec3 Tip(const VisitanteAnimado::Matrices& matrices) const
    {
        return glm::vec3(rig.HandFlower(matrices) * glm::vec4(0,-.11f,0,1));
    }

    VisitanteAnimado::Matrices EvaluarCaminata(const Clave& clave)
    {
        using namespace visitanteDatos;
        const float travel = pista.claves.back().avance;
        const float stride = .8f;
        const float turn = glm::clamp((clave.tiempo - pista.claves[2].tiempo) /
            (pista.claves[3].tiempo - pista.claves[2].tiempo), 0.f, 1.f);
        const float strength = (std::min)(Suavizar(clave.avance / .28f), Suavizar((travel - clave.avance) / .28f));
        const float turnStep = sin(6.283185307f * turn);
        Pose pose = poses[0];
        pose.rootY = -.036f * strength - .018f * sin(3.141592654f * turn);
        const auto foot = [&](float offset, int thigh, int knee, int ankle, float pivot) {
            const float phase = glm::fract(clave.avance / stride + offset);
            const float swing = glm::clamp((phase - .5f) * 2.f, 0.f, 1.f);
            const float z = phase < .5f ? stride * (.25f - phase) : stride * (.5f * Suavizar(swing) - .25f);
            const float lift = .12f * sin(3.141592654f * swing) * strength + .065f * (std::max)(0.f, pivot);
            Paso(pose, thigh, knee, ankle, z * strength, lift);
        };
        foot(0, MusloIzquierdo, PiernaIzquierda, PieIzquierdo, turnStep);
        foot(.5f, MusloDerecho, PiernaDerecha, PieDerecho, -turnStep);
        const float swing = 22.f * cos(6.283185307f * clave.avance / stride) * strength;
        pose.angles[BrazoIzquierdo].x = swing;
        pose.angles[BrazoDerecho].x = -swing;
        pose.angles[AntebrazoIzquierdo].x -= .4f * fabs(swing);
        pose.angles[AntebrazoDerecho].x -= .4f * fabs(swing);
        pose.angles[Torso].x = 3.f * strength;
        rig.Place(pista.raiz + glm::vec3(clave.avance, 0, 0), pista.giro + 90.f * Suavizar(turn), surfaces);
        return rig.Articular(pose, 0);
    }

    bool ComprobarSendero(const std::vector<UnifiedSegment>& routes, const Model& paving) const
    {
        const float x0 = pista.raiz.x, x1 = x0 + pista.claves.back().avance, z = pista.raiz.z;
        bool found = false;
        for (const auto& route : routes)
            if (fabs(route.a.y - route.b.y) < .001f && fabs(route.a.y - z) <= .3f &&
                (std::min)(route.a.x, route.b.x) <= x0 && (std::max)(route.a.x, route.b.x) >= x1)
                found = true;
        if (!found) return false;
        for (int x = 0; x <= 72; ++x)
            for (float offset : {-.22f, 0.f, .16f})
                if (fabs(TopSurfaceY(paving, glm::mix(x0 - .2f, x1 + .2f, x / 72.f), z + offset)
                    - pista.raiz.y) > .002f) return false;
        std::cout << "VISITANTE CAMINO: ruta_real=1 apoyo_y=" << pista.raiz.y << " distancia=" << x1 - x0
            << " desde=" << x0 << "," << z << " hasta=" << x1 << "," << z << std::endl;
        return true;
    }
};
}
