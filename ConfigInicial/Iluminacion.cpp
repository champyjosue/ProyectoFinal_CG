// Proyecto Final / Base Practicas 8 y 9
// Equipo 12
// Números de cuenta: 421122006 | 320173985

#include <iostream>
#include <cmath>
#include <string>

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
Camera camera(glm::vec3(0.0f, 0.0f, 6.0f));
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

// TRAYECTORIA DE ORBITA: SOL Y LUNA (De Practica 8)
glm::vec3 sunPos(0.0f, 2.5f, -2.0f);
glm::vec3 moonPos(0.0f, -2.5f, -2.0f);
float sunAngle = 0.0f;
float sunOrbitRadius = 10.0f;

// POSICIONES Y ESCALAS DE MODELOS LUMINOSOS (De Practica 9)
glm::vec3 posFogata(1.0f, -1.0f, 0.6f);
glm::vec3 posVela(-0.55f, -1.0f, 0.45f);
glm::vec3 posLuciernaga(0.2f, -0.45f, 0.9f); // Centro del recorrido de la luciernaga
glm::vec3 posFarol(-1.6f, -1.0f, -0.2f);
glm::vec3 posVeladora(-0.2f, -1.0f, 1.0f);

const float ESC_FOGATA = 1.0f;
const float ESC_VELA = 1.0f;
const float ESC_LUCIERNAGA = 3.0f;
const float ESC_FAROL = 1.0f;
const float ESC_VELADORA = 1.0f;

glm::vec3 posIglesia(0.0f, -1.0f, -8.0f);     // el frente mira hacia +Z (hacia la camara)
const float ESC_IGLESIA = 0.6f;
glm::vec3 posCuervo(0.9f, 1.0f, -1.0f);
const float ESC_CUERVO = 2.0f;
glm::vec3 posMaceta1(-2.4f, -1.0f, 1.6f);
glm::vec3 posMaceta2(2.9f, -1.0f, 1.2f);
glm::vec3 posMaceta3(-1.2f, -1.0f, 2.8f);
const float ESC_MACETA = 1.5f;
glm::vec3 posMacizo1(-2.0f, -1.0f, -0.9f);
glm::vec3 posMacizo2(3.2f, -1.0f, -1.4f);
const float ESC_FLOR = 1.5f;

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

// PERSONAJES ANIMADOS =====================
const float SUELO_Y = -1.0f;
const float ESC_PERSONA = 1.0f;   // las personas miden maso 0.9
const float ESC_CATRINA = 1.0f;   // la catrina mide maso 1.15

// Cada pose son 16 angulos (grados) en este orden:
enum {
    J_RAIZ, J_TORSO, J_CAB_X, J_CAB_Y,
    J_IZQ_PITCH, J_IZQ_ABD, J_IZQ_GIRO, J_IZQ_CODO,
    J_DER_PITCH, J_DER_ABD, J_DER_GIRO, J_DER_CODO,
    J_PIZQ_CAD, J_PIZQ_ROD, J_PDER_CAD, J_PDER_ROD
};
// J_RAIZ es la altura de la cadera (no es angulo). Torso/cabeza: positivo = adelante.
// Brazo/pierna: negativo = adelante. Rodilla: positivo = pantorrilla atras. Codo: negativo = adelante.

float POSE_NEUTRA[16] = { 0,0,0,0,        0,0,0,0,            0,0,0,0,              0,0, 0,0 };
float POSE_ORACION[16] = { 0,0,12,0,       -14,-27,-26,-81,    -14,-27,-26,-81,      0,0, 0,0 };
float POSE_ORACION_BAJA[16] = { 0,0,24,0,       -14,-27,-26,-81,    -14,-27,-26,-81,      0,0, 0,0 };
float POSE_FRENTE[16] = { 0,0,0,0,        -5,-5,0,-20,        -104,3,-49,-58,       0,0, 0,0 };
float POSE_PECHO[16] = { 0,0,5,0,        -5,-5,0,-20,        -2,-41,-19,-85,       0,0, 0,0 };
float POSE_HOMBRO_IZQ[16] = { 0,0,5,0,        -5,-5,0,-20,        -84,-2,-71,-5,        0,0, 0,0 };
float POSE_HOMBRO_DER[16] = { 0,0,5,0,        -5,-5,0,-20,        -9,-2,-5,-140,        0,0, 0,0 };
float POSE_ARRODILLADO[16] = { -0.17f,8,18,0,  -14,-27,-26,-81,    -14,-27,-26,-81,      0,90, 0,90 };
float POSE_PONER_FLOR[16] = { -0.17f,45,25,0, -30,-5,0,-30,       -70,6,0,-15,          0,90, 0,90 };
float POSE_VELADORA[16] = { -0.17f,30,20,0, -20,-5,0,-40,       -70,6,0,-20,          0,90, 0,90 };

// Personajes: 0 caminante, 1 flor, 2 veladora, 3 rezo, 4 arrodillado
float pose[5][16];   // angulos actuales de cada personaje (empiezan en 0 = neutra)
glm::vec3 posPersona[5] = {
    glm::vec3(-3.0f, 0.0f, 7.4f),      // 0 caminante (punto A de su ruta)
    glm::vec3(1.35f, 0.0f, 4.1f),      // 1 flor 
    glm::vec3(-0.355f, 0.0f, 5.42f),   // 2 veladora 
    glm::vec3(0.0f, 0.0f, 4.15f),      // 3 rezo 
    glm::vec3(-2.75f, 0.0f, 4.15f)     // 4 arrodillado 
};
float yawPersona[5] = { 90.0f, 180.0f, 180.0f, 180.0f, 180.0f };  // 0 mira a +Z, 180 mira a -Z (hacia las tumbas)

// --- Caminante (maquina de estados como el perrito de la Practica 11)
const int RUTA_PUNTOS = 2;
glm::vec3 rutaCam[RUTA_PUNTOS] = { glm::vec3(-3.0f, 0.0f, 3.4f), glm::vec3(3.0f, 0.0f, 3.4f) };
int camAnim = 1;            // 1 = AVANZAR, 2 = GIRAR
int camDestino = 1;
float camTargetYaw = 0.0f;
float camFase = 0.0f;
bool camCaminando = true;   // tecla 1 lo pausa / reanuda
float velCaminar = 0.7f;
float velGiro = 140.0f;

// --- Flor
int florAnim = 1;
float tFlor = 0.0f;
bool florEnMano = true;
bool florSuelta = false;
glm::vec3 florPos(0.0f);
float florYaw = 180.0f;
glm::mat4 manoDer[5];       // matriz de la mano derecha de cada personaje (para colgar objetos)

// --- Veladora
int veladoraAnim =1;
float tVeladora = 0.0f;
bool cerilloEnMano = false;
float intensidadVeladora = 0.0f;   // 0 apagada, 1 encendida

// --- Arrodillado
int arrodAnim = 1;
float tArrod = 0.0f;

// --- Rezo / persignarse (KEYFRAMES)
float* KFRezo[10] = { POSE_NEUTRA, POSE_ORACION, POSE_ORACION_BAJA, POSE_FRENTE, POSE_PECHO,
                      POSE_HOMBRO_IZQ, POSE_HOMBRO_DER, POSE_ORACION_BAJA, POSE_ORACION_BAJA, POSE_NEUTRA };
float KFRezoDur[10] = { 0.0f, 1.2f, 1.0f, 1.0f, 0.7f, 0.7f, 0.7f, 1.0f, 1.5f, 1.2f };  // seg. desde el frame anterior
bool playRezo = true;
int rezoIndex = 0;
float tRezo = 0.0f;

// --- Catrina
glm::vec3 posCatrina(3.2f, -1.0f, 4.0f);
float yawCatrina = 0.0f;
// ===============================================================

int main()
{
    // Init GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Proyecto CG - Equipo 12", nullptr, nullptr);

    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

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

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_DEPTH_TEST);

    // Compilacion de Shaders
    Shader shader("Shader/modelLoading.vs", "Shader/modelLoading.frag");
    Shader lampShader("Shader/lamp.vs", "Shader/lamp.frag");
    Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");

    // CARGA DE MODELOS
    Model Piso((char*)"Models/piso.obj");
    Model TumbaTransparente((char*)"Models/TumbaTransparente.obj");
    Model sol((char*)"Models/SunCute.obj");
    Model luna((char*)"Models/Luna.obj");
    Model flor((char*)"Models/cartoon_flower.obj");
    Model hongo((char*)"Models/Blue+Mushroom.obj");
    Model tumba((char*)"Models/Tumba.obj");
    Model tumba2((char*)"Models/Tumba2.obj");
    Model tumba3((char*)"Models/Tumba3.obj");
    // otros modelos para decorar panteon
    Model iglesia((char*)"Models/iglesia.obj");
    Model cuervo((char*)"Models/cuervo.obj");
    Model maceta((char*)"Models/maceta_cempasuchil.obj");
    Model macizo((char*)"Models/cempasuchil_macizo.obj");
    Model cuervoCuerpo((char*)"Models/cuervo_vuelo_cuerpo.obj");
    Model cuervoAlaDer((char*)"Models/cuervo_ala_der.obj");
    Model cuervoAlaIzq((char*)"Models/cuervo_ala_izq.obj");

    // Modelos luminosos
    Model fogata((char*)"Models/fogata.obj");
    Model vela((char*)"Models/vela.obj");
    Model luciernaga((char*)"Models/luciernaga.obj");
    Model farol((char*)"Models/farol.obj");
    Model veladora((char*)"Models/veladora.obj");

    // Personajes animados (piezas) ===============================
    Model CamTorso((char*)"Models/PCaminante_Torso.obj");
    Model CamCabeza((char*)"Models/PCaminante_Cabeza.obj");
    Model CamBrazo((char*)"Models/PCaminante_Brazo.obj");
    Model CamAntebrazo((char*)"Models/PCaminante_Antebrazo.obj");
    Model CamMuslo((char*)"Models/PCaminante_Muslo.obj");
    Model CamPantorrilla((char*)"Models/PCaminante_Pantorrilla.obj");

    Model FlTorso((char*)"Models/PFlor_Torso.obj");
    Model FlCabeza((char*)"Models/PFlor_Cabeza.obj");
    Model FlBrazo((char*)"Models/PFlor_Brazo.obj");
    Model FlAntebrazo((char*)"Models/PFlor_Antebrazo.obj");
    Model FlMuslo((char*)"Models/PFlor_Muslo.obj");
    Model FlPantorrilla((char*)"Models/PFlor_Pantorrilla.obj");

    Model VelTorso((char*)"Models/PVeladora_Torso.obj");
    Model VelCabeza((char*)"Models/PVeladora_Cabeza.obj");
    Model VelBrazo((char*)"Models/PVeladora_Brazo.obj");
    Model VelAntebrazo((char*)"Models/PVeladora_Antebrazo.obj");
    Model VelMuslo((char*)"Models/PVeladora_Muslo.obj");
    Model VelPantorrilla((char*)"Models/PVeladora_Pantorrilla.obj");

    Model RezTorso((char*)"Models/PRezo_Torso.obj");
    Model RezCabeza((char*)"Models/PRezo_Cabeza.obj");
    Model RezBrazo((char*)"Models/PRezo_Brazo.obj");
    Model RezAntebrazo((char*)"Models/PRezo_Antebrazo.obj");
    Model RezMuslo((char*)"Models/PRezo_Muslo.obj");
    Model RezPantorrilla((char*)"Models/PRezo_Pantorrilla.obj");

    Model ArrTorso((char*)"Models/PArrodillado_Torso.obj");
    Model ArrCabeza((char*)"Models/PArrodillado_Cabeza.obj");
    Model ArrBrazo((char*)"Models/PArrodillado_Brazo.obj");
    Model ArrAntebrazo((char*)"Models/PArrodillado_Antebrazo.obj");
    Model ArrMuslo((char*)"Models/PArrodillado_Muslo.obj");
    Model ArrPantorrilla((char*)"Models/PArrodillado_Pantorrilla.obj");

    // Catrina y objetos
    Model CatCuerpo((char*)"Models/Catrina_Cuerpo.obj");
    Model CatCabeza((char*)"Models/Catrina_Cabeza.obj");
    Model CatBrazoDer((char*)"Models/Catrina_BrazoDer.obj");
    Model CatBrazoIzq((char*)"Models/Catrina_BrazoIzq.obj");
    Model FlorOfrenda((char*)"Models/FlorOfrenda.obj");
    Model Cerillo((char*)"Models/Cerillo.obj");

    // Tabla para dibujar los 5 personajes con un for
    // columnas: 0 torso, 1 cabeza, 2 brazo, 3 antebrazo, 4 muslo, 5 pantorrilla
    Model* Personas[5][6] = {
        { &CamTorso, &CamCabeza, &CamBrazo, &CamAntebrazo, &CamMuslo, &CamPantorrilla },
        { &FlTorso,  &FlCabeza,  &FlBrazo,  &FlAntebrazo,  &FlMuslo,  &FlPantorrilla  },
        { &VelTorso, &VelCabeza, &VelBrazo, &VelAntebrazo, &VelMuslo, &VelPantorrilla },
        { &RezTorso, &RezCabeza, &RezBrazo, &RezAntebrazo, &RezMuslo, &RezPantorrilla },
        { &ArrTorso, &ArrCabeza, &ArrBrazo, &ArrAntebrazo, &ArrMuslo, &ArrPantorrilla }
    };
    //=============================================

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

    glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Calcular deltaTime
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        GLfloat t = currentFrame;

        // Eventos y movimiento de camara/teclado
        glfwPollEvents();
        DoMovement();

        // ANIMACION DE PERSONAJES =====================
        float kAnim = 0.0f;

        // ---- 0) CAMINANTE: maquina de estados AVANZAR / GIRAR (como el perrillo)
        if (camCaminando)
        {
            switch (camAnim)
            {
            case 1: // AVANZAR
            {
                glm::vec3 d = rutaCam[camDestino] - posPersona[0];
                float dist = glm::length(d);
                float avance = velCaminar * deltaTime;
                camFase += avance * 8.27f;   // el paso avanza segun la distancia recorrida
                float s = sin(camFase), c = cos(camFase);
                for (int i = 0; i < 16; i++) pose[0][i] = 0.0f;
                pose[0][J_RAIZ] = -0.45f * (1.0f - cos(glm::radians(25.0f * fabs(s))));
                pose[0][J_IZQ_PITCH] = -20.0f * s;
                pose[0][J_DER_PITCH] = 20.0f * s;
                pose[0][J_IZQ_ABD] = 4.0f;   pose[0][J_DER_ABD] = 4.0f;
                pose[0][J_IZQ_CODO] = -15.0f; pose[0][J_DER_CODO] = -15.0f;
                pose[0][J_PIZQ_CAD] = 25.0f * s;
                pose[0][J_PDER_CAD] = -25.0f * s;
                pose[0][J_PIZQ_ROD] = 35.0f * (c < 0.0f ? -c : 0.0f);
                pose[0][J_PDER_ROD] = 35.0f * (c > 0.0f ? c : 0.0f);

                if (dist <= avance)
                {
                    posPersona[0] = rutaCam[camDestino];
                    camDestino = (camDestino + 1) % RUTA_PUNTOS;
                    camTargetYaw = glm::degrees(atan2(rutaCam[camDestino].x - posPersona[0].x,
                        rutaCam[camDestino].z - posPersona[0].z));
                    camAnim = 2;
                }
                else
                    posPersona[0] += (d / dist) * avance;
                break;
            }
            case 2: // GIRAR
            {
                for (int i = 0; i < 16; i++) pose[0][i] -= pose[0][i] * 6.0f * deltaTime;  // vuelve a pose neutra
                float diff = camTargetYaw - yawPersona[0];
                while (diff > 180.0f) diff -= 360.0f;
                while (diff <= -180.0f) diff += 360.0f;
                float giroMax = velGiro * deltaTime;
                if (fabs(diff) <= giroMax)
                {
                    yawPersona[0] = camTargetYaw;
                    camAnim = 1;
                }
                else
                    yawPersona[0] += (diff > 0.0f) ? giroMax : -giroMax;
                break;
            }
            }
        }

        // ---- 1) PONER FLOR EN LA TUMBA: maquina de estados
        switch (florAnim)
        {
        case 1: // AGACHARSE y estirar el brazo
            tFlor += deltaTime;
            kAnim = tFlor / 1.6f; if (kAnim > 1.0f) kAnim = 1.0f; kAnim = kAnim * kAnim * (3.0f - 2.0f * kAnim);
            for (int i = 0; i < 16; i++) pose[1][i] = POSE_NEUTRA[i] + (POSE_PONER_FLOR[i] - POSE_NEUTRA[i]) * kAnim;
            if (tFlor >= 1.6f) { tFlor = 0.0f; florAnim = 2; }
            break;
        case 2: // ESPERAR
            tFlor += deltaTime;
            if (tFlor >= 0.6f) { tFlor = 0.0f; florAnim = 3; }
            break;
        case 3: // SOLTAR LA FLOR
            florEnMano = false;
            florSuelta = true;
            florYaw = yawPersona[1];
            florPos = glm::vec3(manoDer[1] * glm::vec4(0.0f, 0.04f, 0.0f, 1.0f));
            florAnim = 4;
            break;
        case 4: // ESPERAR
            tFlor += deltaTime;
            if (tFlor >= 0.8f) { tFlor = 0.0f; florAnim = 5; }
            break;
        case 5: // LEVANTARSE
            tFlor += deltaTime;
            kAnim = tFlor / 1.5f; if (kAnim > 1.0f) kAnim = 1.0f; kAnim = kAnim * kAnim * (3.0f - 2.0f * kAnim);
            for (int i = 0; i < 16; i++) pose[1][i] = POSE_PONER_FLOR[i] + (POSE_NEUTRA[i] - POSE_PONER_FLOR[i]) * kAnim;
            if (tFlor >= 1.5f) { tFlor = 0.0f; florAnim = 1; florEnMano = true; florSuelta = false; }            break;
        }
        if (florSuelta && florPos.y > SUELO_Y + 0.02f)   // la flor cae al piso
        {
            florPos.y -= 1.2f * deltaTime;
            if (florPos.y < SUELO_Y + 0.02f) florPos.y = SUELO_Y + 0.02f;
        }

        // ---- 2) ENCENDER LA VELADORA: maquina de estados
        switch (veladoraAnim)
        {
        case 1: // AGACHARSE con el brazo estirado
            tVeladora += deltaTime;
            kAnim = tVeladora / 1.4f; if (kAnim > 1.0f) kAnim = 1.0f; kAnim = kAnim * kAnim * (3.0f - 2.0f * kAnim);
            for (int i = 0; i < 16; i++) pose[2][i] = POSE_NEUTRA[i] + (POSE_VELADORA[i] - POSE_NEUTRA[i]) * kAnim;
            if (tVeladora >= 1.4f) { tVeladora = 0.0f; cerilloEnMano = true; veladoraAnim = 2; }
            break;
        case 2: // SACAR EL CERILLO
            tVeladora += deltaTime;
            if (tVeladora >= 0.8f) { tVeladora = 0.0f; veladoraAnim = 3; }
            break;
        case 3: // ENCENDER (la luz sube poco a poco)
            tVeladora += deltaTime;
            intensidadVeladora = tVeladora / 1.5f;
            if (intensidadVeladora > 1.0f) intensidadVeladora = 1.0f;
            if (tVeladora >= 1.8f) { tVeladora = 0.0f; cerilloEnMano = false; veladoraAnim = 4; }
            break;
        case 4: // LEVANTARSE
            tVeladora += deltaTime;
            kAnim = tVeladora / 1.4f; if (kAnim > 1.0f) kAnim = 1.0f; kAnim = kAnim * kAnim * (3.0f - 2.0f * kAnim);
            for (int i = 0; i < 16; i++) pose[2][i] = POSE_VELADORA[i] + (POSE_NEUTRA[i] - POSE_VELADORA[i]) * kAnim;
            if (tVeladora >= 1.4f) { tVeladora = 0.0f; veladoraAnim = 1; intensidadVeladora = 0.0f; }
            break;
        }

        // ---- 3) REZO / PERSIGNARSE: KEYFRAMES (como la Practica 10)
        if (playRezo)
        {
            tRezo += deltaTime;
            kAnim = tRezo / KFRezoDur[rezoIndex + 1]; if (kAnim > 1.0f) kAnim = 1.0f; kAnim = kAnim * kAnim * (3.0f - 2.0f * kAnim);
            for (int i = 0; i < 16; i++)
                pose[3][i] = KFRezo[rezoIndex][i] + (KFRezo[rezoIndex + 1][i] - KFRezo[rezoIndex][i]) * kAnim;
            if (tRezo >= KFRezoDur[rezoIndex + 1])
            {
                tRezo = 0.0f;
                rezoIndex++;
                if (rezoIndex >= 9) rezoIndex = 0;   // regresa al primer frame y se repite
            }
        }

        // ---- 4) ARRODILLARSE: maquina de estados
        switch (arrodAnim)
        {
        case 1: // ARRODILLARSE
            tArrod += deltaTime;
            kAnim = tArrod / 1.8f; if (kAnim > 1.0f) kAnim = 1.0f; kAnim = kAnim * kAnim * (3.0f - 2.0f * kAnim);
            for (int i = 0; i < 16; i++) pose[4][i] = POSE_NEUTRA[i] + (POSE_ARRODILLADO[i] - POSE_NEUTRA[i]) * kAnim;
            if (tArrod >= 1.8f) { tArrod = 0.0f; arrodAnim = 2; }
            break;
        case 2: // REZAR
            tArrod += deltaTime;
            if (tArrod >= 5.0f) { tArrod = 0.0f; arrodAnim = 3; }
            break;
        case 3: // LEVANTARSE
            tArrod += deltaTime;
            kAnim = tArrod / 1.8f; if (kAnim > 1.0f) kAnim = 1.0f; kAnim = kAnim * kAnim * (3.0f - 2.0f * kAnim);
            for (int i = 0; i < 16; i++) pose[4][i] = POSE_ARRODILLADO[i] + (POSE_NEUTRA[i] - POSE_ARRODILLADO[i]) * kAnim;
            if (tArrod >= 1.8f) { tArrod = 0.0f; arrodAnim = 1; }
            break;
        }
        // ===================================================================

        // Limpiar buffers
        glClearColor(0.08f, 0.08f, 0.12f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        lightingShader.Use();

        GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
        glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 16.0f);

        // Por defecto la transparencia esta desactivada (0 = opaco)
        glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);

        // 1. CALCULO DE TRAYECTORIAS (ORBITA SOL/LUNA Y VUELO DE LUCIERNAGA)
        // Orbita del Sol y la Luna
        sunAngle += 0.25f * deltaTime; // Velocidad de rotacion constante con deltaTime
        sunPos.x = cos(sunAngle) * sunOrbitRadius;
        sunPos.y = 2.0f + sin(sunAngle) * sunOrbitRadius;
        sunPos.z = -2.0f;

        moonPos.x = cos(sunAngle + glm::radians(180.0f)) * sunOrbitRadius;
        moonPos.y = 2.0f + sin(sunAngle + glm::radians(180.0f)) * sunOrbitRadius;
        moonPos.z = -2.0f;

        // Trayectoria parametrica de la luciernaga y calculo del angulo de giro
        glm::vec3 posLuc = posLuciernaga + glm::vec3(0.35f * sin(0.6f * t), 0.12f * sin(1.7f * t), 0.35f * cos(0.45f * t));
        float avanceX = 0.35f * 0.6f * cos(0.6f * t);
        float avanceZ = -0.35f * 0.45f * sin(0.45f * t);
        float rumboLuciernaga = atan2(avanceX, avanceZ);

        // Actualizar posicion de cada luz puntual junto a su modelo
        pointLightPositions[0] = posFogata + glm::vec3(0.0f, 0.25f * ESC_FOGATA, 0.0f);
        pointLightPositions[1] = posVela + glm::vec3(0.0f, 0.27f * ESC_VELA, 0.0f);
        pointLightPositions[2] = posLuc;
        pointLightPositions[3] = posFarol + glm::vec3(0.0f, 0.875f * ESC_FAROL, 0.0f);
        pointLightPositions[4] = posVeladora + glm::vec3(0.0f, 0.25f * ESC_VELADORA, 0.0f);

        // 2. CONFIGURACION DE FUENTES DE LUZ
        // Luz del Sol y Luna
        bool sunEnabled = (sunPos.y >= 2.0f);
        bool moonEnabled = !sunEnabled;
        glUniform1i(glGetUniformLocation(lightingShader.Program, "sunEnabled"), sunEnabled ? 1 : 0);
        glUniform1i(glGetUniformLocation(lightingShader.Program, "moonEnabled"), moonEnabled ? 1 : 0);

        glUniform3f(glGetUniformLocation(lightingShader.Program, "sun.position"), sunPos.x, sunPos.y, sunPos.z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "sun.ambient"), 0.15f, 0.15f, 0.15f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "sun.diffuse"), 0.90f, 0.80f, 0.60f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "sun.specular"), 0.50f, 0.50f, 0.50f);

        glUniform3f(glGetUniformLocation(lightingShader.Program, "moon.position"), moonPos.x, moonPos.y, moonPos.z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "moon.ambient"), 0.03f, 0.04f, 0.08f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "moon.diffuse"), 0.10f, 0.13f, 0.28f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "moon.specular"), 0.10f, 0.10f, 0.20f);

        // ---------- DIRECCIONAL: Luz ambiental nocturna general
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.05f, 0.06f, 0.12f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.10f, 0.13f, 0.28f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.10f, 0.10f, 0.20f);

        // ---------- PUNTUAL 1: FOGATA para cantar la cancion de la hoguera
        float parpadeoFogata = 0.85f + 0.10f * sin(t * 11.0f) * sin(t * 5.3f) + 0.05f * sin(t * 27.0f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), 0.15f * parpadeoFogata, 0.07f * parpadeoFogata, 0.015f * parpadeoFogata);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), 1.0f * parpadeoFogata, 0.45f * parpadeoFogata, 0.10f * parpadeoFogata);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 0.6f * parpadeoFogata, 0.3f * parpadeoFogata, 0.1f * parpadeoFogata);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.14f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.07f);

        // ---------- PUNTUAL 2: VELA1
        float parpadeoVela = 0.90f + 0.06f * sin(t * 9.0f) + 0.04f * sin(t * 23.0f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), 0.10f * parpadeoVela, 0.07f * parpadeoVela, 0.03f * parpadeoVela);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), 1.0f * parpadeoVela, 0.72f * parpadeoVela, 0.32f * parpadeoVela);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 0.3f * parpadeoVela, 0.2f * parpadeoVela, 0.1f * parpadeoVela);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.7f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 1.8f);

        // ---------- PUNTUAL 3: MOSKA
        float destelloLuc = 0.5f + 0.5f * sin(t * 3.0f);
        destelloLuc = destelloLuc * destelloLuc;
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].ambient"), 0.05f * destelloLuc, 0.12f * destelloLuc, 0.02f * destelloLuc);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].diffuse"), 0.45f * destelloLuc, 1.0f * destelloLuc, 0.15f * destelloLuc);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].specular"), 0.3f * destelloLuc, 0.6f * destelloLuc, 0.1f * destelloLuc);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].linear"), 1.4f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].quadratic"), 6.0f);

        // ---------- PUNTUAL 4: FAROL
        float titileoFarol = 0.97f + 0.03f * sin(t * 7.0f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].ambient"), 0.08f * titileoFarol, 0.06f * titileoFarol, 0.03f * titileoFarol);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].diffuse"), 1.0f * titileoFarol, 0.78f * titileoFarol, 0.40f * titileoFarol);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].specular"), 0.4f * titileoFarol, 0.3f * titileoFarol, 0.15f * titileoFarol);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].linear"), 0.22f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].quadratic"), 0.20f);

        // ---------- PUNTUAL 5: VELADORA2
        float parpadeoVeladora = intensidadVeladora * (0.88f + 0.08f * sin(t * 8.0f + 1.3f) + 0.04f * sin(t * 21.0f));        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[4].position"), pointLightPositions[4].x, pointLightPositions[4].y, pointLightPositions[4].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[4].ambient"), 0.08f * parpadeoVeladora, 0.03f * parpadeoVeladora, 0.01f * parpadeoVeladora);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[4].diffuse"), 1.0f * parpadeoVeladora, 0.45f * parpadeoVeladora, 0.12f * parpadeoVeladora);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[4].specular"), 0.3f * parpadeoVeladora, 0.15f * parpadeoVeladora, 0.05f * parpadeoVeladora);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[4].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[4].linear"), 0.9f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[4].quadratic"), 2.5f);

        // ---------- SPOTLIGHT -->Linterna de la camara 
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.05f, 0.05f, 0.15f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.2f, 0.2f, 0.6f);
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

        // 3. MODELOS OPACOS (transparency = 0)
        glm::mat4 modelPiso(1.0f);
        modelPiso = glm::translate(modelPiso, glm::vec3(0.0f, -1.2f, -1.0f));
        modelPiso = glm::scale(modelPiso, glm::vec3(5.0f, 0.2f, 5.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelPiso));
        Piso.Draw(lightingShader);

        // Sol (en orbita)
        glm::mat4 modelSol(1.0f);
        modelSol = glm::translate(modelSol, sunPos);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelSol));
        sol.Draw(lightingShader);

        // Luna (en orbita)
        glm::mat4 modelLuna(1.0f);
        modelLuna = glm::translate(modelLuna, moonPos);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelLuna));
        luna.Draw(lightingShader);

        // Flores y Hongo
        glm::mat4 modelFlor(1.0f);
        modelFlor = glm::translate(modelFlor, glm::vec3(-1.5f, -1.0f, 0.98f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelFlor));
        flor.Draw(lightingShader);

        glm::mat4 modelFlor2(1.0f);
        modelFlor2 = glm::translate(modelFlor2, glm::vec3(1.5f, -1.0f, 0.98f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelFlor2));
        flor.Draw(lightingShader);

        glm::mat4 modelHongo(1.0f);
        modelHongo = glm::translate(modelHongo, glm::vec3(0.2f, -0.89f, 1.28f));
        modelHongo = glm::scale(modelHongo, glm::vec3(0.15f, 0.15f, 0.15f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelHongo));
        hongo.Draw(lightingShader);

        // Modelos luminosos
        glm::mat4 modelFogata(1.0f);
        modelFogata = glm::translate(modelFogata, posFogata);
        modelFogata = glm::scale(modelFogata, glm::vec3(ESC_FOGATA));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelFogata));
        fogata.Draw(lightingShader);

        glm::mat4 modelVela(1.0f);
        modelVela = glm::translate(modelVela, posVela);
        modelVela = glm::scale(modelVela, glm::vec3(ESC_VELA));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelVela));
        vela.Draw(lightingShader);

        glm::mat4 modelLuciernaga(1.0f);
        modelLuciernaga = glm::translate(modelLuciernaga, posLuc);
        modelLuciernaga = glm::rotate(modelLuciernaga, rumboLuciernaga, glm::vec3(0.0f, 1.0f, 0.0f));
        modelLuciernaga = glm::scale(modelLuciernaga, glm::vec3(ESC_LUCIERNAGA));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelLuciernaga));
        luciernaga.Draw(lightingShader);

        glm::mat4 modelFarol(1.0f);
        modelFarol = glm::translate(modelFarol, posFarol);
        modelFarol = glm::scale(modelFarol, glm::vec3(ESC_FAROL));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelFarol));
        farol.Draw(lightingShader);

        glm::mat4 modelVeladora(1.0f);
        modelVeladora = glm::translate(modelVeladora, posVeladora);
        modelVeladora = glm::scale(modelVeladora, glm::vec3(ESC_VELADORA));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelVeladora));
        veladora.Draw(lightingShader);

        // Otros modelos para adornar al panteon
        // Iglesia
        glm::mat4 modelIglesia(1);
        modelIglesia = glm::translate(modelIglesia, posIglesia);
        modelIglesia = glm::scale(modelIglesia, glm::vec3(ESC_IGLESIA));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelIglesia));
        iglesia.Draw(lightingShader);

        // Cuervo posado 
        glm::mat4 modelCuervo(1);
        modelCuervo = glm::translate(modelCuervo, posCuervo);
        modelCuervo = glm::rotate(modelCuervo, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        modelCuervo = glm::scale(modelCuervo, glm::vec3(ESC_CUERVO));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelCuervo));
        cuervo.Draw(lightingShader);

        // Macetas 
        glm::mat4 modelMaceta1(1);
        modelMaceta1 = glm::translate(modelMaceta1, posMaceta1);
        modelMaceta1 = glm::scale(modelMaceta1, glm::vec3(ESC_MACETA));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMaceta1));
        maceta.Draw(lightingShader);

        glm::mat4 modelMaceta2(1);
        modelMaceta2 = glm::translate(modelMaceta2, posMaceta2);
        modelMaceta2 = glm::rotate(modelMaceta2, glm::radians(70.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        modelMaceta2 = glm::scale(modelMaceta2, glm::vec3(ESC_MACETA));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMaceta2));
        maceta.Draw(lightingShader);

        glm::mat4 modelMaceta3(1);
        modelMaceta3 = glm::translate(modelMaceta3, posMaceta3);
        modelMaceta3 = glm::rotate(modelMaceta3, glm::radians(200.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        modelMaceta3 = glm::scale(modelMaceta3, glm::vec3(ESC_MACETA));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMaceta3));
        maceta.Draw(lightingShader);

        // Flores sin maceta
        glm::mat4 modelMacizo1(1);
        modelMacizo1 = glm::translate(modelMacizo1, posMacizo1);
        modelMacizo1 = glm::scale(modelMacizo1, glm::vec3(ESC_FLOR));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMacizo1));
        macizo.Draw(lightingShader);

        glm::mat4 modelMacizo2(1);
        modelMacizo2 = glm::translate(modelMacizo2, posMacizo2);
        modelMacizo2 = glm::rotate(modelMacizo2, glm::radians(120.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        modelMacizo2 = glm::scale(modelMacizo2, glm::vec3(ESC_FLOR));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMacizo2));
        macizo.Draw(lightingShader);

        float giro = 0.5f * t;
        float aleteo = 35.0f * sin(t * 6.0f);
        glm::mat4 modelCuervoV(1);
        modelCuervoV = glm::translate(modelCuervoV, glm::vec3(3.0f * sin(giro), 3.2f + 0.2f * sin(t * 2.0f), -2.0f + 3.0f * cos(giro)));
        modelCuervoV = glm::rotate(modelCuervoV, giro + glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        modelCuervoV = glm::scale(modelCuervoV, glm::vec3(ESC_CUERVO));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelCuervoV));
        cuervoCuerpo.Draw(lightingShader);

        glm::mat4 modelAlaD = modelCuervoV;
        modelAlaD = glm::translate(modelAlaD, glm::vec3(0.05f, 0.03f, 0.02f));
        modelAlaD = glm::rotate(modelAlaD, glm::radians(aleteo), glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelAlaD));
        cuervoAlaDer.Draw(lightingShader);

        glm::mat4 modelAlaI = modelCuervoV;
        modelAlaI = glm::translate(modelAlaI, glm::vec3(-0.05f, 0.03f, 0.02f));
        modelAlaI = glm::rotate(modelAlaI, glm::radians(-aleteo), glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelAlaI));
        cuervoAlaIzq.Draw(lightingShader);
        //----------------------
        
        // Lapidas: 
        glm::mat4 modelTumba(1);
        modelTumba = glm::scale(modelTumba, glm::vec3(0.5f, 0.5f, 0.5f));
        modelTumba = glm::translate(modelTumba, glm::vec3(-5.5f, -2.2f, -1.0f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelTumba));
        glBindVertexArray(VAO);
        tumba.Draw(lightingShader);

        glm::mat4 modelTumba2(1);
        modelTumba2 = glm::scale(modelTumba2, glm::vec3(0.5f,0.5f, 0.5f));
        modelTumba2 = glm::translate(modelTumba2, glm::vec3(3.0f, -1.9f, -1.0f));
        modelTumba2 = glm::rotate(modelTumba2,glm::radians(180.0f),glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelTumba2));
        glBindVertexArray(VAO);
        tumba2.Draw(lightingShader);

        glm::mat4 modelTumba3(1);
        modelTumba3 = glm::scale(modelTumba3, glm::vec3(0.5f, 0.5f, 0.5f));
        modelTumba3 = glm::translate(modelTumba3, glm::vec3(0.0f, -1.7f, -1.0f));
        modelTumba3 = glm::rotate(modelTumba3, glm::radians(180.0f),glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelTumba3));
        glBindVertexArray(VAO);
        tumba3.Draw(lightingShader);
        //--------------------

        // ---------- PERSONAJES ANIMADOS (se dibujan con transparency = 0) ----------
        for (int p = 0; p < 5; p++)
        {
            glm::mat4 base(1.0f);
            base = glm::translate(base, glm::vec3(posPersona[p].x, SUELO_Y, posPersona[p].z));
            base = glm::rotate(base, glm::radians(yawPersona[p]), glm::vec3(0.0f, 1.0f, 0.0f));
            base = glm::scale(base, glm::vec3(ESC_PERSONA));
            glm::mat4 raiz = glm::translate(base, glm::vec3(0.0f, pose[p][J_RAIZ], 0.0f));

            // Piernas (cuelgan de la cadera)
            for (int l = 0; l < 2; l++)
            {
                float lado = (l == 0) ? 1.0f : -1.0f;     // +1 izquierda, -1 derecha
                glm::mat4 m = glm::translate(raiz, glm::vec3(lado * 0.06f, 0.45f, 0.0f));
                m = glm::rotate(m, glm::radians(pose[p][J_PIZQ_CAD + 2 * l]), glm::vec3(1.0f, 0.0f, 0.0f));
                glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(m));
                Personas[p][4]->Draw(lightingShader);                       // muslo
                m = glm::translate(m, glm::vec3(0.0f, -0.23f, 0.0f));
                m = glm::rotate(m, glm::radians(pose[p][J_PIZQ_ROD + 2 * l]), glm::vec3(1.0f, 0.0f, 0.0f));
                glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(m));
                Personas[p][5]->Draw(lightingShader);                       // pantorrilla
            }

            // Torso (pivote en la cadera)
            glm::mat4 tor = glm::translate(raiz, glm::vec3(0.0f, 0.45f, 0.0f));
            tor = glm::rotate(tor, glm::radians(pose[p][J_TORSO]), glm::vec3(1.0f, 0.0f, 0.0f));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tor));
            Personas[p][0]->Draw(lightingShader);

            // Cabeza (pivote en el cuello)
            glm::mat4 cab = glm::translate(tor, glm::vec3(0.0f, 0.31f, 0.0f));
            cab = glm::rotate(cab, glm::radians(pose[p][J_CAB_Y]), glm::vec3(0.0f, 1.0f, 0.0f));
            cab = glm::rotate(cab, glm::radians(pose[p][J_CAB_X]), glm::vec3(1.0f, 0.0f, 0.0f));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(cab));
            Personas[p][1]->Draw(lightingShader);

            // Brazos (cuelgan de los hombros)
            for (int a = 0; a < 2; a++)
            {
                float lado = (a == 0) ? 1.0f : -1.0f;
                int j = 4 + 4 * a;                                  // 4 = brazo izq, 8 = brazo der
                glm::mat4 m = glm::translate(tor, glm::vec3(lado * 0.15f, 0.27f, 0.0f));
                m = glm::rotate(m, glm::radians(lado * pose[p][j + 2]), glm::vec3(0.0f, 1.0f, 0.0f));
                m = glm::rotate(m, glm::radians(lado * pose[p][j + 1]), glm::vec3(0.0f, 0.0f, 1.0f));
                m = glm::rotate(m, glm::radians(pose[p][j]), glm::vec3(1.0f, 0.0f, 0.0f));
                glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(m));
                Personas[p][2]->Draw(lightingShader);               // brazo
                m = glm::translate(m, glm::vec3(0.0f, -0.15f, 0.0f));
                m = glm::rotate(m, glm::radians(pose[p][j + 3]), glm::vec3(1.0f, 0.0f, 0.0f));
                glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(m));
                Personas[p][3]->Draw(lightingShader);               // antebrazo
                if (a == 1) manoDer[p] = glm::translate(m, glm::vec3(0.0f, -0.15f, 0.0f));   // punta de la mano derecha
            }
        }

        // Flor: en la mano derecha del personaje 1, o ya en el piso
        if (florEnMano || florSuelta)
        {
            glm::mat4 mFlor(1.0f);
            if (florEnMano)
            {
                mFlor = glm::translate(manoDer[1], glm::vec3(0.0f, 0.04f, 0.0f));
                mFlor = glm::rotate(mFlor, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            }
            else
            {
                mFlor = glm::translate(mFlor, florPos);
                mFlor = glm::rotate(mFlor, glm::radians(florYaw), glm::vec3(0.0f, 1.0f, 0.0f));
                mFlor = glm::rotate(mFlor, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                mFlor = glm::scale(mFlor, glm::vec3(ESC_PERSONA));
            }
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mFlor));
            FlorOfrenda.Draw(lightingShader);
        }

        // Cerillo en la mano derecha del personaje 2
        if (cerilloEnMano)
        {
            glm::mat4 mCer = glm::translate(manoDer[2], glm::vec3(0.0f, 0.03f, 0.0f));
            mCer = glm::rotate(mCer, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mCer));
            Cerillo.Draw(lightingShader);
        }

        // Catrina (animacion procedural con sin(t))
        glm::mat4 catBase(1.0f);
        catBase = glm::translate(catBase, posCatrina);
        catBase = glm::rotate(catBase, glm::radians(yawCatrina), glm::vec3(0.0f, 1.0f, 0.0f));
        catBase = glm::scale(catBase, glm::vec3(ESC_CATRINA));
        catBase = glm::rotate(catBase, glm::radians(4.0f * sin(t * 1.3f)), glm::vec3(0.0f, 0.0f, 1.0f));   // balanceo
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(catBase));
        CatCuerpo.Draw(lightingShader);

        glm::mat4 catCab = glm::translate(catBase, glm::vec3(0.0f, 0.82f, 0.0f));
        catCab = glm::rotate(catCab, glm::radians(18.0f * sin(t * 0.7f)), glm::vec3(0.0f, 1.0f, 0.0f));
        catCab = glm::rotate(catCab, glm::radians(6.0f * sin(t * 1.3f + 0.8f)), glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(catCab));
        CatCabeza.Draw(lightingShader);

        glm::mat4 catBD = glm::translate(catBase, glm::vec3(-0.12f, 0.78f, 0.0f));       // brazo que saluda
        catBD = glm::rotate(catBD, glm::radians(-(115.0f + 14.0f * sin(t * 5.0f))), glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(catBD));
        CatBrazoDer.Draw(lightingShader);

        glm::mat4 catBI = glm::translate(catBase, glm::vec3(0.12f, 0.78f, 0.0f));        // brazo que cuelga
        catBI = glm::rotate(catBI, glm::radians(14.0f + 4.0f * sin(t * 1.3f)), glm::vec3(0.0f, 0.0f, 1.0f));
        catBI = glm::rotate(catBI, glm::radians(6.0f * sin(t * 0.9f)), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(catBI));
        CatBrazoIzq.Draw(lightingShader);
        //==========================






        // 5. DIBUJO DE MODELOS CON TRANSPARENCIA-->Siempre al final del ciclo
        //Tumba Transparente (con transparency = 1)
        glm::mat4 modelT(1.0f);
        modelT = glm::translate(modelT, glm::vec3(-1.5f, -1.3f, 0.0f));
        modelT = glm::rotate(modelT, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        modelT = glm::scale(modelT, glm::vec3(0.6f, 0.6f, 0.6f));
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelT));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 1); // 1 = Activa transparencia
        TumbaTransparente.Draw(lightingShader);
        glDisable(GL_BLEND);
        //Importante: regresamos transparency a 0 para no afectar el siguiente frame
        glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
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

    if (action == GLFW_PRESS)
    {
        if (key == GLFW_KEY_1) camCaminando = !camCaminando;
        if (key == GLFW_KEY_2 && florAnim == 0) { florAnim = 1; tFlor = 0.0f; florEnMano = true; florSuelta = false; }
        if (key == GLFW_KEY_3 && veladoraAnim == 0) { veladoraAnim = 1; tVeladora = 0.0f; intensidadVeladora = 0.0f; cerilloEnMano = false; }
        if (key == GLFW_KEY_4 && !playRezo) { playRezo = true; rezoIndex = 0; tRezo = 0.0f; }
        if (key == GLFW_KEY_5 && arrodAnim == 0) { arrodAnim = 1; tArrod = 0.0f; }
    }
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
    if (firstMouse)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;

    lastX = xPos;
    lastY = yPos;

    camera.ProcessMouseMovement(xOffset, yOffset);
}
