#pragma once

// Incluido despues de las definiciones de Placement y los recorridos unificados.
class MixquicPerimeter
{
public:
    static constexpr float frontZ = 30.5f;
    static constexpr float rearZ = -31.55f;
    static constexpr float sideX = 24.55f;
    const float openAngle;

    explicit MixquicPerimeter(bool corrected)
        : openAngle(corrected ? 85.f : 75.f),
          arch(corrected ? "Models/Perimetro_Alan/entrada_arco_mixquic_despejado.obj"
                         : "Models/Perimetro_Alan/entrada_arco_mixquic.obj")
    {}

    bool PasoLibre(glm::vec2 point) const { return !Blocked(point); }

    bool Load()
    {
        for (const Model* model : Models())
            if (!model->IsLoaded()) return Error("falta un modelo del perimetro");
        const float inset = 0.21f;
        for (const float x : {-sideX, sideX})
        {
            AddRun(rearZ + inset, frontZ - inset, x, true);
            AddSolid(Grounded(pillar, {x, 0, rearZ}, glm::vec3(1)));
            AddSolid(Grounded(pillar, {x, 0, frontZ}, glm::vec3(1)));
        }
        AddRun(-sideX + inset, sideX - inset, rearZ, false);
        AddRun(-sideX + inset, -3.85f, frontZ, false);
        AddRun(3.85f, sideX - inset, frontZ, false);

        const Placement entry = Grounded(arch, {0, 0, frontZ}, {entryWidthScale, 1.2f, 1});
        pieces.push_back(entry);
        Bounds jamb = entry.bounds;
        jamb.max.x = -entryClearHalfWidth;
        solids.push_back(jamb);
        jamb.min.x = entryClearHalfWidth;
        jamb.max.x = entry.bounds.max.x;
        solids.push_back(jamb);
        for (const Mesh& mesh : arch.Meshes())
            for (const Vertex& vertex : mesh.vertices)
            {
                const glm::vec3 p = glm::vec3(entry.matrix * glm::vec4(vertex.Position, 1));
                if (p.y < 1.85f && std::abs(p.x) < entryClearHalfWidth - 0.001f)
                    return Error("el arco invade el paso peatonal");
            }
        size_t triangles = left.TriangleCount() + right.TriangleCount();
        for (const auto& p : pieces) triangles += p.model->TriangleCount();
        std::cout << "PERIMETRO: ejes=" << 2 * sideX << "x" << frontZ - rearZ
                  << " modulos=" << segments << " remates=" << endPieces << " pilares=4"
                  << " instancias=" << pieces.size() + 2 << " triangulos_totales=" << triangles
                  << " puerta_Z=" << frontZ << " despeje_arco=" << 2 * entryClearHalfWidth
                  << " apertura=" << openAngle << std::endl;
        return true;
    }

    bool ValidateLayout(const std::vector<Bounds>& scene, const Placement& paving) const
    {
        const Bounds swing = {{-hinge - 0.13f, 0, frontZ - leafReach},
                              {hinge + 0.13f, 2, frontZ + 0.13f}};
        for (const Bounds& obstacle : scene)
        {
            if (OverlapXZ(swing, obstacle)) return Error("barrido del porton invade la escena");
            for (const Bounds& solid : solids)
                if (OverlapXZ(solid, obstacle)) return Error("muro invade la escena");
        }
        for (const Placement& p : pieces)
            if (p.bounds.min.x < -25.001f || p.bounds.max.x > 25.001f ||
                p.bounds.min.z < -32.001f || p.bounds.max.z > 32.001f)
                return Error("muro fuera de la plataforma");

        for (const Mesh& mesh : paving.model->Meshes())
            for (size_t i = 0; i < mesh.indices.size(); i += 3)
            {
                glm::vec3 a = glm::vec3(paving.matrix * glm::vec4(mesh.vertices[mesh.indices[i]].Position, 1));
                glm::vec3 b = glm::vec3(paving.matrix * glm::vec4(mesh.vertices[mesh.indices[i + 1]].Position, 1));
                glm::vec3 c = glm::vec3(paving.matrix * glm::vec4(mesh.vertices[mesh.indices[i + 2]].Position, 1));
                const Bounds tile = {glm::min(a, glm::min(b, c)), glm::max(a, glm::max(b, c))};
                for (const Bounds& solid : solids)
                    if (OverlapXZ(tile, solid)) return Error("muro invade el pavimento");
            }

        size_t samples = 0;
        for (const UnifiedSegment& route : unifiedExpandedSegments)
        {
            const int steps = static_cast<int>(std::ceil(glm::length(route.b - route.a) / 0.05f));
            for (int i = 0; i <= steps; ++i)
            {
                if (Blocked(glm::mix(route.a, route.b, float(i) / (std::max)(1, steps))))
                    return Error("muro o rejas abiertas bloquean una ruta");
                ++samples;
            }
        }
        std::cout << "PERIMETRO RUTAS: " << samples
                  << " muestras libres; sin solapes con suelo pavimentado, tumbas, adornos, templo u ofrenda." << std::endl;
        return true;
    }

    void AddBudget(std::vector<Model*>& loaded, std::vector<Placement>& drawn)
    {
        for (Model* model : Models()) loaded.push_back(model);
        drawn.insert(drawn.end(), pieces.begin(), pieces.end());
        drawn.push_back(Leaf(true));
        drawn.push_back(Leaf(false));
    }

    void Draw(Shader& shader, const glm::mat4& clip)
    {
        const glm::mat4 rows = glm::transpose(clip);
        const glm::vec4 planes[] = {rows[3] + rows[0], rows[3] - rows[0], rows[3] + rows[1],
                                    rows[3] - rows[1], rows[3] + rows[2], rows[3] - rows[2]};
        for (const Placement& p : pieces)
            if (Visible(p.bounds, planes)) DrawPlacement(p, shader);
        for (const bool isLeft : {true, false})
        {
            const Placement leaf = Leaf(isLeft);
            if (Visible(leaf.bounds, planes)) DrawPlacement(leaf, shader);
        }
    }

    void Toggle()
    {
        wantOpen = !wantOpen;
        std::cout << "PORTON R: " << (wantOpen ? "abrir" : "cerrar") << std::endl;
    }

    void Advance(float seconds, glm::vec2 walker)
    {
        if (!wantOpen && walker.y <= frontZ + cameraRadius + 0.04f &&
            (glm::length(walker - glm::vec2(-hinge, frontZ)) < leafReach + cameraRadius ||
             glm::length(walker - glm::vec2(hinge, frontZ)) < leafReach + cameraRadius))
        {
            wantOpen = true;
            std::cout << "PORTON: cierre cancelado, acceso ocupado." << std::endl;
        }
        const float limit = glm::clamp(seconds, 0.0f, 0.05f) * 60.0f;
        const float delta = glm::clamp((wantOpen ? openAngle : 0.0f) - angle, -limit, limit);
        // Comprueba cada posicion aceptada de la hoja. El radio coincide con
        // el desplazamiento peatonal para permitir abrir desde el limite.
        const int steps = (std::max)(1, static_cast<int>(std::ceil(2.0f * std::abs(delta))));
        for (int i = 0; i < steps; ++i)
        {
            const float next = glm::clamp(angle + delta / steps, 0.0f, openAngle);
            if (HitsLeaf(walker, true, next, cameraRadius) ||
                HitsLeaf(walker, false, next, cameraRadius))
                break;
            angle = next;
        }
    }

    void SetCaptureAngle(float degrees)
    {
        angle = glm::clamp(degrees, 0.0f, openAngle);
        wantOpen = angle > 0.0f;
    }

    float Angle() const { return angle; }

    glm::vec2 ResolveMotion(glm::vec2 from, glm::vec2 to) const
    {
        const glm::vec2 movement = to - from;
        const int steps = (std::max)(1, static_cast<int>(std::ceil(glm::length(movement) / 0.05f)));
        const glm::vec2 step = movement / static_cast<float>(steps);
        for (int i = 0; i < steps; ++i)
        {
            const glm::vec2 alongX(from.x + step.x, from.y);
            if (!Blocked(alongX)) from.x = alongX.x;
            const glm::vec2 alongZ(from.x, from.y + step.y);
            if (!Blocked(alongZ)) from.y = alongZ.y;
        }
        return from;
    }

private:
    static constexpr float cameraRadius = 0.35f;
    static constexpr float entryWidthScale = 2.2f;
    static constexpr float entryClearHalfWidth = 1.03f * entryWidthScale;
    static constexpr float hinge = 1.084f * entryWidthScale;
    static constexpr float leafReach = 1.082f * entryWidthScale + 0.04f;
    Model segment{"Models/Perimetro_Alan/muro_panteon_tramo.obj"};
    Model pillar{"Models/Perimetro_Alan/muro_panteon_pilar.obj"};
    Model arch;
    Model left{"Models/Perimetro_Alan/reja_puerta_izq.obj"};
    Model right{"Models/Perimetro_Alan/reja_puerta_der.obj"};
    std::vector<Placement> pieces;
    std::vector<Bounds> solids;
    size_t segments = 0, endPieces = 0;
    float angle = openAngle;
    bool wantOpen = true;

    std::array<Model*, 5> Models() { return {{&segment, &pillar, &arch, &left, &right}}; }

    static bool Error(const char* text)
    {
        std::cerr << "ERROR PERIMETRO: " << text << std::endl;
        return false;
    }

    void AddSolid(const Placement& piece)
    {
        pieces.push_back(piece);
        solids.push_back(piece.bounds);
    }

    void AddRun(float start, float end, float fixed, bool alongZ)
    {
        while (end - start > 0.001f)
        {
            const float length = (std::min)(3.0f, end - start);
            const float center = start + length * 0.5f;
            const glm::vec3 position = alongZ ? glm::vec3(fixed, 0, center) : glm::vec3(center, 0, fixed);
            AddSolid(Grounded(segment, position, {length / 3.0f, 1, 1}, alongZ ? 90.0f : 0.0f));
            ++segments;
            if (length < 2.999f) ++endPieces;
            start += length;
        }
    }

    Placement Leaf(bool isLeft)
    {
        Model& model = isLeft ? left : right;
        glm::mat4 matrix = glm::translate(glm::mat4(1), {isLeft ? -hinge : hinge, 0, frontZ});
        matrix = glm::rotate(matrix, glm::radians(isLeft ? angle : -angle), {0, 1, 0});
        matrix = glm::scale(matrix, {entryWidthScale, 1.12f, 1});
        return {&model, matrix, WorldBounds(model, matrix)};
    }

    static bool Visible(const Bounds& bounds, const glm::vec4 (&planes)[6])
    {
        for (const glm::vec4& plane : planes)
        {
            const glm::vec3 farCorner(plane.x >= 0 ? bounds.max.x : bounds.min.x,
                                      plane.y >= 0 ? bounds.max.y : bounds.min.y,
                                      plane.z >= 0 ? bounds.max.z : bounds.min.z);
            if (glm::dot(plane, glm::vec4(farCorner, 1)) < 0.0f) return false;
        }
        return true;
    }

    static bool HitsBox(glm::vec2 p, glm::vec2 minimum, glm::vec2 maximum, float radius)
    {
        const glm::vec2 gap = p - glm::clamp(p, minimum, maximum);
        return glm::dot(gap, gap) < radius * radius;
    }

    bool HitsLeaf(glm::vec2 point, bool isLeft, float degrees, float radius) const
    {
        const Model& model = isLeft ? left : right;
        const glm::vec2 relative = point - glm::vec2(isLeft ? -hinge : hinge, frontZ);
        const float theta = glm::radians(isLeft ? degrees : -degrees);
        const float c = std::cos(theta), s = std::sin(theta);
        const glm::vec2 local(c * relative.x - s * relative.y, s * relative.x + c * relative.y);
        return HitsBox(local, {model.BoundsMin().x * entryWidthScale, model.BoundsMin().z},
                       {model.BoundsMax().x * entryWidthScale, model.BoundsMax().z}, radius);
    }

    bool Blocked(glm::vec2 point) const
    {
        for (const Bounds& solid : solids)
            if (HitsBox(point, {solid.min.x, solid.min.z}, {solid.max.x, solid.max.z}, cameraRadius)) return true;
        return HitsLeaf(point, true, angle, cameraRadius) || HitsLeaf(point, false, angle, cameraRadius);
    }
};
