from pathlib import Path
import re

root = Path(__file__).parent
path = root / 'ConfigInicial/Iluminacion.cpp'
s = path.read_text(encoding='utf-8-sig')
s = s.replace('#include <string>', '#include <string>\n#include <algorithm>\n#include <vector>')
s = s.replace('Camera camera(glm::vec3(0.0f, 0.0f, 6.0f));', 'Camera camera(glm::vec3(0.0f, 1.7f, 19.0f), glm::vec3(0,1,0), -90.0f, -3.0f);')
start = s.index('// TRAYECTORIA DE ORBITA:')
end = s.index('// Posiciones de las 5 luces puntuales:')
s = s[:start] + '''// ETAPAS 5-6: emisores y trayectorias adaptados a las seis zonas.
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
const float ESC_LUCIERNAGA = 3.0f;
const float ESC_FAROL = 1.8f;
const float ESC_VELADORA = 1.6f;
const float ESC_CUERVO = 1.4f;

''' + s[end:]
s = s.replace('int main()\n{', (root / 'helpers-escena.txt').read_text() + '''int main(int argc, char** argv)
{
    const bool validate = argc == 3 && std::string(argv[1]) == "--validar-escena";
    const std::string captureDirectory = validate ? argv[2] : "";
    camera.SetWalkingMode(EYE_HEIGHT, 3.5f);
''')
s = s.replace('    glfwInit();', '''    if (!glfwInit())
    {
        std::cerr << "ERROR: no se pudo iniciar GLFW." << std::endl;
        return EXIT_FAILURE;
    }
    if (validate) glfwWindowHint(GLFW_VISIBLE, GL_FALSE);''')
s = s.replace('"Proyecto CG - Equipo 12"', '"Panteon de Mixquic v1.0 - Equipo 12"')
s = s.replace('    glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);', '''    glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
    glfwSwapInterval(validate ? 0 : 1);
    if (!validate) glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);''')
s = s.replace('    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);', '''    // GLEW puede dejar GL_INVALID_ENUM al consultar extensiones en un perfil core.
    while (glGetError() != GL_NO_ERROR) {}
    std::cout << "OpenGL: " << glGetString(GL_VERSION) << " / " << glGetString(GL_RENDERER) << std::endl;
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);''')
s = s.replace('    // CARGA DE MODELOS', '''    for (GLuint program : {shader.Program, lampShader.Program, lightingShader.Program})
    {
        GLint linked = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linked);
        if (!linked) { glfwTerminate(); return EXIT_FAILURE; }
    }

    // CARGA DE MODELOS''')
s = s.replace('    Model macizo((char*)"Models/cempasuchil_macizo.obj");', '    Model macizo((char*)"Models/cempasuchil_macizo.obj");\n    Model cempasuchil("Models/cempasuchil.obj");')
anchor = '    // Configuracion de VAO y VBO'
start = s.index(anchor)
s = s[:start] + '''    // La validacion impide aceptar un prototipo con recursos faltantes.
    for (Model* model : {&Piso,&sol,&luna,&flor,&tumba,&tumba2,&tumba3,&iglesia,&cuervo,&maceta,
        &macizo,&cempasuchil,&cuervoCuerpo,&cuervoAlaDer,&cuervoAlaIzq,&fogata,&vela,&luciernaga,&farol,&veladora})
        if (!model->IsLoaded()) { glfwTerminate(); return EXIT_FAILURE; }

''' + (root / 'construir-distribucion.txt').read_text() + s[start:]
s = s.replace('glm::perspective(camera.GetZoom(),', 'glm::perspective(glm::radians(camera.GetZoom()),')
s = s.replace('0.1f, 100.0f);', '0.1f, 120.0f);')
s = s.replace('    // Game loop', '''    struct Viewpoint { const char* name; glm::vec3 eye, target; float time; };
    const Viewpoint viewpoints[] = {
        {"01-entrada", {0,1.7f,19}, {0,3,-8}, 0},
        {"02-atrio", {0,1.7f,11}, {0,3,-6}, 0},
        {"03-tumbas-izquierda", {-6.2f,1.7f,6}, {-10.7f,1,2}, 0},
        {"04-tumbas-derecha", {6.2f,1.7f,6}, {10.7f,1,2}, 0},
        {"05-paso-lateral", {-6.2f,1.7f,-7}, {-6.2f,1.7f,-16}, 0},
        {"06-alumbrada", {0,1.7f,-15.1f}, {0,1.2f,-18.5f}, 0},
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
        const int forwardKeys[] = {GLFW_KEY_W, GLFW_KEY_UP};
        for (int key : forwardKeys) { keys[key]=true; DoMovement(); keys[key]=false; }
        const int backwardKeys[] = {GLFW_KEY_S, GLFW_KEY_DOWN};
        for (int key : backwardKeys) { keys[key]=true; DoMovement(); keys[key]=false; }
        const int leftKeys[] = {GLFW_KEY_A, GLFW_KEY_LEFT};
        for (int key : leftKeys) { keys[key]=true; DoMovement(); keys[key]=false; }
        const int rightKeys[] = {GLFW_KEY_D, GLFW_KEY_RIGHT};
        for (int key : rightKeys) { keys[key]=true; DoMovement(); keys[key]=false; }
        if (glm::length(camera.GetPosition()-glm::vec3(0,EYE_HEIGHT,19)) > 0.001f)
        { std::cerr << "ERROR: controles de recorrido." << std::endl; return EXIT_FAILURE; }
        // Verificar que el callback del mouse cambia la direccion de la vista.
        const glm::vec3 previousFront = camera.GetFront();
        firstMouse=true; MouseCallback(window,100,100); MouseCallback(window,160,100);
        if (glm::length(camera.GetFront()-previousFront) < 0.01f)
        { std::cerr << "ERROR: control de mouse." << std::endl; return EXIT_FAILURE; }
        std::cout << "VALIDACION: WASD, flechas y mouse; altura peatonal constante." << std::endl;
    }
    const double animationStart = glfwGetTime();
    lastFrame = 0.0f;

    // Game loop''')
start = s.index('        GLfloat currentFrame = glfwGetTime();')
end = s.index('        // Limpiar buffers', start)
s = s[:start] + '''        GLfloat currentFrame = static_cast<GLfloat>(glfwGetTime() - animationStart);
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

''' + s[end:]
s = s.replace('glClearColor(0.08f, 0.08f, 0.12f, 1.0f);', 'glClearColor(0.018f, 0.023f, 0.042f, 1.0f);')
s = s.replace('        lightingShader.Use();', '''        lightingShader.Use();
        glUniform3f(glGetUniformLocation(lightingShader.Program, "objectGlow"), 0,0,0);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "emissionPulse"), 0.94f + 0.06f*sin(t*8.0f));''')
start = s.index('        sunAngle +=')
end = s.index('        // Trayectoria parametrica', start)
s = s[:start] + '''        sunAngle = glm::radians(225.0f) + 0.08f * t;
        sunPos.x = cos(sunAngle) * sunOrbitRadius;
        sunPos.y = 18.0f + sin(sunAngle) * sunOrbitRadius;
        sunPos.z = -22.0f;
        moonPos.x = cos(sunAngle + glm::radians(180.0f)) * sunOrbitRadius;
        moonPos.y = 18.0f + sin(sunAngle + glm::radians(180.0f)) * sunOrbitRadius;
        moonPos.z = -22.0f;

''' + s[end:]
s = s.replace('0.35f * sin(0.6f * t), 0.12f * sin(1.7f * t), 0.35f * cos(0.45f * t)', '0.7f * sin(0.6f * t), 0.18f * sin(1.7f * t), 0.7f * cos(0.45f * t)')
s = s.replace('0.35f * 0.6f', '0.7f * 0.6f').replace('-0.35f * 0.45f', '-0.7f * 0.45f')
s = s.replace('bool sunEnabled = (sunPos.y >= 2.0f);', 'bool sunEnabled = !ESCENA_NOCTURNA && sin(sunAngle) >= 0.0f;')
s = s.replace('bool moonEnabled = !sunEnabled;', 'bool moonEnabled = ESCENA_NOCTURNA || !sunEnabled;')
# Uniforms existentes: se conservan las cinco luces, direccional, Sol/Luna y linterna.
uniforms = {
    'dirLight.ambient': '0.13f, 0.14f, 0.18f',
    'dirLight.diffuse': '0.13f, 0.15f, 0.22f',
    'dirLight.specular': '0.08f, 0.09f, 0.13f',
    'moon.ambient': '0.025f, 0.03f, 0.05f',
    'moon.diffuse': '0.10f, 0.12f, 0.18f',
    'spotLight.ambient': '0.025f, 0.022f, 0.018f',
    'spotLight.diffuse': '0.85f, 0.75f, 0.55f',
}
for name, value in uniforms.items():
    pattern = r'(glUniform3f\(glGetUniformLocation\(lightingShader.Program, "' + re.escape(name) + r'"\), )[^;]+;'
    s, count = re.subn(pattern, lambda m: m[1] + value + ');', s)
    assert count == 1, name
for i, linear, quadratic in [(0,'0.07f','0.017f'),(1,'0.07f','0.017f'),(2,'0.35f','0.44f'),(3,'0.07f','0.017f'),(4,'0.045f','0.0075f')]:
    for name, value in [('linear',linear),('quadratic',quadratic)]:
        pattern = r'(glUniform1f\(glGetUniformLocation\(lightingShader.Program, "pointLights\[' + str(i) + r'\]\.' + name + r'"\), )[^;]+;'
        s, count = re.subn(pattern, lambda m: m[1] + value + ');', s)
        assert count == 1
s = s.replace('1.0f * parpadeoFogata, 0.45f * parpadeoFogata, 0.10f * parpadeoFogata', '2.4f * parpadeoFogata, 1.15f * parpadeoFogata, 0.30f * parpadeoFogata')
s = s.replace('1.0f * parpadeoVela, 0.72f * parpadeoVela, 0.32f * parpadeoVela', '2.8f * parpadeoVela, 1.7f * parpadeoVela, 0.7f * parpadeoVela')
s = s.replace('1.0f * titileoFarol, 0.78f * titileoFarol, 0.40f * titileoFarol', '2.0f * titileoFarol, 1.45f * titileoFarol, 0.65f * titileoFarol')
s = s.replace('1.0f * parpadeoVeladora, 0.45f * parpadeoVeladora, 0.12f * parpadeoVeladora', '3.5f * parpadeoVeladora, 2.0f * parpadeoVeladora, 0.55f * parpadeoVeladora')
start = s.index('        // 3. MODELOS OPACOS')
end = s.index('        // 5. DIBUJO DE MODELOS CON TRANSPARENCIA', start)
s = s[:start] + (root / 'dibujar-distribucion.txt').read_text() + s[end:]
s = s.replace('        glfwSwapBuffers(window);', '''        if (validate)
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
        glfwSwapBuffers(window);''')
s = s.replace('    glDeleteVertexArrays(1, &VAO);', '    glDeleteTextures(1, &concreteTexture);\n    glDeleteVertexArrays(1, &VAO);')
s = s.replace('    return 0;\n}', '    return resultCode;\n}')
s = s.replace('GLfloat xOffset = xPos - lastX;', 'GLfloat xOffset = static_cast<GLfloat>(xPos) - lastX;')
s = s.replace('GLfloat yOffset = lastY - yPos;', 'GLfloat yOffset = lastY - static_cast<GLfloat>(yPos);')
s = s.replace('lastX = xPos;', 'lastX = static_cast<GLfloat>(xPos);').replace('lastY = yPos;', 'lastY = static_cast<GLfloat>(yPos);')
path.write_text(s, encoding='utf-8')
