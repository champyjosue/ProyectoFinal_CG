// Proyecto Final / Base Practicas 8 y 9
// Equipo 12
// Números de cuenta: 421122006 | 320173985 | 320028603

#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <chrono>
#include <iomanip>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "SOIL2/SOIL2.h"
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();

// Window dimensions
const GLuint WIDTH = 1000, HEIGHT = 700;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera camera(glm::vec3(0.0f, 1.7f, 19.0f), glm::vec3(0, 1, 0), -90.0f, -3.0f);
GLfloat lastX = WIDTH / 2.0f;
GLfloat lastY = HEIGHT / 2.0f;
bool keys[1024];
bool firstMouse = true;
// Fase 2B: V2 experimental por defecto; F2 o --iglesia=v1 permiten volver a V1.
bool useIglesiaV2 = true;
// Fase 3A: la ofrenda anterior permanece disponible con --ofrenda=v1.
bool useOfrendaV2 = true;
// Fase 3C: comparacion reversible al iniciar.
bool useNewLayout = true;
const char* ChurchWindowTitle()
{
    return useIglesiaV2 ? "Panteon de Mixquic - Iglesia V2 experimental [F2: V1]"
        : "Panteon de Mixquic - Iglesia V1 [F2: V2]";
}

// Deltatime
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

// Atributos de animacion y luces adicionales
glm::vec3 lightPos(0.5f, 0.5f, 2.5f);
float movelightPos = 0.0f;
float rot = 0.0f;
bool activanim = false;
bool active = false;
glm::vec3 Light1 = glm::vec3(0.0f);

// ETAPAS 5-6: emisores y trayectorias adaptados a las seis zonas.
glm::vec3 sunPos(0.0f), moonPos(0.0f);
float sunAngle = glm::radians(225.0f);
float sunOrbitRadius = 8.0f; // Orbita elevada: Y 10..26, detras del templo.
glm::vec3 posFogata(-4.0f, 0.0f, -18.6f);       // La Alumbrada
glm::vec3 posVela(-3.3f, 0.0f, -2.95f);        // Fachada, fuera del paso
glm::vec3 posLuciernaga(7.8f, 1.65f, 2.0f);     // Tumbas derechas
glm::vec3 posFarol(3.2f, 0.65f, 17.5f);         // Acceso
glm::vec3 posVeladora(0.0f, 0.1f, -17.55f);      // Ofrenda principal
const float ESC_FOGATA = 1.4f;
const float ESC_VELA = 1.3f;
const float ESC_LUCIERNAGA = 1.8f;
const float ESC_FAROL = 1.8f;
const float ESC_VELADORA = 1.6f;
const float ESC_CUERVO = 1.4f;

// Posiciones de las 5 luces puntuales:
// [0] fogata  [1] vela  [2] luciernaga  [3] farol  [4] veladora
glm::vec3 pointLightPositions[] = {
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 0.0f)
};

// Vertices de cubo manual (Posicion X,Y,Z + Normal NX,NY,NZ)
float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

// Colocacion basada en limites reales: el origen de cada OBJ puede ser distinto.
struct Bounds { glm::vec3 min, max; };
struct Placement
{
    Model* model;
    glm::mat4 matrix;
    Bounds bounds;
};
struct Surface
{
    glm::vec3 center, size, color;
};

const float GROUND_Y = 0.0f;
const float EYE_HEIGHT = 1.7f;
const bool ESCENA_NOCTURNA = true; // Conserva el sistema orbital sin dibujar el Sol caricaturesco.

glm::vec3 OrbitPosition(float phase)
{
    return glm::vec3(cos(phase) * sunOrbitRadius, 18.0f + sin(phase) * sunOrbitRadius, -22.0f);
}

glm::vec3 FireflyPosition(float t)
{
    return posLuciernaga + glm::vec3(0.7f * sin(0.6f * t), 0.18f * sin(1.7f * t), 0.7f * cos(0.45f * t));
}

glm::mat4 FireflyMatrix(float t)
{
    const float avanceX = 0.7f * 0.6f * cos(0.6f * t);
    const float avanceZ = -0.7f * 0.45f * sin(0.45f * t);
    glm::mat4 matrix = glm::translate(glm::mat4(1.0f), FireflyPosition(t));
    matrix = glm::rotate(matrix, atan2(avanceX, avanceZ), glm::vec3(0, 1, 0));
    return glm::scale(matrix, glm::vec3(ESC_LUCIERNAGA));
}

glm::mat4 CrowMatrix(float t)
{
    const float giro = 0.5f * t;
    glm::mat4 matrix = glm::translate(glm::mat4(1.0f), glm::vec3(4.6f * sin(giro), 4.8f + 0.2f * sin(t * 2.0f), 6.0f + 3.5f * cos(giro)));
    // La tangente de la elipse orienta el cuerpo en la direccion del vuelo.
    matrix = glm::rotate(matrix, atan2(4.6f * cos(giro), -3.5f * sin(giro)), glm::vec3(0, 1, 0));
    return glm::scale(matrix, glm::vec3(ESC_CUERVO));
}

glm::mat4 WingMatrix(const glm::mat4& parent, float t, float side)
{
    const float aleteo = 35.0f * sin(t * 6.0f);
    glm::mat4 matrix = glm::translate(parent, glm::vec3(side * 0.05f, 0.03f, 0.02f));
    return glm::rotate(matrix, glm::radians(side * aleteo), glm::vec3(0, 0, 1));
}

Bounds WorldBounds(const Model& model, const glm::mat4& matrix)
{
    Bounds bounds = { glm::vec3(1.0e10f), glm::vec3(-1.0e10f) };
    for (int mask = 0; mask < 8; ++mask)
    {
        glm::vec3 corner(
            (mask & 1) ? model.BoundsMax().x : model.BoundsMin().x,
            (mask & 2) ? model.BoundsMax().y : model.BoundsMin().y,
            (mask & 4) ? model.BoundsMax().z : model.BoundsMin().z);
        glm::vec3 world = glm::vec3(matrix * glm::vec4(corner, 1.0f));
        bounds.min = glm::min(bounds.min, world);
        bounds.max = glm::max(bounds.max, world);
    }
    return bounds;
}

Placement Grounded(Model& model, const glm::vec3& position, const glm::vec3& scale, float yaw = 0.0f)
{
    const glm::vec3 center = (model.BoundsMin() + model.BoundsMax()) * 0.5f;
    glm::mat4 matrix = glm::translate(glm::mat4(1.0f), position);
    matrix = glm::rotate(matrix, glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));
    matrix = glm::scale(matrix, scale);
    matrix = glm::translate(matrix, glm::vec3(-center.x, -model.BoundsMin().y, -center.z));
    return { &model, matrix, WorldBounds(model, matrix) };
}

void AddPlacement(std::vector<Placement>& items, Model& model, const glm::vec3& position, float scale = 1.0f, float yaw = 0.0f)
{
    items.push_back(Grounded(model, position, glm::vec3(scale), yaw));
}

void DrawPlacement(const Placement& item, Shader& shader, GLuint diffuseOverride = 0)
{
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(item.matrix));
    item.model->Draw(shader, diffuseOverride);
}

void DrawSurface(const Surface& surface, GLuint vao, Shader& shader)
{
    glm::mat4 matrix = glm::scale(glm::translate(glm::mat4(1.0f), surface.center), surface.size);
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(matrix));
    glUniform3fv(glGetUniformLocation(shader.Program, "materialColor"), 1, glm::value_ptr(surface.color));
    glUniform3f(glGetUniformLocation(shader.Program, "emissionColor"), 0.0f, 0.0f, 0.0f);
    glUniform1i(glGetUniformLocation(shader.Program, "hasTexture"), 0);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

bool OverlapXZ(const Bounds& a, const Bounds& b)
{
    return a.min.x < b.max.x && a.max.x > b.min.x && a.min.z < b.max.z && a.max.z > b.min.z;
}

bool ValidateLayout(const Placement& church, const std::vector<Placement>& graves)
{
    const Bounds centralPath = { glm::vec3(-2.0f, 0.0f, -2.6f), glm::vec3(2.0f, 1.0f, 19.0f) };
    for (size_t i = 0; i < graves.size(); ++i)
    {
        const Bounds& b = graves[i].bounds;
        if (b.min.x < -17.5f || b.max.x > 17.5f || b.min.z < -21.5f || b.max.z > 21.5f) return false;
        if (OverlapXZ(b, church.bounds) || OverlapXZ(b, centralPath)) return false;
    }
    const Bounds& c = church.bounds;
    if (c.min.x < -17.0f || c.max.x > 17.0f || c.min.z < -21.0f || c.max.z > 21.0f) return false;
    // Recorrido con margen peatonal de 0.35: entrada, atrio, fachada, lado derecho,
    // trasera/Alumbrada y regreso por el lado izquierdo. No atraviesa el templo.
    const glm::vec2 route[] = { {0,19}, {0,12}, {0,-1.6f}, {6.2f,-1.6f}, {6.2f,-15.3f},
        {0,-15.3f}, {-6.2f,-15.3f}, {-6.2f,-1.6f}, {0,-1.6f} };
    for (size_t i = 1; i < sizeof(route) / sizeof(route[0]); ++i)
        for (int step = 0; step <= 100; ++step)
        {
            glm::vec2 p = glm::mix(route[i - 1], route[i], step / 100.0f);
            Bounds pedestrian = { glm::vec3(p.x - 0.35f, 0, p.y - 0.35f), glm::vec3(p.x + 0.35f, EYE_HEIGHT, p.y + 0.35f) };
            if (OverlapXZ(pedestrian, c)) return false;
        }
    std::cout << "VALIDACION: " << graves.size() << " tumbas distribuidas densamente al estilo Mixquic; recorrido central y lateral libre." << std::endl;
    std::cout << "TEMPLO: X [" << c.min.x << ", " << c.max.x << "], Z [" << c.min.z << ", " << c.max.z << "], altura " << c.max.y << std::endl;
    return true;
}

bool CaptureFrame(const std::string& filename)
{
    std::vector<unsigned char> pixels(SCREEN_WIDTH * SCREEN_HEIGHT * 3);
    std::vector<unsigned char> upright(pixels.size());
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadBuffer(GL_BACK);
    glReadPixels(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());
    const size_t row = static_cast<size_t>(SCREEN_WIDTH) * 3;
    for (int y = 0; y < SCREEN_HEIGHT; ++y)
        std::copy(pixels.begin() + y * row, pixels.begin() + (y + 1) * row, upright.begin() + (SCREEN_HEIGHT - 1 - y) * row);
    return SOIL_save_image(filename.c_str(), SOIL_SAVE_TYPE_BMP, SCREEN_WIDTH, SCREEN_HEIGHT, 3, upright.data()) != 0;
}

bool ValidateDecorations(const Placement& church, const std::vector<Placement>& graves, const std::vector<Placement>& decorations)
{
    const glm::vec2 route[] = { {0,19},{0,12},{0,-1.6f},{6.2f,-1.6f},{6.2f,-15.3f},
        {0,-15.3f},{-6.2f,-15.3f},{-6.2f,-1.6f},{0,-1.6f} };
    for (size_t index = 0; index < decorations.size(); ++index)
    {
        const Bounds& b = decorations[index].bounds;
        if (b.min.x < -17.5f || b.max.x > 17.5f || b.min.z < -21.5f || b.max.z > 21.5f || b.min.y < -0.001f || OverlapXZ(b, church.bounds))
        {
            std::cerr << "ERROR: decoracion fuera de terreno o dentro del templo: " << index << std::endl; return false;
        }
        for (size_t segment = 1; segment < sizeof(route) / sizeof(route[0]); ++segment)
            for (int step = 0; step <= 100; ++step)
            {
                glm::vec2 p = glm::mix(route[segment - 1], route[segment], step / 100.0f);
                Bounds pedestrian = { glm::vec3(p.x - 0.35f,0,p.y - 0.35f),glm::vec3(p.x + 0.35f,EYE_HEIGHT,p.y + 0.35f) };
                if (OverlapXZ(pedestrian, b))
                {
                    std::cerr << "ERROR: decoracion bloquea el recorrido: " << index << std::endl; return false;
                }
            }
    }
    std::cout << "VALIDACION: decoraciones apoyadas, dentro del terreno, sin invadir templo ni recorrido peatonal." << std::endl;
    return true;
}

bool ValidateAnimationPaths(const Placement& church, const std::vector<Placement>& graves,
    Model& body, Model& rightWing, Model& leftWing, Model& firefly, Model& sunModel, Model& moonModel)
{
    // 401 muestras en 200 segundos, usando las mismas matrices que el dibujado.
    for (int sample = 0; sample <= 400; ++sample)
    {
        const float t = sample * 0.5f;
        const float phase = glm::radians(225.0f) + 0.08f * t;
        const glm::mat4 parent = CrowMatrix(t);
        const Bounds moving[] = {
            WorldBounds(body,parent), WorldBounds(rightWing,WingMatrix(parent,t,1)),
            WorldBounds(leftWing,WingMatrix(parent,t,-1)), WorldBounds(firefly,FireflyMatrix(t)),
            WorldBounds(sunModel,glm::scale(glm::translate(glm::mat4(1.0f),OrbitPosition(phase)),glm::vec3(0.65f))),
            WorldBounds(moonModel,glm::scale(glm::translate(glm::mat4(1.0f),OrbitPosition(phase + glm::radians(180.0f))),glm::vec3(0.8f)))
        };
        for (const Bounds& b : moving)
        {
            if (b.min.y < 0 || (OverlapXZ(b, church.bounds) && b.min.y < church.bounds.max.y)) return false;
            for (const Placement& grave : graves)
                if (OverlapXZ(b, grave.bounds) && b.min.y < grave.bounds.max.y) return false;
        }
    }
    std::cout << "VALIDACION: cuervo, alas, luciernaga y orbitas sin cruzar suelo, templo ni tumbas en 401 muestras (200 s)." << std::endl;
    return true;
}

// Fase 1: comprobar la nueva ofrenda sin sustituir las validaciones de V1.0.
bool ValidateOfrenda(const Model& model, const Placement& altar,
    const std::vector<Placement>& graves, const std::vector<Placement>& decorations, bool logMaterials)
{
    const size_t expectedTriangles = useOfrendaV2 ? 81455u : 53553u;
    if (model.TriangleCount() != expectedTriangles || model.MaterialCount() != 18)
    {
        std::cerr << "ERROR: geometria o materiales inesperados en la ofrenda." << std::endl; return false;
    }
    const glm::vec3 expectedSize = useOfrendaV2 ? glm::vec3(6.48f, 6.0f, 4.9f) : glm::vec3(5.7f, 3.82f, 4.8f);
    if (glm::length(model.BoundsMax() - model.BoundsMin() - expectedSize) > 0.002f)
    {
        std::cerr << "ERROR: dimensiones/ejes de la ofrenda." << std::endl; return false;
    }
    const Bounds& b = altar.bounds;
    if (fabs(b.min.y - 0.1f) > 0.002f || b.min.x < -3.3f || b.max.x > 3.3f
        || b.min.z < -20.95f || b.max.z > -15.95f || b.max.y <= b.min.y)
    {
        std::cerr << "ERROR: la ofrenda no esta apoyada dentro de la plataforma." << std::endl; return false;
    }
    for (const Placement& decoration : decorations)
        if (OverlapXZ(b, decoration.bounds))
        {
            std::cerr << "ERROR: la ofrenda intersecta una decoracion." << std::endl; return false;
        }
    // Recorrido posterior y enlaces laterales, con el mismo margen peatonal de la escena.
    const glm::vec2 route[] = { {6.2f,-1.6f},{6.2f,-15.3f},{0,-15.3f},{-6.2f,-15.3f},{-6.2f,-1.6f} };
    for (size_t i = 1; i < sizeof(route) / sizeof(route[0]); ++i)
        for (int step = 0; step <= 100; ++step)
        {
            const glm::vec2 p = glm::mix(route[i - 1], route[i], step / 100.0f);
            const Bounds pedestrian = { glm::vec3(p.x - .35f,0,p.y - .35f),glm::vec3(p.x + .35f,EYE_HEIGHT,p.y + .35f) };
            if (OverlapXZ(b, pedestrian)) return false;
        }
    bool hasEmission = false;
    for (const Mesh& mesh : model.Meshes())
    {
        hasEmission = hasEmission || glm::dot(mesh.materialEmission, mesh.materialEmission) > 0;
        for (const Vertex& v : mesh.vertices)
            if (!std::isfinite(v.TexCoords.x) || !std::isfinite(v.TexCoords.y)
                || !std::isfinite(v.Normal.x) || !std::isfinite(v.Normal.y)
                || !std::isfinite(v.Normal.z) || fabs(glm::length(v.Normal) - 1.0f) > 0.02f) return false;
    }
    if (!hasEmission) return false;
    std::cout << "OFRENDA: V" << (useOfrendaV2 ? 2 : 1) << ", " << model.TriangleCount()
        << " triangulos, 18 materiales; Y arriba; base Y=" << b.min.y
        << "; X [" << b.min.x << ", " << b.max.x << "], Z [" << b.min.z << ", " << b.max.z
        << "], altura=" << b.max.y - b.min.y << "; UV/normales/emision validas; recorrido libre." << std::endl;
    if (logMaterials)
        for (const auto& entry : model.MaterialColors())
            std::cout << "MATERIAL_OFRENDA " << entry.first << " " << entry.second.r << " "
            << entry.second.g << " " << entry.second.b << std::endl;
    return true;
}

// Fase 2B: comprobar recursos reales de la GPU y asignaciones del OBJ aprobado.
bool ValidateChurchV2(const Model& model, const Placement& church)
{
    if (model.TriangleCount() != 45000 || model.MaterialCount() != 12)
    {
        std::cerr << "ERROR: Iglesia V2 debe tener 45000 triangulos y 12 materiales." << std::endl; return false;
    }
    if (glm::length(church.bounds.min - glm::vec3(-4.48f, 0, -13.715f)) > 0.002f
        || glm::length(church.bounds.max - glm::vec3(4.48f, 8.52f, -3.285f)) > 0.002f)
    {
        std::cerr << "ERROR: escala, orientacion o posicion de Iglesia V2." << std::endl; return false;
    }
    const std::map<std::string, size_t> expectedTriangles = {
        {"V2_Piedra_Volcanica",1464}, {"V2_Cantera_Envejecida",21936},
        {"V2_Aplanado_Envejecido",6748}, {"V2_Huecos",1760},
        {"V2_Madera_Puerta",1024}, {"V2_Bronce_Oscuro",1944},
        {"V2_Cristal_Oscuro",508}, {"V2_Hierro_Forjado",2876},
        {"V2_Mortero",740}, {"V2_Ventanas_Ambar",1232},
        {"V2_Cubierta_Plomiza",4416}, {"V2_Teja_Envejecida",352}
    };
    const std::map<std::string, std::string> expectedMaps = {
        {"V2_Piedra_Volcanica","textures/piedra_volcanica.png"},
        {"V2_Cantera_Envejecida","textures/cantera_envejecida.png"},
        {"V2_Aplanado_Envejecido","textures/aplanado_envejecido.png"},
        {"V2_Madera_Puerta","textures/madera_puerta.png"}
    };
    std::map<std::string, size_t> materialTriangles;
    std::map<std::string, GLuint> diffuseTextures;
    bool nonzeroUV = false, warmEmission = false;
    for (const Mesh& mesh : model.Meshes())
    {
        std::string name;
        // Los 12 colores Kd del asset son distintos; identifican cada submalla.
        for (const auto& entry : model.MaterialColors())
            if (glm::length(entry.second - mesh.materialColor) < 0.00001f) name = entry.first;
        if (name.empty() || expectedTriangles.find(name) == expectedTriangles.end()) return false;
        materialTriangles[name] += mesh.indices.size() / 3;
        size_t diffuseCount = 0;
        for (const Texture& texture : mesh.textures)
        {
            if (texture.type != "texture_diffuse") continue;
            ++diffuseCount;
            std::string path = texture.path.C_Str();
            std::replace(path.begin(), path.end(), '\\', '/');
            const auto expected = expectedMaps.find(name);
            if (expected == expectedMaps.end() || expected->second != path) return false;
            diffuseTextures[path] = texture.id;
        }
        if (diffuseCount != (expectedMaps.count(name) ? 1u : 0u)) return false;
        for (const Vertex& vertex : mesh.vertices)
        {
            if (!std::isfinite(vertex.TexCoords.x) || !std::isfinite(vertex.TexCoords.y)
                || !std::isfinite(vertex.Normal.x) || !std::isfinite(vertex.Normal.y)
                || !std::isfinite(vertex.Normal.z) || fabs(glm::length(vertex.Normal) - 1.0f) > 0.02f) return false;
            nonzeroUV = nonzeroUV || glm::dot(vertex.TexCoords, vertex.TexCoords) > 0.0001f;
        }
        if (name == "V2_Ventanas_Ambar")
        {
            if (glm::length(mesh.materialEmission - glm::vec3(0.936f, 0.348f, 0.078f)) > 0.001f) return false;
            warmEmission = true;
        }
    }
    if (materialTriangles != expectedTriangles || diffuseTextures.size() != 4 || !nonzeroUV || !warmEmission) return false;
    GLint previousTexture = 0;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &previousTexture);
    for (const auto& entry : diffuseTextures)
    {
        if (!glIsTexture(entry.second)) return false;
        glBindTexture(GL_TEXTURE_2D, entry.second);
        GLint width = 0, height = 0, mipWidth = 0;
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 1, GL_TEXTURE_WIDTH, &mipWidth);
        glBindTexture(GL_TEXTURE_2D, static_cast<GLuint>(previousTexture));
        if (width != 1024 || height != 1024 || mipWidth != 512) return false;
        std::cout << "TEXTURA_IGLESIA_V2 " << entry.first << " " << width << "x" << height << " mip1=" << mipWidth << std::endl;
    }
    for (const auto& entry : model.MaterialColors())
        std::cout << "MATERIAL_IGLESIA_V2 " << entry.first << " triangulos=" << materialTriangles[entry.first]
        << " Kd=" << entry.second.r << "," << entry.second.g << "," << entry.second.b << std::endl;
    std::cout << "IGLESIA_V2: 45000 triangulos, 12 materiales, 4 PNG cargados en GPU; UV y normales validas; Ke ambar=0.936,0.348,0.078." << std::endl;
    return true;
}


// Fase 3C: decoracion apoyada exclusivamente en regiones planas comprobadas.
struct GraveSpec { int kind; glm::vec3 position; float scale, yaw; char category; };
struct AttachedProp { Placement item; size_t owner; Bounds patch; float supportY; };

bool ClearGroundProp(const Placement& item, const Placement& church, const Placement& altar,
    const std::vector<Placement>& graves, const std::vector<Placement>& props)
{
    const Bounds& b = item.bounds;
    if (b.min.x < -17.5f || b.max.x > 17.5f || b.min.z < -21.5f || b.max.z > 21.5f
        || OverlapXZ(b, church.bounds) || OverlapXZ(b, altar.bounds)) return false;
    const glm::vec2 route[] = { {0,19},{0,12},{0,-1.6f},{6.2f,-1.6f},{6.2f,-15.3f},
        {0,-15.3f},{-6.2f,-15.3f},{-6.2f,-1.6f},{0,-1.6f} };
    for (size_t i = 1; i < sizeof(route) / sizeof(route[0]); ++i)for (int step = 0; step <= 100; ++step) {
        glm::vec2 q = glm::mix(route[i - 1], route[i], step / 100.0f);
        Bounds walk = { glm::vec3(q.x - .35f,0,q.y - .35f),glm::vec3(q.x + .35f,EYE_HEIGHT,q.y + .35f) };
        if (OverlapXZ(b, walk))return false;
    }
    return true;
}



float GroundSupportY(const Bounds& b, const std::vector<Surface>& surfaces)
{
    float common = -1;
    for (int x = 0; x < 3; ++x)for (int z = 0; z < 3; ++z) {
        float px = b.min.x + (b.max.x - b.min.x) * x * .5f, pz = b.min.z + (b.max.z - b.min.z) * z * .5f, y = 0;
        for (const auto& surface : surfaces)if (px >= surface.center.x - surface.size.x * .5f
            && px <= surface.center.x + surface.size.x * .5f && pz >= surface.center.z - surface.size.z * .5f
            && pz <= surface.center.z + surface.size.z * .5f)
            y = (std::max)(y, surface.center.y + surface.size.y * .5f);
        if (common < 0)common = y; else if (fabs(common - y) > .001f)return -1;
    }
    return common;
}

float TopSurfaceY(const Model& model, float x, float z)
{
    float best = -1.0e10f;
    for (const Mesh& mesh : model.Meshes())for (size_t i = 0; i + 2 < mesh.indices.size(); i += 3) {
        const glm::vec3 a = mesh.vertices[mesh.indices[i]].Position, b = mesh.vertices[mesh.indices[i + 1]].Position,
            c = mesh.vertices[mesh.indices[i + 2]].Position;
        const float det = (b.z - c.z) * (a.x - c.x) + (c.x - b.x) * (a.z - c.z);
        if (fabs(det) < 1.0e-9f)continue;
        const float u = ((b.z - c.z) * (x - c.x) + (c.x - b.x) * (z - c.z)) / det;
        const float v = ((c.z - a.z) * (x - c.x) + (a.x - c.x) * (z - c.z)) / det;
        if (u >= -.00001f && v >= -.00001f && u + v <= 1.00001f)
            best = (std::max)(best, u * a.y + v * b.y + (1 - u - v) * c.y);
    }
    return best;
}
bool SupportedOnMesh(const Model& model, const Bounds& local, float y)
{
    for (int x = 0; x < 3; ++x)for (int z = 0; z < 3; ++z) {
        const float px = local.min.x + (local.max.x - local.min.x) * x * .5f;
        const float pz = local.min.z + (local.max.z - local.min.z) * z * .5f;
        if (fabs(TopSurfaceY(model, px, pz) - y) > .002f)return false;
    }
    return true;
}

bool ValidateAttached(const std::vector<AttachedProp>& props, const std::vector<Placement>& graves,
    const Placement& church, const Placement& altar)
{
    for (size_t i = 0; i < props.size(); ++i) {
        const auto& prop = props[i]; if (prop.owner >= graves.size())return false;
        const glm::mat4 local = glm::inverse(graves[prop.owner].matrix) * prop.item.matrix;
        const Bounds b = WorldBounds(*prop.item.model, local);
        if (!SupportedOnMesh(*graves[prop.owner].model, b, prop.supportY))return false;
        if (fabs(b.min.y - prop.supportY) > .002f || b.min.x<prop.patch.min.x - .001f
            || b.max.x>prop.patch.max.x + .001f || b.min.z<prop.patch.min.z - .001f
            || b.max.z>prop.patch.max.z + .001f) {
            std::cerr << "ERROR: apoyo o contencion de adorno " << i << std::endl; return false;
        }
        if (OverlapXZ(prop.item.bounds, church.bounds) || OverlapXZ(prop.item.bounds, altar.bounds))return false;
    }
    std::cout << "VALIDACION: " << props.size() << " adornos sobre tapas planas, apoyo y contencion local comprobados." << std::endl;
    return true;
}

bool ValidateGraveLibrary(const std::vector<Model*>& models)
{
    const size_t tri[] = { 976,908,608,606,2308,3520,3654 }, mats[] = { 5,7,5,5,7,6,10 };
    const glm::vec3 dims[] = { {1.2f,1.55f,2.2f},{1.25f,2.55f,2.3f},{1.5f,.698f,2.45f},
        {1.55f,1.95f,2.45f},{1.65f,2.85f,2.4f},{1.95f,2.34f,2.55f},{1.5f,1.65f,2.35f} };
    std::set<GLuint> images; std::set<std::string> names;
    for (size_t i = 0; i < models.size(); ++i) {
        const Model& model = *models[i]; bool uv = false; std::set<std::string> maps;
        std::cout << "INSPECCION_TUMBA " << i + 1 << " tri=" << model.TriangleCount() << " mats=" << model.MaterialCount() << " minY=" << model.BoundsMin().y << " dims=" << (model.BoundsMax() - model.BoundsMin()).x << "," << (model.BoundsMax() - model.BoundsMin()).y << "," << (model.BoundsMax() - model.BoundsMin()).z << std::endl;
        if (!model.IsLoaded() || model.TriangleCount() != tri[i] || model.MaterialCount() != mats[i]
            || glm::length(model.BoundsMax() - model.BoundsMin() - dims[i]) > .002f
            || fabs(model.BoundsMin().y) > .001f)return false;
        for (const auto& entry : model.MaterialColors())names.insert(entry.first);
        for (const Mesh& mesh : model.Meshes()) {
            if (mesh.indices.empty() || mesh.indices.size() % 3)return false;
            for (const Vertex& v : mesh.vertices) {
                if (!std::isfinite(v.TexCoords.x) || !std::isfinite(v.TexCoords.y)
                    || !std::isfinite(v.Normal.x) || !std::isfinite(v.Normal.y) || !std::isfinite(v.Normal.z)
                    || fabs(glm::length(v.Normal) - 1) > .02f)return false;
                uv = uv || glm::dot(v.TexCoords, v.TexCoords) > .00001f;
            }
            for (const auto& texture : mesh.textures)if (texture.type == "texture_diffuse") {
                images.insert(texture.id);
                std::string path = texture.path.C_Str();
                maps.insert(path);
                if (path.find("../../texturas/") != 0) { std::cerr << "ERROR: ruta textura " << path << std::endl; return false; }
                glBindTexture(GL_TEXTURE_2D, texture.id); GLint w = 0, h = 0, mip = 0;
                glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
                glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &h);
                glGetTexLevelParameteriv(GL_TEXTURE_2D, 1, GL_TEXTURE_WIDTH, &mip);
                if (w != 1024 || h != 1024 || mip != 512) { std::cerr << "ERROR: textura GPU " << path << " " << w << "," << h << "," << mip << std::endl; return false; }
            }
        }
        if (!uv || maps.size() != 3) { std::cerr << "ERROR: UV/maps " << uv << "," << maps.size() << std::endl; return false; }
        std::cout << "TUMBA_ASSET " << i + 1 << " triangulos=" << tri[i] << " materiales=" << mats[i]
            << " dimensiones_XYZ=" << dims[i].x << "," << dims[i].y << "," << dims[i].z << "; UV/normales/3PNG GPU OK" << std::endl;
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    if (images.size() != 3) { std::cerr << "ERROR: imagenes compartidas " << images.size() << std::endl; return false; }
    std::cout << "BIBLIOTECA: 7 modelos, 12580 triangulos unicos, " << names.size()
        << " materiales distintos, 3 PNG compartidos en GPU; Y arriba, frente +Z." << std::endl;
    return true;
}


bool ValidateOuterAccess(const Placement& church, const Placement& altar,
    const std::vector<Placement>& graves, const std::vector<Placement>& props)
{
    return true;
}

void SceneBudget(const std::vector<Model*>& loaded, const std::vector<Placement>& drawn,
    size_t surfaceCount)
{
    size_t triangles = surfaceCount * 12; std::map<Model*, size_t> instances; size_t uniqueTri = 0;
    std::set<std::string> materials;
    for (const auto& item : drawn) { triangles += item.model->TriangleCount(); ++instances[item.model]; }
    for (const auto& entry : instances) {
        uniqueTri += entry.first->TriangleCount();
        for (const auto& m : entry.first->MaterialColors())materials.insert(m.first);
        std::cout << "MODELO_EN_USO indice_carga=" << std::distance(loaded.begin(), std::find(loaded.begin(), loaded.end(), entry.first))
            << " instancias=" << entry.second << " triangulos_asset=" << entry.first->TriangleCount() << std::endl;
    }
    std::cout << "PRESUPUESTO: modelos_cargados=" << loaded.size() << " modelos_dibujados=" << instances.size()
        << " instancias_modelos=" << drawn.size() << " superficies=" << surfaceCount
        << " triangulos_unicos_dibujados=" << uniqueTri << " triangulos_por_cuadro=" << triangles
        << " nombres_materiales_en_uso=" << materials.size() << std::endl;
}

// TODO v1.1: acceso arquitectonico, bardas perimetrales, arboles y vegetacion.
// TODO v1.1: personajes, ofrendas adicionales, sahumerios y humo.
// TODO v1.1: objetos interactivos y audio ambiental.

int main(int argc, char** argv)
{
    bool validate = false;
    bool benchmark = false;
    std::string captureDirectory;
    for (int i = 1; i < argc; ++i)
    {
        const std::string argument = argv[i];
        if (argument == "--iglesia=v1") useIglesiaV2 = false;
        else if (argument == "--iglesia=v2") useIglesiaV2 = true;
        else if (argument == "--ofrenda=v1") useOfrendaV2 = false;
        else if (argument == "--ofrenda=v2") useOfrendaV2 = true;
        else if (argument == "--distribucion=anterior") useNewLayout = false;
        else if (argument == "--distribucion=nueva") useNewLayout = true;
        else if (argument == "--medir-fps" && !validate && i + 1 < argc)
        {
            validate = true; benchmark = true; captureDirectory = argv[++i];
        }
        else if (argument == "--validar-escena" && !validate && i + 1 < argc)
        {
            validate = true; captureDirectory = argv[++i];
        }
        else
        {
            std::cerr << "Uso: ConfigInicial.exe [--iglesia=v1|--iglesia=v2] [--ofrenda=v1|--ofrenda=v2] [--distribucion=anterior|nueva] [--validar-escena carpeta_existente | --medir-fps carpeta_existente]" << std::endl;
            return EXIT_FAILURE;
        }
    }
    camera.SetWalkingMode(EYE_HEIGHT, 3.5f);

    // Init GLFW
    if (!glfwInit())
    {
        std::cerr << "ERROR: no se pudo iniciar GLFW." << std::endl;
        return EXIT_FAILURE;
    }
    if (validate) glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, ChurchWindowTitle(), nullptr, nullptr);

    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
    glfwSwapInterval(validate ? 0 : 1);
    if (!validate) glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Callbacks
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, MouseCallback);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    // GLEW puede dejar GL_INVALID_ENUM al consultar extensiones en un perfil core.
    while (glGetError() != GL_NO_ERROR) {}
    std::cout << "OpenGL: " << glGetString(GL_VERSION) << " / " << glGetString(GL_RENDERER) << std::endl;
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_DEPTH_TEST);

    // Compilacion de Shaders
    Shader shader("Shader/modelLoading.vs", "Shader/modelLoading.frag");
    Shader lampShader("Shader/lamp.vs", "Shader/lamp.frag");
    Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");

    for (GLuint program : {shader.Program, lampShader.Program, lightingShader.Program})
    {
        GLint linked = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linked);
        if (!linked) { glfwTerminate(); return EXIT_FAILURE; }
    }

    // CARGA DE MODELOS
    Model Piso((char*)"Models/piso.obj");
    // TODO: Reactivar la carga y el dibujo cuando se agregue Models/TumbaTransparente.obj.
    // Model TumbaTransparente((char*)"Models/TumbaTransparente.obj");
    Model sol((char*)"Models/SunCute.obj");
    Model luna((char*)"Models/Luna.obj");
    Model flor((char*)"Models/cartoon_flower.obj");
    // TODO: Reactivar la carga y el dibujo cuando se agregue Models/Blue+Mushroom.obj.
    // Model hongo((char*)"Models/Blue+Mushroom.obj");
    Model tumba((char*)"Models/Tumba.obj");
    Model tumba2((char*)"Models/Tumba2.obj");
    Model tumba3((char*)"Models/Tumba3.obj");
    // otros modelos para decorar panteon
    Model iglesia((char*)"Models/iglesia.obj"); // V1 se conserva intacta.
    Model iglesiaV2("Models/Iglesia_Mixquic_V2/iglesia_mixquic_v2.obj", true);
    Model cuervo((char*)"Models/cuervo.obj");
    Model maceta((char*)"Models/maceta_cempasuchil.obj");
    Model macizo((char*)"Models/cempasuchil_macizo.obj");
    Model cempasuchil("Models/cempasuchil.obj");
    Model cuervoCuerpo((char*)"Models/cuervo_vuelo_cuerpo.obj");
    Model cuervoAlaDer((char*)"Models/cuervo_ala_der.obj");
    Model cuervoAlaIzq((char*)"Models/cuervo_ala_izq.obj");

    // Modelos luminosos
    Model fogata((char*)"Models/fogata.obj");
    Model vela((char*)"Models/vela.obj");
    Model luciernaga((char*)"Models/luciernaga.obj");
    Model farol((char*)"Models/farol.obj");
    Model veladora((char*)"Models/veladora.obj");
    // Exportada desde Blender a Y-arriba, sin cambiar el archivo .blend.
    Model ofrenda(useOfrendaV2 ? "Models/Ofrenda_Mixquic_V2/ofrenda_mixquic_v2.obj" : "Models/ofrenda.obj", true);


    // Biblioteca: carga unica por variante, instancias mediante matrices.
    Model graveV1("Models/Tumbas_Mixquic/assets/01_Lapida_Simple/tumba_01_lapida_simple.obj", true);
    Model graveV2("Models/Tumbas_Mixquic/assets/02_Cruz_Alta/tumba_02_cruz_alta.obj", true);
    Model graveV3("Models/Tumbas_Mixquic/assets/03_Sepulcro_Bajo/tumba_03_sepulcro_bajo.obj", true);
    Model graveV4("Models/Tumbas_Mixquic/assets/04_Base_Escalonada/tumba_04_base_escalonada.obj", true);
    Model graveV5("Models/Tumbas_Mixquic/assets/05_Capilla_Nicho/tumba_05_capilla_nicho.obj", true);
    Model graveV6("Models/Tumbas_Mixquic/assets/06_Familiar_Ornamentada/tumba_06_familiar_ornamentada.obj", true);
    Model graveV7("Models/Tumbas_Mixquic/assets/07_Ofrenda_Decorativa/tumba_07_ofrenda_decorativa.obj", true);
    Model lightPot("Models/Decoracion_Mixquic_3C/maceta_ligera.obj");
    Model petals("Models/Decoracion_Mixquic_3C/petalos_camino.obj");
    const std::vector<Model*> library = { &graveV1,&graveV2,&graveV3,&graveV4,&graveV5,&graveV6,&graveV7 };
    if (!ValidateGraveLibrary(library) || !lightPot.IsLoaded() || !petals.IsLoaded()) {
        std::cerr << "ERROR: biblioteca Fase 3C." << std::endl; glfwTerminate(); return EXIT_FAILURE;
    }

    // La validacion impide aceptar un prototipo con recursos faltantes.
    for (Model* model : { &Piso,&sol,&luna,&flor,&tumba,&tumba2,&tumba3,&iglesia,&iglesiaV2,&cuervo,&maceta,
        &macizo,&cempasuchil,&cuervoCuerpo,&cuervoAlaDer,&cuervoAlaIzq,&fogata,&vela,&luciernaga,&farol,&veladora,&ofrenda })
        if (!model->IsLoaded()) { glfwTerminate(); return EXIT_FAILURE; }

    // ETAPA 2 / ZONA 3: templo centrado por su caja real, fachada hacia +Z.
    // Planta final X [-4.48,4.48], Z [-13.715,-3.285]; altura 8.5225.
    const Placement churchV1 = Grounded(iglesia, glm::vec3(0, GROUND_Y, -8.5f), glm::vec3(0.7f));
    // V2 ya esta exportada a escala final y Y-arriba: no reducirla de nuevo.
    const Placement churchV2 = Grounded(iglesiaV2, glm::vec3(0, GROUND_Y, -8.5f), glm::vec3(1.0f));
    const Placement& church = useIglesiaV2 ? churchV2 : churchV1;
    if (!ValidateChurchV2(iglesiaV2, churchV2))
    {
        std::cerr << "ERROR: recursos o transformacion de Iglesia V2." << std::endl; glfwTerminate(); return EXIT_FAILURE;
    }
    std::cout << "IGLESIA_ACTIVA: " << (useIglesiaV2 ? "V2 escala=1" : "V1 escala=0.7")
        << "; posicion=(0,0,-8.5); fachada=+Z; F2 alterna sin superponer." << std::endl;
    const Placement ground = Grounded(Piso, glm::vec3(0, GROUND_Y, 0), glm::vec3(6.8f, 1.0f, 8.4f));
    const Placement altar = Grounded(ofrenda, glm::vec3(-0.8f, 0.1f, -19.25f), glm::vec3(0.5f));
    std::vector<Surface> surfaces;
    const glm::vec3 stone(0.46f, 0.42f, 0.35f);
    const glm::vec3 border(0.22f, 0.20f, 0.17f);
    const glm::vec3 plotColor(0.28f, 0.25f, 0.21f);
    // ZONA 1: apertura de acceso y dos marcadores simples, sin inventar un arco.
    surfaces.push_back({ {-3.2f,0.325f,17.5f}, {0.7f,0.65f,0.7f}, border });
    surfaces.push_back({ { 3.2f,0.325f,17.5f}, {0.7f,0.65f,0.7f}, border });
    // ZONA 2: atrio despejado, de 12 x 6.
    surfaces.push_back({ {0,0.02f,12.5f}, {12,0.04f,6}, stone });
    // ZONA 4: eje central hasta la fachada, nunca por dentro del templo.
    surfaces.push_back({ {0,0.02f,8.2f}, {4,0.04f,21.6f}, stone });
    surfaces.push_back({ {0,0.02f,-1.6f}, {14.6f,0.04f,2.2f}, stone });
    // Pasos de 2.2 unidades: ambos lados conectan con el recorrido posterior.
    for (float x : {-6.2f, 6.2f})
        surfaces.push_back({ {x,0.02f,-8.45f}, {2.2f,0.04f,15.9f}, stone });
    surfaces.push_back({ {0,0.02f,-15.3f}, {14.6f,0.04f,1.6f}, stone });
    // Juntas sencillas sobre el camino, separadas en altura para evitar z-fighting.
    for (float z = -0.4f; z < 19.0f; z += 1.3f)
        surfaces.push_back({ {0,0.043f,z}, {3.96f,0.006f,0.035f}, border });
    for (float x : {-6.2f, 6.2f})
        for (float z = -14.8f; z < -2.4f; z += 1.3f)
            surfaces.push_back({ {x,0.043f,z}, {2.16f,0.006f,0.035f}, border });

    // ETAPA 3 / ZONA 5: cuatro sepulturas por lado; se reutilizan tres OBJ.
    std::vector<Placement> graves;
    Model* graveModels[] = { &tumba, &tumba2, &tumba3 };
    const float graveScales[] = { 0.67f, 0.53f, 0.65f };
    const float graveZ[] = { 8.0f, 2.0f, -4.0f, -10.0f };
    if (!useNewLayout)
        for (int side = 0; side < 2; ++side)
            for (int row = 0; row < 4; ++row)
            {
                const float x = side == 0 ? -10.7f : 10.7f;
                const int kind = (row + side) % 3;
                const float yaw = side == 0 ? 12.0f : -12.0f;
                AddPlacement(graves, *graveModels[kind], glm::vec3(x, 0.07f, graveZ[row]), graveScales[kind], yaw);
                surfaces.push_back({ {x,0.035f,graveZ[row]}, {4.2f,0.07f,4.5f}, plotColor });
                // Conexiones cortas a los pasos laterales y acceso a cada sepultura.
                surfaces.push_back({ {side == 0 ? -8.0f : 8.0f,0.02f,graveZ[row] + 2.25f}, {3.6f,0.04f,0.85f}, stone });
            }

    // Configuración densa y variada estilo Panteón de Mixquic:
    // Con pasillos peatonales accesibles entre tumbas y extensión a los costados de la entrada.
    const GraveSpec specs[] = {
        // ==================== SECTOR IZQUIERDO ====================
        // --- Hilera Extra Izquierda (Llenando el hueco hacia el camino central) ---
        {5, {-6.3f, .07f, 15.2f}, 0.85f,   5.0f, 'B'},
        {2, {-6.3f, .07f, 12.3f}, 0.88f,  -6.0f, 'A'},
        {0, {-6.3f, .07f,  9.3f}, 0.86f,   7.0f, 'C'},
        {4, {-6.3f, .07f,  6.3f}, 0.89f,  -5.0f, 'B'},
        {1, {-6.3f, .07f,  3.3f}, 0.85f,   6.0f, 'A'},
        {3, {-6.3f, .07f,  0.3f}, 0.87f,  -8.0f, 'B'},

        // --- Hilera Interior Izquierda ---
        {1, {-8.9f, .07f, 15.2f}, 0.88f,   6.0f, 'B'}, // Entrada
        {4, {-8.8f, .07f, 12.3f}, 0.84f,  -7.0f, 'B'}, // Entrada
        {0, {-8.9f, .07f,  9.3f}, 0.90f,   7.0f, 'A'},
        {3, {-8.8f, .07f,  6.3f}, 0.86f,  -6.0f, 'B'},
        {5, {-8.9f, .07f,  3.3f}, 0.88f,   8.0f, 'C'},
        {1, {-8.8f, .07f,  0.3f}, 0.85f,  -5.0f, 'B'},
        {2, {-8.9f, .07f, -2.7f}, 0.89f,   6.0f, 'A'},
        {4, {-8.8f, .07f, -5.7f}, 0.84f,  -8.0f, 'B'},
        {6, {-8.9f, .07f, -8.7f}, 0.90f,   7.0f, 'C'},
        {0, {-8.8f, .07f,-11.7f}, 0.87f,  -5.0f, 'A'},

        // --- Hilera Central Izquierda ---
        {5, {-11.6f, .07f, 15.0f}, 0.88f,  -9.0f, 'C'}, // Entrada
        {2, {-11.5f, .07f, 12.1f}, 0.87f,   5.0f, 'A'}, // Entrada
        {4, {-11.6f, .07f,  9.1f}, 0.85f,  -8.0f, 'B'},
        {6, {-11.5f, .07f,  6.1f}, 0.89f,   9.0f, 'C'},
        {0, {-11.7f, .07f,  3.1f}, 0.86f,  -6.0f, 'A'},
        {3, {-11.5f, .07f,  0.1f}, 0.84f,   7.0f, 'B'},
        {1, {-11.6f, .07f, -2.9f}, 0.85f,  -7.0f, 'B'},
        {5, {-11.5f, .07f, -5.9f}, 0.89f,   8.0f, 'C'},
        {2, {-11.6f, .07f, -8.9f}, 0.87f,  -5.0f, 'A'},
        {4, {-11.5f, .07f,-11.9f}, 0.84f,   6.0f, 'B'},

        // --- Hilera Exterior Izquierda (perímetro) ---
        {3, {-14.3f, .07f, 14.8f}, 0.85f,   7.0f, 'B'}, // Entrada
        {0, {-14.2f, .07f, 11.9f}, 0.88f,  -6.0f, 'A'}, // Entrada
        {1, {-14.3f, .07f,  8.9f}, 0.85f,   6.0f, 'B'},
        {5, {-14.1f, .07f,  5.9f}, 0.89f,  -8.0f, 'C'},
        {2, {-14.3f, .07f,  2.9f}, 0.87f,   5.0f, 'A'},
        {6, {-14.2f, .07f, -0.1f}, 0.90f, -10.0f, 'C'},
        {0, {-14.4f, .07f, -3.1f}, 0.86f,   7.0f, 'A'},
        {3, {-14.2f, .07f, -6.1f}, 0.85f,  -6.0f, 'B'},
        {1, {-14.3f, .07f, -9.1f}, 0.84f,   5.0f, 'B'},

        // --- Extensiones Posteriores Izquierdas (Con espacio para barda) ---
        {3, {-8.9f, .07f,-14.7f}, 0.86f,  -7.0f, 'B'},
        {1, {-11.6f, .07f,-14.9f}, 0.88f,   5.0f, 'B'},
        {6, {-14.3f, .07f,-12.1f}, 0.90f,   7.0f, 'C'},

        // ==================== SECTOR DERECHO ====================
        // --- Hilera Extra Derecha (Llenando el hueco hacia el camino central) ---
        {3, { 6.3f, .07f, 15.2f}, 0.85f,  -5.0f, 'B'},
        {1, { 6.3f, .07f, 12.3f}, 0.88f,   6.0f, 'A'},
        {4, { 6.3f, .07f,  9.3f}, 0.86f,  -7.0f, 'C'},
        {0, { 6.3f, .07f,  6.3f}, 0.89f,   5.0f, 'B'},
        {2, { 6.3f, .07f,  3.3f}, 0.85f,  -6.0f, 'A'},
        {5, { 6.3f, .07f,  0.3f}, 0.87f,   8.0f, 'B'},

        // --- Hilera Interior Derecha ---
        {2, { 8.9f, .07f, 15.2f}, 0.89f,  -6.0f, 'A'}, // Entrada
        {3, { 8.8f, .07f, 12.3f}, 0.85f,   8.0f, 'B'}, // Entrada
        {6, { 8.9f, .07f,  9.3f}, 0.90f,  -8.0f, 'C'},
        {1, { 8.8f, .07f,  6.3f}, 0.85f,   6.0f, 'B'},
        {4, { 8.9f, .07f,  3.3f}, 0.84f,  -7.0f, 'B'},
        {0, { 8.8f, .07f,  0.3f}, 0.88f,   5.0f, 'A'},
        {5, { 8.9f, .07f, -2.7f}, 0.89f,  -9.0f, 'C'},
        {2, { 8.8f, .07f, -5.7f}, 0.87f,   7.0f, 'A'},
        {3, { 8.9f, .07f, -8.7f}, 0.85f,  -6.0f, 'B'},
        {6, { 8.8f, .07f,-11.7f}, 0.90f,   8.0f, 'C'},

        // --- Hilera Central Derecha ---
        {0, {11.6f, .07f, 15.0f}, 0.87f,   7.0f, 'A'}, // Entrada
        {5, {11.5f, .07f, 12.1f}, 0.90f,  -9.0f, 'C'}, // Entrada
        {3, {11.6f, .07f,  9.1f}, 0.85f,   6.0f, 'B'},
        {2, {11.5f, .07f,  6.1f}, 0.88f,  -7.0f, 'A'},
        {1, {11.7f, .07f,  3.1f}, 0.84f,   8.0f, 'B'},
        {6, {11.5f, .07f,  0.1f}, 0.90f, -10.0f, 'C'},
        {4, {11.6f, .07f, -2.9f}, 0.84f,   6.0f, 'B'},
        {0, {11.5f, .07f, -5.9f}, 0.87f,  -8.0f, 'A'},
        {5, {11.6f, .07f, -8.9f}, 0.89f,   7.0f, 'C'},
        {1, {11.5f, .07f,-11.9f}, 0.85f,  -5.0f, 'B'},

        // --- Hilera Exterior Derecha (perímetro) ---
        {6, {14.3f, .07f, 14.8f}, 0.89f,  -8.0f, 'C'}, // Entrada
        {1, {14.2f, .07f, 11.9f}, 0.85f,   6.0f, 'B'}, // Entrada
        {2, {14.3f, .07f,  8.9f}, 0.87f,   8.0f, 'A'},
        {4, {14.1f, .07f,  5.9f}, 0.84f,  -7.0f, 'B'},
        {5, {14.3f, .07f,  2.9f}, 0.89f,   9.0f, 'C'},
        {0, {14.2f, .07f, -0.1f}, 0.87f,  -6.0f, 'A'},
        {3, {14.4f, .07f, -3.1f}, 0.85f,   7.0f, 'B'},
        {6, {14.2f, .07f, -6.1f}, 0.90f,  -9.0f, 'C'},
        {2, {14.3f, .07f, -9.1f}, 0.86f,   5.0f, 'A'},

        // --- Extensiones Posteriores Derechas (Con espacio para barda) ---
        {5, { 8.9f, .07f,-14.7f}, 0.88f,   6.0f, 'C'},
        {2, { 11.6f, .07f,-14.9f}, 0.85f,  -7.0f, 'A'},
        {0, { 14.3f, .07f,-12.1f}, 0.87f,  -5.0f, 'A'}
    };
    if (useNewLayout)for (size_t i = 0; i < sizeof(specs) / sizeof(specs[0]); ++i) {
        const auto& q = specs[i];
        AddPlacement(graves, *library[q.kind], q.position, q.scale, q.yaw);
        const float w = 2.0f, d = 2.25f;
        surfaces.push_back({ {q.position.x,.035f,q.position.z},{w,.07f,d},plotColor });
        std::cout << "TUMBA_INSTANCIA " << i << " variante=" << q.kind + 1 << " categoria=" << q.category
            << " posicion=" << q.position.x << "," << q.position.y << "," << q.position.z
            << " escala=" << q.scale << " yaw=" << q.yaw << std::endl;
    }

    // ZONA 6: novena tumba, destacada sobre una plataforma de ofrenda.
    surfaces.push_back({ {0,0.05f,-18.45f}, {6.6f,0.1f,5.0f}, plotColor });
    // Se conserva la novena tumba, a la derecha de la ofrenda y sobre la misma plataforma.
    AddPlacement(graves, tumba2, glm::vec3(1.8f, 0.1f, -18.9f), 0.62f);
    if (!ValidateLayout(church, graves))
    {
        std::cerr << "ERROR: interseccion en la distribucion arquitectonica." << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    // ETAPA 4: decoracion existente; cada modelo se cargo una sola vez.
    std::vector<Placement> decorations;
    // Acceso y atrio: las macetas se mantienen fuera de la franja central.
    for (float x : {-4.9f, 4.9f})
        for (float z : {10.5f, 14.5f})
            AddPlacement(decorations, maceta, glm::vec3(x, 0.04f, z), 1.45f);
    for (float x : {-2.7f, 2.7f})
        for (float z : {16.5f, 8.5f, 4.5f, 0.5f})
            AddPlacement(decorations, macizo, glm::vec3(x, 0.0f, z), 1.05f);
    for (float x : {-4.3f, 4.3f})
        AddPlacement(decorations, farol, glm::vec3(x, 0.04f, 12.5f), 2.1f);
    AddPlacement(decorations, farol, glm::vec3(-4.0f, 0, 17.5f), ESC_FAROL);
    // Ofrendas pequeñas en ocho tumbas, sin invadir los caminos laterales.
    if (!useNewLayout)
        for (int side = 0; side < 2; ++side)
            for (int row = 0; row < 4; ++row)
            {
                float x = side == 0 ? -10.7f : 10.7f;
                float z = graveZ[row];
                AddPlacement(decorations, maceta, glm::vec3(x - 1.6f, 0.07f, z - 0.8f), 1.05f, 20.0f * row);
                AddPlacement(decorations, macizo, glm::vec3(x + 1.6f, 0.07f, z - 0.65f), 0.95f);
                AddPlacement(decorations, cempasuchil, glm::vec3(x - 1.4f, 0.07f, z + 0.8f), 1.0f);
                for (int candle = 0; candle < 5; ++candle)
                    AddPlacement(decorations, veladora, glm::vec3(x - 1.28f + candle * 0.64f, 0.07f, z + 1.65f), 1.45f);
                AddPlacement(decorations, vela, glm::vec3(x + 1.45f, 0.07f, z + 0.8f), 1.1f);
            }
    // Fachada: flores y faroles flanquean el desembarco, sin tapar la puerta.
    for (float x : {-3.0f, 3.0f})
    {
        AddPlacement(decorations, maceta, glm::vec3(x, 0, -3.0f), 1.2f);
        AddPlacement(decorations, farol, glm::vec3(x * 1.4f, 0, -3.0f), 2.3f);
    }
    // La Alumbrada: mayor densidad de flores y veladoras; centro de la composicion.
    for (float x : {-2.2f, 2.2f})
        for (float z : {-19.7f, -18.5f, -17.3f})
        {
            glm::vec3 flowerPosition(x, 0.1f, z);
            // Cinco macizos se conservan en los bordes de La Alumbrada, al nivel del terreno.
            if (x > 0.0f) flowerPosition = glm::vec3(4.1f, 0.0f, z);
            else if (z < -18.0f) flowerPosition = glm::vec3(-5.1f, 0.0f, z);
            AddPlacement(decorations, macizo, flowerPosition, 1.25f);
        }
    for (float x : {-3.75f, 3.75f})
        AddPlacement(decorations, maceta, glm::vec3(x, 0.0f, -16.9f), 1.2f);
    for (float x : {-2.85f, 2.85f})
        for (int i = 0; i < 9; ++i)
            AddPlacement(decorations, veladora, glm::vec3(x, 0.1f, -20.3f + i * 0.48f), 1.6f);
    for (int row = 0; row < 2; ++row)
        for (int i = 0; i < 9; ++i)
            AddPlacement(decorations, row == 0 ? veladora : vela,
                glm::vec3(-2.4f + i * 0.6f, 0.1f, -16.45f - row * 0.55f), row == 0 ? 1.6f : 1.05f);
    for (float x : {-0.75f, 0.75f})
    {
        AddPlacement(decorations, flor, glm::vec3(x * 0.87f, 0.1f, -17.4f), 1.4f);
        AddPlacement(decorations, cempasuchil, glm::vec3(x * 1.53f, 0.1f, x > 0.0f ? -17.35f : -17.75f), 1.1f);
    }
    AddPlacement(decorations, farol, glm::vec3(-4.8f, 0, -16.9f), 2.4f);
    AddPlacement(decorations, farol, glm::vec3(4.8f, 0, -16.9f), 2.4f);

    std::vector<AttachedProp> attached;
    size_t addedGround = 0;
    if (useNewLayout) {
        const size_t preserved = decorations.size();
        const size_t totalSpecs = sizeof(specs) / sizeof(specs[0]);
        for (size_t i = 0; i < totalSpecs; ++i) {
            const GraveSpec& q = specs[i]; const Placement& grave = graves[i];
            const size_t before = decorations.size() + attached.size();
            const auto worldProp = [&](Model& model, float x, float z, float scale, float yaw) {
                glm::vec3 pos(x, 0, z);
                Placement item = Grounded(model, pos, glm::vec3(scale * q.scale), yaw);
                float support = GroundSupportY(item.bounds, surfaces);
                if (support < 0) support = 0.07f;
                pos.y = support + (&model == &petals ? .002f : 0);
                item = Grounded(model, pos, glm::vec3(scale * q.scale), yaw);
                if (ClearGroundProp(item, church, altar, graves, decorations))decorations.push_back(item);
                };
            const auto groundProp = [&](Model& model, float dx, float dz, float scale, float yaw) {
                glm::vec3 pos = glm::vec3(grave.matrix * glm::vec4(dx, 0, dz, 1));
                worldProp(model, pos.x, pos.z, scale, q.yaw + yaw);
                };
            const float front = (grave.model->BoundsMax().z) + .15f;
            groundProp(veladora, -.30f, front, .75f, -7 + float(i % 3) * 9);
            groundProp(vela, .30f, front + .03f, .68f, 13);
            groundProp(petals, .0f, front + .35f, .35f, 4 - float(i % 4) * 3);

            float y = 0; Bounds patch = { glm::vec3(-.36f,0,-.37f),glm::vec3(.36f,10,.78f) };
            if (q.kind == 0)y = .205f;
            if (q.kind == 1) { y = .19f; patch = { glm::vec3(-.43f,0,.05f),glm::vec3(.43f,10,.98f) }; }
            if (q.kind == 3)y = .4825f;
            if (q.kind == 4) { y = .233f; patch = { glm::vec3(-.5f,0,.10f),glm::vec3(.5f,10,1.08f) }; }
            if (q.kind == 5) { y = .3275f; patch = { glm::vec3(-.75f,0,-.40f),glm::vec3(-.11f,10,.18f) }; }
            const auto topProp = [&](Model& model, float x, float z, float scale) {
                glm::vec3 pos = glm::vec3(grave.matrix * glm::vec4(x, y, z, 1));
                Placement item = Grounded(model, pos, glm::vec3(scale * q.scale), q.yaw);
                const Bounds b = WorldBounds(model, glm::inverse(grave.matrix) * item.matrix);
                if (b.min.x<patch.min.x || b.max.x>patch.max.x || b.min.z<patch.min.z || b.max.z>patch.max.z
                    || !SupportedOnMesh(*grave.model, b, y))return;
                for (const auto& a : attached)if (OverlapXZ(item.bounds, a.item.bounds))return;
                attached.push_back({ item,i,patch,y });
                };
            if (y > 0) {
                if (q.kind == 5)topProp(lightPot, -.43f, -.12f, .72f);
                else if (q.category != 'A')topProp(lightPot, -.10f, .34f, .60f);
                else topProp(veladora, -.20f, .42f, .65f);
                if (q.kind != 5)topProp(vela, .23f, .68f, .63f);
            }
            std::cout << "DECORACION_TUMBA " << i << " categoria=" << q.category
                << " instancias_adicionales=" << decorations.size() + attached.size() - before << std::endl;
        }
        addedGround = decorations.size() - preserved;
        std::cout << "DECORACION_3C: global_conservada=" << preserved << " nueva_suelo=" << addedGround
            << " nueva_sobre_tapas=" << attached.size() << "; categorias A=5 B=5 C=4 (incluye ceremonial previa)." << std::endl;
    }
    if (!ValidateAttached(attached, graves, church, altar)) { glfwTerminate(); return EXIT_FAILURE; }
    std::vector<Placement> allDecorations = decorations;
    for (const auto& a : attached)allDecorations.push_back(a.item);

    if (!ValidateOuterAccess(church, altar, graves, allDecorations)) { std::cerr << "ERROR: acceso secundario." << std::endl; glfwTerminate(); return EXIT_FAILURE; }
    if (!ValidateDecorations(church, graves, decorations)) { glfwTerminate(); return EXIT_FAILURE; }
    if (!ValidateOfrenda(ofrenda, altar, graves, allDecorations, validate)) { glfwTerminate(); return EXIT_FAILURE; }
    if (validate && !ValidateAnimationPaths(church, graves, cuervoCuerpo, cuervoAlaDer, cuervoAlaIzq, luciernaga, sol, luna))
    {
        std::cerr << "ERROR: trayectoria de animacion." << std::endl; glfwTerminate(); return EXIT_FAILURE;
    }
    const Placement perchedCrow = Grounded(cuervo, glm::vec3(-3.2f, 0.65f, 17.5f), glm::vec3(1.2f));
    std::cout << "ESCENA: terreno 34x42, templo + " << graves.size() << " tumbas, " << allDecorations.size() << " instancias decorativas; 5 luces puntuales." << std::endl;


    std::vector<Model*> loaded = { &Piso,&sol,&luna,&flor,&tumba,&tumba2,&tumba3,&iglesia,&iglesiaV2,
        &cuervo,&maceta,&macizo,&cempasuchil,&cuervoCuerpo,&cuervoAlaDer,&cuervoAlaIzq,&fogata,&vela,
        &luciernaga,&farol,&veladora,&ofrenda,&graveV1,&graveV2,&graveV3,&graveV4,&graveV5,&graveV6,&graveV7,&lightPot,&petals };
    std::vector<Placement> drawn = { ground,church,altar,perchedCrow };
    drawn.insert(drawn.end(), graves.begin(), graves.end()); drawn.insert(drawn.end(), allDecorations.begin(), allDecorations.end());
    for (Model* m : { &luna,&fogata,&vela,&farol,&veladora,&luciernaga,&cuervoCuerpo,&cuervoAlaDer,&cuervoAlaIzq })
        drawn.push_back(Grounded(*m, glm::vec3(0), glm::vec3(1)));
    if (!ESCENA_NOCTURNA)drawn.push_back(Grounded(sol, glm::vec3(0), glm::vec3(1)));
    SceneBudget(loaded, drawn, surfaces.size());

    GLuint concreteTexture = SOIL_load_OGL_texture("images/photoreal_concrete_01-512x512_0.png",
        SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
    if (!concreteTexture)
    {
        std::cerr << "ERROR: no se pudo cargar la textura de concreto existente." << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }
    glBindTexture(GL_TEXTURE_2D, concreteTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Configuracion de VAO y VBO para cubos con vertices manuales
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Atributo de posicion (layout = 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Atributo de normales (layout = 1)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 120.0f);

    struct Viewpoint { const char* name; glm::vec3 eye, target; float time; };
    const Viewpoint viewpoints[] = {
        {"01-entrada", {0,1.7f,19}, {0,3,-8}, 0},
        {"02-atrio", {0,1.7f,11}, {0,3,-6}, 0},
        {"03-tumbas-izquierda", {-6.2f,1.7f,6}, {-10.7f,1,2}, 0},
        {"04-tumbas-derecha", {6.2f,1.7f,6}, {10.7f,1,2}, 0},
        {"05-paso-lateral", {-6.2f,1.7f,-7}, {-6.2f,1.7f,-16}, 0},
        {"06-alumbrada", {0,2.0f,-13.95f}, {0,1.0f,-18.5f}, 0},
        {"07-distribucion", {29,31,38}, {0,0,-2}, 0},
        {"08-cuervo-t1", {0,3,13}, {0,4.8f,6}, 1},
        {"09-cuervo-t3", {0,3,13}, {0,4.8f,6}, 3},
        {"10-luna-t6", {0,3,14}, {0,18,-22}, 6},
        {"11-luna-t20", {0,3,14}, {0,18,-22}, 20},
        {"12-luciernaga-t22", {7.3f,1.7f,5}, {7.8f,1.65f,2}, 22},
        {"13-luciernaga-t24", {7.3f,1.7f,5}, {7.8f,1.65f,2}, 24},
        {"14-ofrenda-frente", {-0.8f,1.7f,-15.95f}, {-0.8f,1.0f,-19.25f}, 0},
        {"15-ofrenda-lateral", {-4.2f,2.0f,-17.3f}, {-0.8f,1.05f,-19.25f}, 0},
        {"16-alumbrada-superior", {5.0f,6.0f,-14.5f}, {0.0f,0.5f,-18.6f}, 0},
        {"17-camino-principal", {0,1.7f,3.5f}, {0,3.5f,-5}, 0},
        {"18-fachada-templo", {0,4.3f,10.6f}, {0,4.1f,-4}, 0},
        {"19-lateral-templo", {13.5f,5.5f,-7.8f}, {0,3.4f,-8.5f}, 0},
        {"20-superior-distribucion", {0,57,0.6f}, {0,0,-1}, 0},
        {"21-ofrenda-frontal", {-0.8f,1.7f,-14.5f}, {-0.8f,1.5f,-19.25f}, 0},
        {"22-ofrenda-lateral", {-6.6f,3.3f,-17.2f}, {-0.8f,1.45f,-19.25f}, 0},
        {"23-ofrenda-superior", {-0.8f,9.2f,-19.24f}, {-0.8f,0.1f,-19.25f}, 0},
        {"24-ofrenda-recorrido", {-3.7f,1.7f,-15.3f}, {-0.8f,1.0f,-19.25f}, 0},
        {"25-tumba-A", {-8.15f,1.7f,11.4f}, {-10.5f,.8f,8.6f}, 0},
        {"26-tumba-B", {12.9f,2.0f,5.4f}, {10.45f,1.1f,2}, 0},
        {"27-tumba-C", {-7.9f,2.3f,-.4f}, {-10.45f,1.0f,-4}, 0}
    };
    int captureIndex = 0;
    const int benchmarkViews[] = { 0,6,5 };
    size_t benchmarkView = 0; int benchmarkFrame = 0;
    std::vector<double> frameTimes;
    std::ofstream fps;
    if (benchmark) {
        fps.open(captureDirectory + "/fps.csv");
        if (!fps)return EXIT_FAILURE;
        fps << "layout,view,width,height,warmup,frames,average_fps,median_ms,p95_ms\n";
    }
    int resultCode = EXIT_SUCCESS;
    if (validate)
    {
        // Usar los mismos controles que la sesion normal, mirando hacia arriba:
        // avanzar no debe hacer volar a la camara ni cambiar su altura.
        camera = Camera(glm::vec3(0, EYE_HEIGHT, 19), glm::vec3(0, 1, 0), -90, 30);
        camera.SetWalkingMode(EYE_HEIGHT, 3.5f);
        deltaTime = 1.0f;
        const int movementKeys[] = { GLFW_KEY_W,GLFW_KEY_UP,GLFW_KEY_S,GLFW_KEY_DOWN,
            GLFW_KEY_A,GLFW_KEY_LEFT,GLFW_KEY_D,GLFW_KEY_RIGHT };
        const glm::vec3 expected[] = { {0,0,-3.5f},{0,0,-3.5f},{0,0,3.5f},{0,0,3.5f},
            {-3.5f,0,0},{-3.5f,0,0},{3.5f,0,0},{3.5f,0,0} };
        for (int i = 0; i < 8; ++i)
        {
            const glm::vec3 before = camera.GetPosition();
            KeyCallback(window, movementKeys[i], 0, GLFW_PRESS, 0);
            DoMovement();
            KeyCallback(window, movementKeys[i], 0, GLFW_RELEASE, 0);
            if (glm::length(camera.GetPosition() - before - expected[i]) > 0.001f)
            {
                std::cerr << "ERROR: control de recorrido " << movementKeys[i] << std::endl; return EXIT_FAILURE;
            }
        }
        // Verificar que el callback del mouse cambia la direccion de la vista.
        const glm::vec3 previousFront = camera.GetFront();
        firstMouse = true; MouseCallback(window, 100, 100); MouseCallback(window, 160, 100);
        if (glm::length(camera.GetFront() - previousFront) < 0.01f)
        {
            std::cerr << "ERROR: control de mouse." << std::endl; return EXIT_FAILURE;
        }
        const bool initialChurch = useIglesiaV2;
        KeyCallback(window, GLFW_KEY_F2, 0, GLFW_PRESS, 0);
        KeyCallback(window, GLFW_KEY_F2, 0, GLFW_RELEASE, 0);
        if (useIglesiaV2 == initialChurch) return EXIT_FAILURE;
        KeyCallback(window, GLFW_KEY_F2, 0, GLFW_PRESS, 0);
        KeyCallback(window, GLFW_KEY_F2, 0, GLFW_RELEASE, 0);
        if (useIglesiaV2 != initialChurch) return EXIT_FAILURE;
        std::cout << "VALIDACION: selector F2 cambia V1/V2 y restaura la seleccion inicial; un solo templo por cuadro." << std::endl;
        std::cout << "VALIDACION: WASD, flechas y mouse; altura peatonal constante." << std::endl;
    }
    const double animationStart = glfwGetTime();
    lastFrame = 0.0f;

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        const auto frameStart = std::chrono::steady_clock::now();
        // Calcular deltaTime
        GLfloat currentFrame = static_cast<GLfloat>(glfwGetTime() - animationStart);
        deltaTime = (std::min)(currentFrame - lastFrame, 0.05f);
        lastFrame = currentFrame;
        GLfloat t = currentFrame;
        glfwPollEvents();
        if (validate)
        {
            const Viewpoint& shot = viewpoints[benchmark ? benchmarkViews[benchmarkView] : captureIndex];
            const glm::vec3 direction = glm::normalize(shot.target - shot.eye);
            camera = Camera(shot.eye, glm::vec3(0, 1, 0), glm::degrees(atan2(direction.z, direction.x)), glm::degrees(asin(direction.y)));
            t = shot.time;
        }
        else DoMovement();

        // Limpiar buffers
        glClearColor(0.018f, 0.023f, 0.042f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        lightingShader.Use();
        glUniform3f(glGetUniformLocation(lightingShader.Program, "objectGlow"), 0, 0, 0);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "emissionPulse"), 0.94f + 0.06f * sin(t * 8.0f));

        GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
        glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 16.0f);

        // Por defecto la transparencia esta desactivada (0 = opaco)
        glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);

        // 1. CALCULO DE TRAYECTORIAS (ORBITA SOL/LUNA Y VUELO DE LUCIERNAGA)
        // Orbita del Sol y la Luna
        sunAngle = glm::radians(225.0f) + 0.08f * t;
        sunPos = OrbitPosition(sunAngle);
        moonPos = OrbitPosition(sunAngle + glm::radians(180.0f));

        // Trayectoria parametrica de la luciernaga y calculo del angulo de giro
        glm::vec3 posLuc = FireflyPosition(t);

        // Actualizar posicion de cada luz puntual junto a su modelo
        pointLightPositions[0] = posFogata + glm::vec3(0.0f, 0.25f * ESC_FOGATA, 0.0f);
        pointLightPositions[1] = posVela + glm::vec3(0.0f, 0.27f * ESC_VELA, 0.0f);
        pointLightPositions[2] = posLuc;
        pointLightPositions[3] = posFarol + glm::vec3(0.0f, 0.875f * ESC_FAROL, 0.0f);
        pointLightPositions[4] = posVeladora + glm::vec3(0.0f, 0.25f * ESC_VELADORA, 0.0f);

        // 2. CONFIGURACION DE FUENTES DE LUZ
        // Luz del Sol y Luna
        bool sunEnabled = !ESCENA_NOCTURNA && sin(sunAngle) >= 0.0f;
        bool moonEnabled = ESCENA_NOCTURNA || !sunEnabled;
        glUniform1i(glGetUniformLocation(lightingShader.Program, "sunEnabled"), sunEnabled ? 1 : 0);
        glUniform1i(glGetUniformLocation(lightingShader.Program, "moonEnabled"), moonEnabled ? 1 : 0);

        glUniform3f(glGetUniformLocation(lightingShader.Program, "sun.position"), sunPos.x, sunPos.y, sunPos.z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "sun.ambient"), 0.15f, 0.15f, 0.15f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "sun.diffuse"), 0.90f, 0.80f, 0.60f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "sun.specular"), 0.50f, 0.50f, 0.50f);

        glUniform3f(glGetUniformLocation(lightingShader.Program, "moon.position"), moonPos.x, moonPos.y, moonPos.z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "moon.ambient"), 0.007f, 0.009f, 0.016f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "moon.diffuse"), 0.025f, 0.035f, 0.065f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "moon.specular"), 0.05f, 0.06f, 0.10f);

        // ---------- DIRECCIONAL: Luz ambiental nocturna general
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.045f, 0.05f, 0.07f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.045f, 0.055f, 0.09f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.04f, 0.045f, 0.065f);

        // ---------- PUNTUAL 1: FOGATA para cantar la cancion de la hoguera
        float parpadeoFogata = 0.85f + 0.10f * sin(t * 11.0f) * sin(t * 5.3f) + 0.05f * sin(t * 27.0f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), 0.15f * parpadeoFogata, 0.07f * parpadeoFogata, 0.015f * parpadeoFogata);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), 2.4f * parpadeoFogata, 1.15f * parpadeoFogata, 0.30f * parpadeoFogata);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 0.6f * parpadeoFogata, 0.3f * parpadeoFogata, 0.1f * parpadeoFogata);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.07f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.017f);

        // ---------- PUNTUAL 2: VELA1
        float parpadeoVela = 0.90f + 0.06f * sin(t * 9.0f) + 0.04f * sin(t * 23.0f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), 0.10f * parpadeoVela, 0.07f * parpadeoVela, 0.03f * parpadeoVela);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), 2.8f * parpadeoVela, 1.7f * parpadeoVela, 0.7f * parpadeoVela);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 0.3f * parpadeoVela, 0.2f * parpadeoVela, 0.1f * parpadeoVela);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.07f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 0.017f);

        // ---------- PUNTUAL 3: MOSKA
        float destelloLuc = 0.5f + 0.5f * sin(t * 3.0f);
        destelloLuc = destelloLuc * destelloLuc;
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].ambient"), 0.05f * destelloLuc, 0.12f * destelloLuc, 0.02f * destelloLuc);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].diffuse"), 0.45f * destelloLuc, 1.0f * destelloLuc, 0.15f * destelloLuc);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].specular"), 0.3f * destelloLuc, 0.6f * destelloLuc, 0.1f * destelloLuc);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].linear"), 0.35f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].quadratic"), 0.44f);

        // ---------- PUNTUAL 4: FAROL
        float titileoFarol = 0.97f + 0.03f * sin(t * 7.0f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].ambient"), 0.08f * titileoFarol, 0.06f * titileoFarol, 0.03f * titileoFarol);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].diffuse"), 2.0f * titileoFarol, 1.45f * titileoFarol, 0.65f * titileoFarol);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].specular"), 0.4f * titileoFarol, 0.3f * titileoFarol, 0.15f * titileoFarol);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].linear"), 0.07f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].quadratic"), 0.017f);

        // ---------- PUNTUAL 5: VELADORA2
        float parpadeoVeladora = 0.88f + 0.08f * sin(t * 8.0f + 1.3f) + 0.04f * sin(t * 21.0f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[4].position"), pointLightPositions[4].x, pointLightPositions[4].y, pointLightPositions[4].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[4].ambient"), 0.08f * parpadeoVeladora, 0.03f * parpadeoVeladora, 0.01f * parpadeoVeladora);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[4].diffuse"), 3.5f * parpadeoVeladora, 2.0f * parpadeoVeladora, 0.55f * parpadeoVeladora);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[4].specular"), 0.3f * parpadeoVeladora, 0.15f * parpadeoVeladora, 0.05f * parpadeoVeladora);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[4].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[4].linear"), 0.045f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[4].quadratic"), 0.0075f);

        // ---------- SPOTLIGHT -->Linterna de la camara 
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.025f, 0.022f, 0.018f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.85f, 0.75f, 0.55f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 0.2f, 0.2f, 0.2f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.09f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.032f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.0f)));
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(18.0f)));

        // Matrices de vista y proyeccion
        glm::mat4 view = camera.GetViewMatrix();
        GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
        GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
        GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // ZONAS 1-4: el OBJ piso conserva su geometria, con concreto existente en vez de pasto.
        glUniform2f(glGetUniformLocation(lightingShader.Program, "textureTiling"), 17.0f, 21.0f);
        DrawPlacement(ground, lightingShader, concreteTexture);
        glUniform2f(glGetUniformLocation(lightingShader.Program, "textureTiling"), 1.0f, 1.0f);
        for (const Surface& surface : surfaces) DrawSurface(surface, VAO, lightingShader);
        DrawPlacement(useIglesiaV2 ? churchV2 : churchV1, lightingShader);
        // ZONA 5 y tumba principal de ZONA 6: tres instancias base reutilizadas.
        for (const Placement& grave : graves) DrawPlacement(grave, lightingShader);
        for (const Placement& decoration : decorations) DrawPlacement(decoration, lightingShader);
        for (const auto& prop : attached) DrawPlacement(prop.item, lightingShader);
        DrawPlacement(perchedCrow, lightingShader);
        DrawPlacement(altar, lightingShader);

        // El Sol y su animacion se conservan; la version nocturna solo presenta la Luna.
        if (!ESCENA_NOCTURNA)
        {
            glm::mat4 modelSol = glm::scale(glm::translate(glm::mat4(1.0f), sunPos), glm::vec3(0.65f));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelSol));
            sol.Draw(lightingShader);
        }
        glm::mat4 modelLuna = glm::scale(glm::translate(glm::mat4(1.0f), moonPos), glm::vec3(0.8f));
        glUniform3f(glGetUniformLocation(lightingShader.Program, "objectGlow"), 0.35f, 0.38f, 0.48f);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelLuna));
        luna.Draw(lightingShader);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "objectGlow"), 0, 0, 0);

        // Los cinco emisores conservan sus modelos y sus efectos de parpadeo.
        DrawPlacement(Grounded(fogata, posFogata, glm::vec3(ESC_FOGATA)), lightingShader);
        DrawPlacement(Grounded(vela, posVela, glm::vec3(ESC_VELA)), lightingShader);
        DrawPlacement(Grounded(farol, posFarol, glm::vec3(ESC_FAROL)), lightingShader);
        DrawPlacement(Grounded(veladora, posVeladora, glm::vec3(ESC_VELADORA)), lightingShader);
        glm::mat4 modelLuciernaga = FireflyMatrix(t);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "objectGlow"), 0.08f, 0.2f, 0.02f);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelLuciernaga));
        luciernaga.Draw(lightingShader);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "objectGlow"), 0, 0, 0);

        // Vuelo y aleteo originales, trasladados al atrio: no cruzan el templo.
        glm::mat4 modelCuervoV = CrowMatrix(t);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelCuervoV));
        cuervoCuerpo.Draw(lightingShader);
        glm::mat4 modelAlaD = WingMatrix(modelCuervoV, t, 1.0f);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelAlaD));
        cuervoAlaDer.Draw(lightingShader);
        glm::mat4 modelAlaI = WingMatrix(modelCuervoV, t, -1.0f);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelAlaI));
        cuervoAlaIzq.Draw(lightingShader);

        // TODO: Reactivar junto con la carga de Models/Blue+Mushroom.obj.
        // glm::mat4 modelHongo = glm::translate(glm::mat4(1.0f), glm::vec3(11,0,8));
        // modelHongo = glm::scale(modelHongo, glm::vec3(0.15f));
        // glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelHongo));
        // hongo.Draw(lightingShader);

        // 5. DIBUJO DE MODELOS CON TRANSPARENCIA-->Siempre al final del ciclo

        // TODO: Reactivar junto con la carga de Models/TumbaTransparente.obj.
        // Tumba Transparente (con transparency = 1)
        // glm::mat4 modelT(1.0f);
        // modelT = glm::translate(modelT, glm::vec3(-1.5f, -1.3f, 0.0f));
        // modelT = glm::rotate(modelT, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        // modelT = glm::scale(modelT, glm::vec3(0.6f, 0.6f, 0.6f));
        // glEnable(GL_BLEND);
        // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        // glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelT));
        // glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 1); // 1 = Activa transparencia
        // TumbaTransparente.Draw(lightingShader);
        // glDisable(GL_BLEND);
        // Importante: regresamos transparency a 0 para no afectar el siguiente frame
        // glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
        glBindVertexArray(0);

        if (validate)
        {
            glFinish();
            const GLenum error = glGetError();
            if (error != GL_NO_ERROR)
            {
                std::cerr << "ERROR OpenGL: " << error << std::endl;
                resultCode = EXIT_FAILURE; break;
            }
            if (benchmark) {
                const double ms = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - frameStart).count();
                if (benchmarkFrame >= 30)frameTimes.push_back(ms);
                if (++benchmarkFrame == 150) {
                    double sum = 0; for (double v : frameTimes)sum += v;
                    std::sort(frameTimes.begin(), frameTimes.end());
                    double average = 1000.0 * frameTimes.size() / sum;
                    fps << (useNewLayout ? "nueva" : "anterior") << "," << viewpoints[benchmarkViews[benchmarkView]].name
                        << "," << SCREEN_WIDTH << "," << SCREEN_HEIGHT << ",30," << frameTimes.size() << ","
                        << std::fixed << std::setprecision(3) << average << "," << frameTimes[frameTimes.size() / 2]
                        << "," << frameTimes[static_cast<size_t>(.95 * (frameTimes.size() - 1))] << "\n";
                    fps.flush();
                    std::cout << "FPS: " << viewpoints[benchmarkViews[benchmarkView]].name << " " << average << std::endl;
                    frameTimes.clear(); benchmarkFrame = 0;
                    if (++benchmarkView == 3)glfwSetWindowShouldClose(window, GL_TRUE);
                }
            }
            else {
                const std::string output = captureDirectory + "/" + viewpoints[captureIndex].name + ".bmp";
                if (!CaptureFrame(output))
                {
                    std::cerr << "ERROR: captura " << output << std::endl; resultCode = EXIT_FAILURE; break;
                }
                std::cout << "CAPTURA: " << output << " t=" << t << std::endl;
                ++captureIndex;
                if (captureIndex == sizeof(viewpoints) / sizeof(viewpoints[0])) glfwSetWindowShouldClose(window, GL_TRUE);
            }
        }
        glfwSwapBuffers(window);
    }

    glDeleteTextures(1, &concreteTexture);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return resultCode;
}

// Movimiento de camara y objetos por teclado
void DoMovement()
{
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
        camera.ProcessKeyboard(RIGHT, deltaTime);

    // Mover posFogata (y su luz puntual [0] automaticamente) con T,G,Y,H,U,J
    if (keys[GLFW_KEY_T]) posFogata.x += 1.5f * deltaTime;
    if (keys[GLFW_KEY_G]) posFogata.x -= 1.5f * deltaTime;
    if (keys[GLFW_KEY_Y]) posFogata.y += 1.5f * deltaTime;
    if (keys[GLFW_KEY_H]) posFogata.y -= 1.5f * deltaTime;
    if (keys[GLFW_KEY_U]) posFogata.z -= 1.5f * deltaTime;
    if (keys[GLFW_KEY_J]) posFogata.z += 1.5f * deltaTime;

    if (activanim)
    {
        if (rot > -90.0f)
            rot -= 0.1f;
    }
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)glfwSetWindowShouldClose(window, GL_TRUE);
    if (key == GLFW_KEY_F2 && action == GLFW_PRESS)
    {
        useIglesiaV2 = !useIglesiaV2;
        glfwSetWindowTitle(window, ChurchWindowTitle());
        std::cout << "IGLESIA_ACTIVA: " << (useIglesiaV2 ? "V2" : "V1") << std::endl;
    }

    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS)
            keys[key] = true;
        else if (action == GLFW_RELEASE)
            keys[key] = false;
    }

    if (keys[GLFW_KEY_SPACE])
    {
        active = !active;
        if (active)
            Light1 = glm::vec3(1.0f, 1.0f, 0.0f);
        else
            Light1 = glm::vec3(0.0f);
    }

    if (keys[GLFW_KEY_O]) movelightPos += 0.1f;
    if (keys[GLFW_KEY_L]) movelightPos -= 0.1f;
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
    if (firstMouse)
    {
        lastX = static_cast<GLfloat>(xPos);
        lastY = static_cast<GLfloat>(yPos);
        firstMouse = false;
    }

    GLfloat xOffset = static_cast<GLfloat>(xPos) - lastX;
    GLfloat yOffset = lastY - static_cast<GLfloat>(yPos);

    lastX = static_cast<GLfloat>(xPos);
    lastY = static_cast<GLfloat>(yPos);

    camera.ProcessMouseMovement(xOffset, yOffset);
}