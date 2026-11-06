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

La unidad principal sigue siendo `Iluminacion.cpp`. Los demas ejemplos tienen sus propios `main` y no se deben agregar todos a la compilacion simultaneamente.

## Recursos pendientes del repositorio

La prueba de arranque detecto que no se incluyeron Models/TumbaTransparente.obj ni Models/Blue+Mushroom.obj. Su carga y sus bloques de dibujo en Iluminacion.cpp quedaron comentados temporalmente, con marcas TODO. Cuando esten disponibles los archivos, descomentar ambos bloques para cada modelo. piso.obj se restauro desde la copia local del curso, verificando que piso.mtl coincide por SHA-256. Estos recursos son independientes de las bibliotecas y de la compilacion.


