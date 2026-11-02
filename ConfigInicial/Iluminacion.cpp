// Proyecto Final / Base Practicas 8 y 9
// Equipo 12
// Números de cuenta: 421122006 | 320173985

#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <vector>

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
Camera camera(glm::vec3(0.0f, 1.7f, 19.0f), glm::vec3(0,1,0), -90.0f, -3.0f);
GLfloat lastX = WIDTH / 2.0f;
GLfloat lastY = HEIGHT / 2.0f;
bool keys[1024];
bool firstMouse = true;

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
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
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
    return glm::vec3(cos(phase)*sunOrbitRadius,18.0f+sin(phase)*sunOrbitRadius,-22.0f);
}

glm::vec3 FireflyPosition(float t)
{
    return posLuciernaga + glm::vec3(0.7f*sin(0.6f*t),0.18f*sin(1.7f*t),0.7f*cos(0.45f*t));
}

glm::mat4 FireflyMatrix(float t)
{
    const float avanceX = 0.7f*0.6f*cos(0.6f*t);
    const float avanceZ = -0.7f*0.45f*sin(0.45f*t);
    glm::mat4 matrix = glm::translate(glm::mat4(1.0f),FireflyPosition(t));
    matrix = glm::rotate(matrix,atan2(avanceX,avanceZ),glm::vec3(0,1,0));
    return glm::scale(matrix,glm::vec3(ESC_LUCIERNAGA));
}

glm::mat4 CrowMatrix(float t)
{
    const float giro = 0.5f*t;
    glm::mat4 matrix = glm::translate(glm::mat4(1.0f),glm::vec3(4.6f*sin(giro),4.8f+0.2f*sin(t*2.0f),6.0f+3.5f*cos(giro)));
    // La tangente de la elipse orienta el cuerpo en la direccion del vuelo.
    matrix = glm::rotate(matrix,atan2(4.6f*cos(giro),-3.5f*sin(giro)),glm::vec3(0,1,0));
    return glm::scale(matrix,glm::vec3(ESC_CUERVO));
}

glm::mat4 WingMatrix(const glm::mat4& parent, float t, float side)
{
    const float aleteo = 35.0f*sin(t*6.0f);
    glm::mat4 matrix = glm::translate(parent,glm::vec3(side*0.05f,0.03f,0.02f));
    return glm::rotate(matrix,glm::radians(side*aleteo),glm::vec3(0,0,1));
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
    if (graves.size() != 9) return false;
    const Bounds centralPath = { glm::vec3(-2.0f, 0.0f, -2.6f), glm::vec3(2.0f, 1.0f, 19.0f) };
    for (size_t i = 0; i < graves.size(); ++i)
    {
        const Bounds& b = graves[i].bounds;
        if (b.min.x < -17.0f || b.max.x > 17.0f || b.min.z < -21.0f || b.max.z > 21.0f) return false;
        if (OverlapXZ(b, church.bounds) || OverlapXZ(b, centralPath)) return false;
        for (size_t j = i + 1; j < graves.size(); ++j)
            if (OverlapXZ(b, graves[j].bounds)) return false;
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
            glm::vec2 p = glm::mix(route[i-1], route[i], step / 100.0f);
            Bounds pedestrian = { glm::vec3(p.x - 0.35f, 0, p.y - 0.35f), glm::vec3(p.x + 0.35f, EYE_HEIGHT, p.y + 0.35f) };
            if (OverlapXZ(pedestrian, c)) return false;
            for (const Placement& grave : graves) if (OverlapXZ(pedestrian, grave.bounds)) return false;
        }
    std::cout << "VALIDACION: 9 tumbas (4 izquierda, 4 derecha, 1 altar), sin cruces; recorrido central y lateral libre." << std::endl;
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
    const glm::vec2 route[] = {{0,19},{0,12},{0,-1.6f},{6.2f,-1.6f},{6.2f,-15.3f},
        {0,-15.3f},{-6.2f,-15.3f},{-6.2f,-1.6f},{0,-1.6f}};
    for (size_t index = 0; index < decorations.size(); ++index)
    {
        const Bounds& b = decorations[index].bounds;
        if (b.min.x < -17 || b.max.x > 17 || b.min.z < -21 || b.max.z > 21 || b.min.y < -0.001f || OverlapXZ(b, church.bounds))
        { std::cerr << "ERROR: decoracion fuera de terreno o dentro del templo: " << index << std::endl; return false; }
        for (const Placement& grave : graves)
            if (OverlapXZ(b, grave.bounds))
            { std::cerr << "ERROR: decoracion intersecta una tumba: " << index << std::endl; return false; }
        for (size_t segment = 1; segment < sizeof(route)/sizeof(route[0]); ++segment)
            for (int step=0; step<=100; ++step)
            {
                glm::vec2 p = glm::mix(route[segment-1],route[segment],step/100.0f);
                Bounds pedestrian = {glm::vec3(p.x-0.35f,0,p.y-0.35f),glm::vec3(p.x+0.35f,EYE_HEIGHT,p.y+0.35f)};
                if (OverlapXZ(pedestrian,b))
                { std::cerr << "ERROR: decoracion bloquea el recorrido: " << index << std::endl; return false; }
            }
    }
    std::cout << "VALIDACION: decoraciones apoyadas, dentro del terreno, sin invadir tumbas, templo ni recorrido peatonal." << std::endl;
    return true;
}

bool ValidateAnimationPaths(const Placement& church, const std::vector<Placement>& graves,
    Model& body, Model& rightWing, Model& leftWing, Model& firefly, Model& sunModel, Model& moonModel)
{
    // 401 muestras en 200 segundos, usando las mismas matrices que el dibujado.
    for (int sample=0; sample<=400; ++sample)
    {
        const float t=sample*0.5f;
        const float phase=glm::radians(225.0f)+0.08f*t;
        const glm::mat4 parent=CrowMatrix(t);
        const Bounds moving[] = {
            WorldBounds(body,parent), WorldBounds(rightWing,WingMatrix(parent,t,1)),
            WorldBounds(leftWing,WingMatrix(parent,t,-1)), WorldBounds(firefly,FireflyMatrix(t)),
            WorldBounds(sunModel,glm::scale(glm::translate(glm::mat4(1.0f),OrbitPosition(phase)),glm::vec3(0.65f))),
            WorldBounds(moonModel,glm::scale(glm::translate(glm::mat4(1.0f),OrbitPosition(phase+glm::radians(180.0f))),glm::vec3(0.8f)))
        };
        for (const Bounds& b : moving)
        {
            if (b.min.y < 0 || (OverlapXZ(b,church.bounds) && b.min.y < church.bounds.max.y)) return false;
            for (const Placement& grave : graves)
                if (OverlapXZ(b,grave.bounds) && b.min.y < grave.bounds.max.y) return false;
        }
    }
    std::cout << "VALIDACION: cuervo, alas, luciernaga y orbitas sin cruzar suelo, templo ni tumbas en 401 muestras (200 s)." << std::endl;
    return true;
}

// TODO v1.1: acceso arquitectonico, bardas perimetrales, arboles y vegetacion.
// TODO v1.1: personajes, ofrendas adicionales, sahumerios y humo.
// TODO v1.1: objetos interactivos y audio ambiental.

int main(int argc, char** argv)
{
    const bool validate = argc == 3 && std::string(argv[1]) == "--validar-escena";
    const std::string captureDirectory = validate ? argv[2] : "";
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

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Panteon de Mixquic v1.0 - Equipo 12", nullptr, nullptr);

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
    Model iglesia((char*)"Models/iglesia.obj"); 
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

    // La validacion impide aceptar un prototipo con recursos faltantes.
    for (Model* model : {&Piso,&sol,&luna,&flor,&tumba,&tumba2,&tumba3,&iglesia,&cuervo,&maceta,
        &macizo,&cempasuchil,&cuervoCuerpo,&cuervoAlaDer,&cuervoAlaIzq,&fogata,&vela,&luciernaga,&farol,&veladora})
        if (!model->IsLoaded()) { glfwTerminate(); return EXIT_FAILURE; }

    // ETAPA 2 / ZONA 3: templo centrado por su caja real, fachada hacia +Z.
    // Planta final X [-4.48,4.48], Z [-13.715,-3.285]; altura 8.5225.
    const Placement church = Grounded(iglesia, glm::vec3(0, GROUND_Y, -8.5f), glm::vec3(0.7f));
    const Placement ground = Grounded(Piso, glm::vec3(0, GROUND_Y, 0), glm::vec3(6.8f, 1.0f, 8.4f));
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
    for (float x : {-6.2f,6.2f})
        for (float z = -14.8f; z < -2.4f; z += 1.3f)
            surfaces.push_back({ {x,0.043f,z}, {2.16f,0.006f,0.035f}, border });

    // ETAPA 3 / ZONA 5: cuatro sepulturas por lado; se reutilizan tres OBJ.
    std::vector<Placement> graves;
    Model* graveModels[] = { &tumba, &tumba2, &tumba3 };
    const float graveScales[] = { 0.67f, 0.53f, 0.65f };
    const float graveZ[] = { 8.0f, 2.0f, -4.0f, -10.0f };
    for (int side = 0; side < 2; ++side)
        for (int row = 0; row < 4; ++row)
        {
            const float x = side == 0 ? -10.7f : 10.7f;
            const int kind = (row + side) % 3;
            const float yaw = side == 0 ? 12.0f : -12.0f;
            AddPlacement(graves, *graveModels[kind], glm::vec3(x,0.07f,graveZ[row]), graveScales[kind], yaw);
            surfaces.push_back({ {x,0.035f,graveZ[row]}, {4.2f,0.07f,4.5f}, plotColor });
            // Conexiones cortas a los pasos laterales y acceso a cada sepultura.
            surfaces.push_back({ {side == 0 ? -8.0f : 8.0f,0.02f,graveZ[row]+2.25f}, {3.6f,0.04f,0.85f}, stone });
        }
    // ZONA 6: novena tumba, destacada sobre una plataforma de ofrenda.
    surfaces.push_back({ {0,0.05f,-18.45f}, {6.6f,0.1f,5.0f}, plotColor });
    AddPlacement(graves, tumba2, glm::vec3(0,0.1f,-18.9f), 0.62f);
    if (!ValidateLayout(church, graves))
    {
        std::cerr << "ERROR: interseccion en la distribucion arquitectonica." << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    // ETAPA 4: decoracion existente; cada modelo se cargo una sola vez.
    std::vector<Placement> decorations;
    // Acceso y atrio: las macetas se mantienen fuera de la franja central.
    for (float x : {-4.9f,4.9f})
        for (float z : {10.5f,14.5f})
            AddPlacement(decorations, maceta, glm::vec3(x,0.04f,z), 1.45f);
    for (float x : {-2.7f,2.7f})
        for (float z : {16.5f,8.5f,4.5f,0.5f})
            AddPlacement(decorations, macizo, glm::vec3(x,0.0f,z), 1.05f);
    for (float x : {-4.3f,4.3f})
        AddPlacement(decorations, farol, glm::vec3(x,0.04f,12.5f), 2.1f);
    AddPlacement(decorations, farol, glm::vec3(-4.0f,0,17.5f), ESC_FAROL);
    // Ofrendas pequeñas en ocho tumbas, sin invadir los caminos laterales.
    for (int side = 0; side < 2; ++side)
        for (int row = 0; row < 4; ++row)
        {
            float x = side == 0 ? -10.7f : 10.7f;
            float z = graveZ[row];
            AddPlacement(decorations, maceta, glm::vec3(x-1.6f,0.07f,z-0.8f), 1.05f, 20.0f*row);
            AddPlacement(decorations, macizo, glm::vec3(x+1.6f,0.07f,z-0.65f), 0.95f);
            AddPlacement(decorations, cempasuchil, glm::vec3(x-1.4f,0.07f,z+0.8f), 1.0f);
            for (int candle = 0; candle < 5; ++candle)
                AddPlacement(decorations, veladora, glm::vec3(x-1.28f+candle*0.64f,0.07f,z+1.65f), 1.45f);
            AddPlacement(decorations, vela, glm::vec3(x+1.45f,0.07f,z+0.8f), 1.1f);
        }
    // Fachada: flores y faroles flanquean el desembarco, sin tapar la puerta.
    for (float x : {-3.0f,3.0f})
    {
        AddPlacement(decorations, maceta, glm::vec3(x,0,-3.0f), 1.2f);
        AddPlacement(decorations, farol, glm::vec3(x*1.4f,0,-3.0f), 2.3f);
    }
    // La Alumbrada: mayor densidad de flores y veladoras; centro de la composicion.
    for (float x : {-2.2f,2.2f})
        for (float z : {-19.7f,-18.5f,-17.3f})
            AddPlacement(decorations, macizo, glm::vec3(x,0.1f,z), 1.25f);
    for (float x : {-1.35f,1.35f})
        AddPlacement(decorations, maceta, glm::vec3(x,0.1f,-18.9f), 1.2f);
    for (float x : {-2.85f,2.85f})
        for (int i = 0; i < 9; ++i)
            AddPlacement(decorations, veladora, glm::vec3(x,0.1f,-20.3f+i*0.48f), 1.6f);
    for (int row = 0; row < 2; ++row)
        for (int i = 0; i < 9; ++i)
            AddPlacement(decorations, row == 0 ? veladora : vela,
                glm::vec3(-2.4f+i*0.6f,0.1f,-16.45f-row*0.55f), row == 0 ? 1.6f : 1.05f);
    for (float x : {-0.75f,0.75f})
    {
        AddPlacement(decorations, flor, glm::vec3(x*0.87f,0.1f,-17.4f), 1.4f);
        AddPlacement(decorations, cempasuchil, glm::vec3(x*1.53f,0.1f,-17.75f), 1.1f);
    }
    AddPlacement(decorations, farol, glm::vec3(-4.8f,0,-16.9f), 2.4f);
    AddPlacement(decorations, farol, glm::vec3(4.8f,0,-16.9f), 2.4f);
    if (!ValidateDecorations(church, graves, decorations)) { glfwTerminate(); return EXIT_FAILURE; }
    if (validate && !ValidateAnimationPaths(church,graves,cuervoCuerpo,cuervoAlaDer,cuervoAlaIzq,luciernaga,sol,luna))
    { std::cerr << "ERROR: trayectoria de animacion." << std::endl; glfwTerminate(); return EXIT_FAILURE; }
    const Placement perchedCrow = Grounded(cuervo, glm::vec3(-3.2f,0.65f,17.5f), glm::vec3(1.2f));
    std::cout << "ESCENA: terreno 34x42, templo + 9 tumbas, " << decorations.size() << " instancias decorativas; 5 luces puntuales." << std::endl;

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
        {"13-luciernaga-t24", {7.3f,1.7f,5}, {7.8f,1.65f,2}, 24}
    };
    int captureIndex = 0;
    int resultCode = EXIT_SUCCESS;
    if (validate)
    {
        // Usar los mismos controles que la sesion normal, mirando hacia arriba:
        // avanzar no debe hacer volar a la camara ni cambiar su altura.
        camera = Camera(glm::vec3(0,EYE_HEIGHT,19),glm::vec3(0,1,0),-90,30);
        camera.SetWalkingMode(EYE_HEIGHT,3.5f);
        deltaTime = 1.0f;
        const int movementKeys[] = {GLFW_KEY_W,GLFW_KEY_UP,GLFW_KEY_S,GLFW_KEY_DOWN,
            GLFW_KEY_A,GLFW_KEY_LEFT,GLFW_KEY_D,GLFW_KEY_RIGHT};
        const glm::vec3 expected[] = {{0,0,-3.5f},{0,0,-3.5f},{0,0,3.5f},{0,0,3.5f},
            {-3.5f,0,0},{-3.5f,0,0},{3.5f,0,0},{3.5f,0,0}};
        for (int i=0; i<8; ++i)
        {
            const glm::vec3 before = camera.GetPosition();
            KeyCallback(window,movementKeys[i],0,GLFW_PRESS,0);
            DoMovement();
            KeyCallback(window,movementKeys[i],0,GLFW_RELEASE,0);
            if (glm::length(camera.GetPosition()-before-expected[i]) > 0.001f)
            { std::cerr << "ERROR: control de recorrido " << movementKeys[i] << std::endl; return EXIT_FAILURE; }
        }
        // Verificar que el callback del mouse cambia la direccion de la vista.
        const glm::vec3 previousFront = camera.GetFront();
        firstMouse=true; MouseCallback(window,100,100); MouseCallback(window,160,100);
        if (glm::length(camera.GetFront()-previousFront) < 0.01f)
        { std::cerr << "ERROR: control de mouse." << std::endl; return EXIT_FAILURE; }
        std::cout << "VALIDACION: WASD, flechas y mouse; altura peatonal constante." << std::endl;
    }
    const double animationStart = glfwGetTime();
    lastFrame = 0.0f;

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Calcular deltaTime
        GLfloat currentFrame = static_cast<GLfloat>(glfwGetTime() - animationStart);
        deltaTime = (std::min)(currentFrame - lastFrame, 0.05f);
        lastFrame = currentFrame;
        GLfloat t = currentFrame;
        glfwPollEvents();
        if (validate)
        {
            const Viewpoint& shot = viewpoints[captureIndex];
            const glm::vec3 direction = glm::normalize(shot.target-shot.eye);
            camera = Camera(shot.eye,glm::vec3(0,1,0),glm::degrees(atan2(direction.z,direction.x)),glm::degrees(asin(direction.y)));
            t = shot.time;
        }
        else DoMovement();

        // Limpiar buffers
        glClearColor(0.018f, 0.023f, 0.042f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        lightingShader.Use();
        glUniform3f(glGetUniformLocation(lightingShader.Program, "objectGlow"), 0,0,0);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "emissionPulse"), 0.94f + 0.06f*sin(t*8.0f));

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
        DrawPlacement(church, lightingShader);
        // ZONA 5 y tumba principal de ZONA 6: tres instancias base reutilizadas.
        for (const Placement& grave : graves) DrawPlacement(grave, lightingShader);
        for (const Placement& decoration : decorations) DrawPlacement(decoration, lightingShader);
        DrawPlacement(perchedCrow, lightingShader);

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
        glUniform3f(glGetUniformLocation(lightingShader.Program, "objectGlow"), 0,0,0);

        // Vuelo y aleteo originales, trasladados al atrio: no cruzan el templo.
        glm::mat4 modelCuervoV = CrowMatrix(t);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelCuervoV));
        cuervoCuerpo.Draw(lightingShader);
        glm::mat4 modelAlaD = WingMatrix(modelCuervoV,t,1.0f);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelAlaD));
        cuervoAlaDer.Draw(lightingShader);
        glm::mat4 modelAlaI = WingMatrix(modelCuervoV,t,-1.0f);
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
                resultCode=EXIT_FAILURE; break;
            }
            const std::string output = captureDirectory + "/" + viewpoints[captureIndex].name + ".bmp";
            if (!CaptureFrame(output))
            { std::cerr << "ERROR: captura " << output << std::endl; resultCode=EXIT_FAILURE; break; }
            std::cout << "CAPTURA: " << output << " t=" << t << std::endl;
            ++captureIndex;
            if (captureIndex == sizeof(viewpoints)/sizeof(viewpoints[0])) glfwSetWindowShouldClose(window,GL_TRUE);
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

    if (key >= 0 && key < 1024){
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
