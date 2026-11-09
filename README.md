# ProyectoFinal_CG

Proyecto de Computacion Grafica con OpenGL, GLEW, GLFW, GLM, Assimp y SOIL2.

## Abrir y ejecutar

1. Abrir `ConfigInicial.sln` en Visual Studio con Desarrollo para el escritorio con C++, MSVC v143 y Windows SDK 10 instalados.
2. Seleccionar `Debug | x86` (o `Release | x86`). En las propiedades del proyecto, x86 aparece como `Win32`.
3. Compilar con Ctrl+Mayus+B y ejecutar con F5.

La solucion utiliza x86 porque los binarios incluidos de GLFW, Assimp y GLEW son de 32 bits. Para migrar a x64 hay que sustituir todas esas dependencias por versiones x64 compatibles; cambiar solo el selector no es suficiente.

Los directorios de encabezados y bibliotecas son relativos al proyecto. No requieren rutas de usuario ni instalaciones globales de OpenGL/GLEW.

El ejecutable y las DLL necesarias se generan en `bin/Win32/Debug/` o `bin/Win32/Release/`. Los archivos intermedios quedan en `obj/`. Visual Studio ejecuta desde `ConfigInicial/` para encontrar `Shader/`, `Models/` e `images/`. Al ejecutar manualmente, usar tambien ese directorio de trabajo.

## Dependencias

- GLEW: encabezados de `External Libraries/GLEW/include`, `lib/Release/Win32/glew32.lib` y la DLL existente `ConfigInicial/glew32.dll`. El archivo de enlace restaurado procede de la copia local del curso, cuyos encabezados y DLL coinciden por SHA-256 con los del proyecto. Distribucion oficial: https://glew.sourceforge.net/.
- GLFW: se enlaza `glfw3dll.lib` y se copia `glfw3.dll` junto al ejecutable, evitando mezclar el runtime del binario estatico de Release con el de Debug.
- SOIL2: se compilan los cuatro archivos C incluidos en `ConfigInicial/SOIL2/` para cada configuracion, en vez de enlazar `soil2-debug.lib` en ambas.
- Assimp: se utiliza `assimp-vc140-mt.lib` y se copia su DLL incluida. Esta DLL depende del runtime de depuracion de Visual C++ (`MSVCP140D.dll`, `VCRUNTIME140D.dll`, `ucrtbased.dll`), tambien en Release. La maquina de desarrollo debe tener Visual Studio con C++ instalado; para distribuir el programa hay que sustituir Assimp por una compilacion Release compatible.
- GLM: solo necesita encabezados. OpenGL se enlaza mediante `opengl32.lib` del Windows SDK.

La unidad principal actual es `Mixquic.cpp` (antes `Iluminacion.cpp`). Los demas ejemplos tienen sus propios `main` y no se deben agregar todos a la compilacion simultaneamente.

## Recursos pendientes del repositorio

La prueba de arranque detecto que no se incluyeron Models/TumbaTransparente.obj ni Models/Blue+Mushroom.obj. Su carga y sus bloques de dibujo en `Mixquic.cpp` quedaron comentados temporalmente, con marcas TODO. Cuando esten disponibles los archivos, descomentar ambos bloques para cada modelo. piso.obj se restauro desde la copia local del curso, verificando que piso.mtl coincide por SHA-256. Estos recursos son independientes de las bibliotecas y de la compilacion.




## Iglesia V2 experimental — Fase 2B

V2 se carga por defecto. Pulsar **F2** para alternar V1/V2; solo se dibuja un templo. Tambien se puede iniciar con `--iglesia=v1` o `--iglesia=v2`, conservando como directorio de trabajo ConfigInicial/. En Visual Studio, agregar ese argumento en las propiedades de depuracion para elegir la version de inicio.

Ambas versiones se colocan en (0,0,-8.5), fachada +Z y Y arriba. V1 conserva escala 0.7; V2 usa 1.0 porque ya mide 8.96 de ancho, 10.43 de profundidad y 8.52 de altura. Los recursos V1 no se modificaron. V2 esta en ConfigInicial/Models/Iglesia_Mixquic_V2/, con cuatro PNG en textures/ y rutas relativas.

Validacion reproducible: ConfigInicial.exe --iglesia=v2 --validar-escena CARPETA_EXISTENTE (repetir con v1). Comprueba los recursos de la GPU y genera 20 capturas deterministas, incluidas fachada, lateral y vista superior. Evidencias y comparativas: Pruebas_Assets/Integracion_Iglesia_V2_001/. No se cambiaron las luces globales, shaders, la ofrenda ni el recorrido.


## Ofrenda V2 — Fase 3A

La ofrenda enriquecida es la opción predeterminada. Se conserva la anterior intacta en Models/ofrenda.obj y Models/ofrenda.mtl. Para iniciar con ella usar --ofrenda=v1; para la nueva usar --ofrenda=v2. Estos argumentos son independientes de --iglesia=v1/v2 y del selector F2 del templo.

La nueva malla está en ConfigInicial/Models/Ofrenda_Mixquic_V2/. Mantiene la posición (-0.8,0.1,-19.25), escala 0.5, Y arriba y fachada +Z. Mide 3.24 de ancho, 2.45 de profundidad y 3.0 de altura en la escena. Tiene 81.455 triángulos, 18 materiales con Kd/Ke y ninguna textura externa. Los tres niveles originales se conservan como base; se añadieron arco floral exterior, velas, ramos, pétalos, retratos, papel picado y ofrendas.

Validar desde ConfigInicial/: ConfigInicial.exe --ofrenda=v2 --validar-escena CARPETA_EXISTENTE. Se conservan las 20 vistas anteriores y se añaden cuatro capturas completas de la ofrenda. Evidencias, comparación y archivo Blender editable: Pruebas_Assets/Ofrenda_Mixquic_V2_001/. No se modificaron iglesia, tumbas, decoración existente, iluminación global ni shaders.


## Distribución variada — Fase 3C

La distribución nueva es predeterminada: 14 tumbas, siete variantes, ornamentación A/B/C. Para comparar con las nueve anteriores iniciar con --distribucion=anterior; --distribucion=nueva restaura la opción actual. Ejecutar desde ConfigInicial/, o poner el argumento en las propiedades de depuración. Iglesia, ofrenda, controles e iluminación se conservan.

Biblioteca: ConfigInicial/Models/Tumbas_Mixquic/, tres PNG compartidas entre modelos. Recursos ligeros derivados: ConfigInicial/Models/Decoracion_Mixquic_3C/. Assets y Blender aprobados intactos.

--validar-escena CARPETA_EXISTENTE genera 27 capturas; --medir-fps CARPETA_EXISTENTE mide tres vistas deterministas (1000x700, VSync desactivado, 30 cuadros de calentamiento + 120 medidos, glFinish). Usar carpetas nuevas para cada prueba. Informe, inventario, comparación y respaldo: Pruebas_Assets/Fase3C_Distribucion_001/INFORME_FASE3C.md. Debug/Release x86 verificados. Sin commits ni limpieza del proyecto.


## Checkpoint de integración en staging

Esta copia contiene el estado aprobado de Mixquic Fase 3. El principal es ConfigInicial/Mixquic.cpp; la solución conserva Debug/Release x86 (Win32 en el proyecto), MSVC v143 y Windows SDK 10. Las bibliotecas mantienen sus versiones existentes. Assimp requiere el runtime Debug de Visual C++ también al ejecutar Release; no es todavía un paquete portátil de distribución.

Compilar desde la raíz de la solución y ejecutar con directorio de trabajo ConfigInicial/. Por ejemplo, desde ConfigInicial/:

    & "..\bin\Win32\Release\ConfigInicial.exe" --iglesia=v2 --ofrenda=v2 --distribucion=nueva

Se conservan --iglesia=v1/v2, F2 para alternar templo, --ofrenda=v1/v2 y --distribucion=anterior/nueva. --validar-escena CARPETA_NUEVA_EXISTENTE genera 27 capturas; --medir-fps CARPETA_NUEVA_EXISTENTE mide con las condiciones documentadas en Fase 3C. Usar carpetas de salida externas al árbol de recursos.

Las referencias históricas de este README a Pruebas_Assets, renders, checkpoints y archivos Blender describen evidencias de desarrollo archivadas aparte: no son dependencias de ejecución ni se copiaron a staging. El inventario y el informe de este checkpoint se entregan por separado. No se cambiaron shaders, iluminación, cámara, controles ni versiones de bibliotecas. No se realizaron commits ni publicación.
