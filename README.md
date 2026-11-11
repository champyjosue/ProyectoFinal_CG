# Panteón de Mixquic · ProyectoFinal_CG

Recorrido nocturno de La Alumbrada en OpenGL 3.3. La escena predeterminada tiene un terreno de 50 × 64 unidades, 62 tumbas, 326 adornos, 49 plantas, iglesia V2, ofrenda híbrida y cinco visitantes articulados. Incluye portón animado, cielo nocturno, campana, luciérnaga, cinco globos de Cantoya, sombras direccionales y humo de copal.

## Compilar y ejecutar

1. Instala Visual Studio 2022 con **Desarrollo para el escritorio con C++**, MSVC v143, Windows SDK 10 y el controlador gráfico con soporte para OpenGL 3.3.
2. Abre `ConfigInicial.sln`. Selecciona `Debug | x86` o `Release | x86`. En el proyecto, la plataforma se llama `Win32`.
3. Compila la solución y ejecuta con F5 o Ctrl+F5. El proyecto establece `ConfigInicial` como directorio de trabajo.

La unidad principal compilada es `ConfigInicial/Mixquic.cpp`. Los ejemplos de prácticas quedan fuera de la compilación de esta solución. La salida se genera en `bin/Win32/Debug` o `bin/Win32/Release` y los intermedios en `obj`.

Para ejecutar manualmente desde PowerShell, en la raíz del proyecto:

```powershell
Set-Location -LiteralPath .\ConfigInicial
& "..\bin\Win32\Release\ConfigInicial.exe"
```

Mantén `ConfigInicial` como directorio de trabajo. Los modelos, texturas, shaders y caras del cubemap se resuelven mediante rutas relativas.

## Dependencias y limitaciones

- Se conservan GLEW, GLFW y Assimp x86 de la base del proyecto. El proyecto copia sus tres DLL junto al ejecutable al compilar. GLM usa encabezados, SOIL2 se compila desde sus cuatro archivos C y OpenGL enlaza con `opengl32.lib` del Windows SDK.
- La DLL incluida `assimp-vc140-mt.dll` requiere el CRT **de depuración** de Visual C++ también al ejecutar Release. Entre sus dependencias están `MSVCP140D.dll`, `VCRUNTIME140D.dll` y `ucrtbased.dll`. El redistribuible estándar de Release por sí solo no cubre ese requisito. La entrega se valida en un equipo de desarrollo con Visual Studio y C++.
- Las bibliotecas incluidas son de 32 bits. Un cambio a x64 requiere dependencias compatibles de 64 bits.
- El mapa direccional usa geometría estática de la iglesia y las tumbas. Las otras fuentes conservan sus aportes locales sin mapas de sombras propios.

## Controles

| Control | Acción |
|---|---|
| W, A, S, D o flechas | Caminar y desplazarse lateralmente |
| Ratón | Mirar alrededor |
| Shift izquierdo o derecho | Correr mientras se mantiene pulsado |
| R | Abrir o cerrar el portón cuando el muro está activo |
| F2 | Alternar la iglesia V1 y V2 |
| F6 | Reiniciar las animaciones de los visitantes |
| Esc | Cerrar |

## Demostraciones

Pasa un argumento al iniciar para colocar la cámara de la demostración correspondiente.

| Demostración | Argumento |
|---|---|
| Colocar una flor | `--demo-personaje=flor` |
| Encender una veladora | `--demo-personaje=veladora` |
| Persignarse | `--demo-personaje=oracion` |
| Caminar hasta una tumba | `--demo-personaje=caminar` |
| Arrodillarse | `--demo-personaje=rodillas` |
| Campana | `--demo-ambiente=campana` |
| Luciérnaga | `--demo-ambiente=insecto` |
| Globos de Cantoya | `--demo-ambiente=globos` |

## Selectores de escena

- `--iluminacion=alumbrada` activa el perfil predeterminado. `--iluminacion=original` recupera la iluminación de Fase 4F.
- `--sombras=off` y `--humo=off` desactivan por separado esos efectos dentro de Alumbrada.
- `--cantoya-modelo=v1` recupera la geometría anterior. `--cantoya-modelo=v2` activa la predeterminada. `--globos=off` oculta los globos.
- `--vegetacion=off`, `--muro=off`, `--skybox=off` y `--personajes=off` sirven para comparaciones.
- `--iglesia=v1|v2`, `--ofrenda=v1|v2|v2-hibrida` y `--distribucion=62|77|anterior` permiten recuperar variantes previas. Pasa uno de los valores indicados, por ejemplo `--distribucion=77`.

## Verificación reproducible

Desde `ConfigInicial`, crea una carpeta vacía fuera del árbol de recursos. Usa su ruta con `--validar-escena`.

```powershell
$evidencia = Join-Path ([System.IO.Path]::GetTempPath()) ('Mixquic-' + [guid]::NewGuid())
New-Item -ItemType Directory -Path $evidencia | Out-Null
& "..\bin\Win32\Release\ConfigInicial.exe" --validar-navegacion --validar-escena $evidencia
```

En la configuración predeterminada, esta prueba produce 45 capturas, comprueba los recorridos, los controles y los recursos de la escena y guarda una lectura del mapa de profundidad. Para medir rendimiento, usa `--medir-fps` con otra carpeta vacía y las mismas condiciones de GPU, energía, resolución y perfil de escena.
