# Panteón de Mixquic — prototipo espacial v1.0

Implementado sobre la base existente de `ConfigInicial/Iluminacion.cpp`, con C++, OpenGL 3.3, GLFW, GLEW, GLM, Assimp y SOIL2 ya incluidos. Fecha: 19 de octubre de 2026.

## Cambios realizados

- Terreno de 34 × 42 unidades a Y = 0, utilizando la geometría de `piso.obj` y la textura existente `images/photoreal_concrete_01-512x512_0.png`. Se sustituye el pasto solo al dibujar: los OBJ, MTL y archivos de imagen se conservan.
- Acceso indicado mediante dos pequeños marcadores de piedra y faroles. Atrio despejado y camino central reconocible, con juntas y dos recorridos laterales hasta la parte posterior del templo.
- Iglesia centrada según sus límites reales, apoyada sobre el suelo y con fachada hacia +Z. Se utiliza `iglesia.obj` y sus materiales originales. `iglesia_pintada.obj` sigue disponible, sin superponer dos iglesias.
- Nueve tumbas: cuatro a cada lado y una destacada en La Alumbrada. Se cargan una vez los tres modelos de tumba y se reutilizan sus instancias.
- 141 instancias decorativas estáticas, además de los emisores y el cuervo posado. La ofrenda principal reúne 36 velas/veladoras decorativas, una veladora emisora, macetas y flores. Cada sepultura lateral tiene una composición más pequeña.
- Se mantienen exactamente cinco luces puntuales, la direccional, el spotlight y el sistema Sol/Luna. Se conservan el parpadeo y el destello de la luciérnaga. Los materiales con Kd > 1, ya identificados como luminosos en los MTL, se presentan con emisión; eso no agrega luces puntuales.
- Se conservan el cuervo en vuelo, sus dos alas, el cuervo posado y la luciérnaga. Las trayectorias se adaptan al terreno ampliado. La órbita se eleva para que Sol y Luna no atraviesen el terreno. `ESCENA_NOCTURNA` mantiene oculto el modelo del Sol y su iluminación, mientras su órbita continúa calculándose.
- Cámara inicial en (0, 1.7, 19), mirando hacia el templo; desplazamiento peatonal a 3.5 unidades/s, con altura constante aunque se mire arriba o abajo. La perspectiva convierte correctamente los grados del zoom a radianes.
- Las referencias de carga y dibujo a `TumbaTransparente.obj` y `Blue+Mushroom.obj` continúan comentadas, con TODO.

No se agregaron modelos, texturas de escena, bibliotecas ni dependencias. Se conservaron los archivos de solución/proyecto, las configuraciones Debug/Release x86, las bibliotecas y la configuración de Git. No se realizaron commits, push ni merges.

## Distribución y recorrido

X representa izquierda/derecha, Y altura y Z profundidad. El frente es +Z; el fondo es −Z.

| Zona | Posición o límites aproximados | Función |
|---|---|---|
| 1. Acceso | X = 0, Z = +17.5; cámara a Z = +19 | Inicio entre dos marcadores y faroles |
| 2. Atrio | X entre −6 y +6; Z entre +9.5 y +15.5 | Bienvenida y conexión con el eje central |
| 3. Templo | X entre −4.48 y +4.48; Z entre −13.715 y −3.285 | Fachada hacia el acceso, altura 8.5225 |
| 4. Camino | Eje X entre −2 y +2; llega al frente del templo | Recorrido central, sin atravesar el edificio |
| 4. Pasos laterales | X = ±6.2, ancho 2.2; enlace posterior en Z = −15.3 | Llegada a La Alumbrada por ambos lados |
| 5. Tumbas | X = ±10.7; Z = +8, +2, −4 y −10 | Cuatro por lateral, con ofrendas pequeñas |
| 6. La Alumbrada | Plataforma centrada en Z = −18.45; tumba en Z = −18.9 | Ofrenda principal detrás del templo |

Desde la entrada se avanza por el atrio hasta la fachada, se toma cualquiera de los pasos laterales y se llega al camino posterior. Allí se accede a La Alumbrada. Hay conexiones cortas hacia los espacios de las tumbas. El recorrido se puede completar regresando por el otro lateral.

Las superficies se separan en altura: piso a Y = 0, caminos a Y = 0.04, juntas a Y = 0.046, plataformas de tumbas a Y = 0.07 y ofrenda principal a Y = 0.1. Cada instancia usa los límites del OBJ para apoyar su base y corregir su origen.

## Archivos modificados o agregados

| Archivo | Cambio |
|---|---|
| `ConfigInicial/Iluminacion.cpp` | Distribución por zonas, instancias reutilizadas, geometría simple, luces, trayectorias, cámara inicial y modo de validación |
| `ConfigInicial/Model.h` | Consulta de límites reales, carga comprobable, parámetro de textura opcional y comprobación correcta de flags de Assimp |
| `ConfigInicial/Mesh.h` | Textura opcional para el piso, emisión de materiales existentes y uso seguro del mapa especular |
| `ConfigInicial/Camera.h` | Modo peatonal opcional; los demás ejercicios conservan por defecto su cámara libre |
| `ConfigInicial/Shader/lighting.frag` | Repetición de concreto, emisión de materiales, mapa especular opcional y tratamiento de color |
| `MIXQUIC_V1.md` | Este documento de distribución, uso, pruebas y pendientes |

`Shader.h`, `Shader/lighting.vs`, los demás shaders, los OBJ/MTL y los archivos de Visual Studio no requieren cambios.

## Ejecutar en Visual Studio

1. Abrir `ConfigInicial.sln` desde la carpeta `ProyectoFinal_CG`.
2. Seleccionar **Debug | x86**. En las propiedades del proyecto, la plataforma se llama **Win32**.
3. Si Visual Studio ya estaba abierto, aceptar la recarga de los archivos modificados.
4. Compilar con **Ctrl + Mayús + B** y ejecutar con **F5**.
5. Usar **WASD** o **flechas** para caminar, **mouse** para mirar y **Esc** para salir. El cursor queda capturado mientras se ejecuta el recorrido.

Se conservan los controles anteriores de la fogata: T/G en X, Y/H en Y y U/J en Z. Al moverla también se mueve su luz. Esos controles de edición permiten sacarla de su posición prevista; el recorrido inicial está verificado con la distribución de fábrica.

El directorio de trabajo debe ser `ConfigInicial`, como ya está configurado en el proyecto. Allí están `Models`, `Shader` e `images`. El ejecutable se genera en `bin/Win32/Debug/` y las DLL se copian con el proceso de compilación existente.

## Validación reproducible

El ejecutable incluye un modo opcional que genera 13 capturas BMP de vistas y fases de animación, comprueba la distribución y termina con un código de resultado:

```powershell
# Ejecutar desde la carpeta ConfigInicial. Crear primero la carpeta de salida.
New-Item -ItemType Directory -Path ..\capturas -Force
& ..\bin\Win32\Debug\ConfigInicial.exe --validar-escena ..\capturas
```

La sesión normal con F5 no utiliza ese modo. Las vistas elevadas de comprobación no alteran la altura ni los controles de la cámara peatonal.

### Pruebas realizadas

- Base anterior: compilación Debug x86 y ejecución durante 15 segundos, sin errores de recursos ni shaders.
- Prototipo: compilación Debug x86 mediante MSBuild con el proyecto y toolset existentes. Sin errores ni advertencias en la compilación final.
- Ejecución real de OpenGL 3.3 en Intel UHD Graphics y generación de las 13 capturas. Shaders enlazados correctamente, modelos cargados y textura de concreto disponible.
- Comprobación de nueve tumbas, apoyos y límites del terreno. Ninguna tumba invade el templo, otra tumba ni el camino central.
- Recorrido central y ambos pasos laterales comprobados con un margen peatonal de 0.35 unidades; las decoraciones tampoco invaden ese recorrido ni las tumbas.
- Cada tecla WASD y cada flecha se prueba por medio del callback de teclado y la función de movimiento: desplazamiento esperado de 3.5 unidades en un segundo. La cámara mantiene Y = 1.7 incluso mirando hacia arriba. Se comprueba además el cambio de dirección producido por el callback del mouse.
- Cuervo, ambas alas, luciérnaga y órbitas: 401 muestras de sus matrices reales en un intervalo de 200 segundos, sin cruces con el suelo, el templo ni las tumbas. Es un muestreo, no una demostración continua de colisiones.
- Revisión visual de capturas desde la entrada, atrio, tumbas de ambos lados, paso lateral y La Alumbrada. Se comparan además distintos instantes del cuervo, la Luna y la luciérnaga.
- Sin errores de OpenGL en las vistas de validación y sin mensajes de recursos, texturas o shaders faltantes.

La compilación y el arranque se verifican con MSBuild y el ejecutable del mismo proyecto. No se afirma una prueba manual dentro de la interfaz de Visual Studio ni una sesión de navegación manual prolongada. La configuración de lanzamiento F5 se conserva; Release no forma parte de las pruebas de esta entrega.

## Problemas encontrados y soluciones

| Problema | Solución |
|---|---|
| Origen asimétrico de la iglesia y escalas distintas entre OBJ | Límites reales calculados al cargar; transformación de apoyo y centrado antes de escala/rotación |
| Suelo original con `grass.jpg` | Sustitución de textura solo durante el dibujo del piso, reutilizando el concreto existente |
| Tumbas y objetos concentrados alrededor del origen | Instancias agrupadas por zonas, plataformas separadas y comprobación de espacios libres |
| Uso de grados directamente en la perspectiva | Conversión con `glm::radians`, sin cambiar GLM ni el resto de dependencias |
| Cámara que subía al caminar mirando hacia arriba | Proyección del avance al plano XZ en modo peatonal opcional |
| Velas decorativas poco visibles sin añadir luces | Emisión para los materiales luminosos ya descritos en los MTL y parpadeo compartido |
| Aspecto demasiado diurno en las primeras capturas | Menor luz direccional/lunar, luces cálidas localizadas y Sol oculto en la presentación nocturna |
| Órbitas y vuelo situados en la distribución antigua | Órbitas elevadas detrás del templo, vuelo del cuervo sobre el atrio y luciérnaga junto al lateral derecho |
| Modelos todavía ausentes | Se conservan comentados, sin archivos sustitutos ni descargas |

## Preparación y pendientes para v1.1

Las estructuras `Placement` y `Surface`, las funciones de apoyo y los arreglos de posiciones permiten añadir recursos sin duplicar grandes bloques de transformaciones. Los modelos se cargan una vez y sus transformaciones se preparan antes del ciclo de dibujo; las matrices de las animaciones se actualizan con el tiempo.

Se dejan TODO para acceso arquitectónico, bardas perimetrales, árboles/vegetación, personajes, ofrendas adicionales, sahumerios/humo, objetos interactivos y audio ambiental. Esos elementos no se implementan en v1.0.

También quedan pendientes recuperar `TumbaTransparente.obj` y `Blue+Mushroom.obj`, añadir colisiones si se requieren, evaluar rendimiento en otras GPU y realizar la revisión manual de la versión con el equipo. El usuario puede atravesar objetos si se aparta del recorrido: no se agregó un sistema de colisiones. Esta versión tampoco agrega sombras dinámicas ni bloom.

La DLL de Assimp sigue siendo la incluida en la base y depende del runtime de depuración de Visual C++; no se cambió por otra distribución.
