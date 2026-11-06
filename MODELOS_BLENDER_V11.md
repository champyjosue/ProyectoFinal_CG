# Primer lote de modelos originales — Blender 5.2.3 LTS

Se utilizó la instalación de Microsoft Store, paquete `5.2.3.0`, ejecutada mediante su alias oficial `blender-launcher.exe`. Se comprobó `bpy.app.version_string`: **5.2.3 LTS**.

## Entrega e integración

| Modelo | Triángulos | Tamaño aproximado (ancho × altura × profundidad) | Uso |
|---|---:|---|---|
| `visitante_veladora` | 2640 | 0.648 × 1.767 × 0.436 m | Seis visitantes estáticos, reutilizando una sola malla |
| `arreglo_cempasuchil` | 5260 | 0.603 × 0.780 × 0.603 m | Diez arreglos: ocho junto a las tumbas y dos en La Alumbrada |
| `lapida_memoria` | 4644 | 1.020 × 1.430 × 0.620 m | Variante en la primera sepultura izquierda; se conservan nueve tumbas |

Son modelos estilizados para prototipo. El visitante tiene una pose fija sosteniendo una vela: no incluye esqueleto ni animación. Las seis personas son instancias del mismo modelo con orientaciones y escalas ligeramente distintas; futuras versiones podrán incorporar ropa y poses adicionales.

Los archivos OBJ y MTL están en `ConfigInicial/Models/BlenderV11/`. Se cargan una sola vez y se reutilizan con transformaciones. Se conservan los OBJ antiguos y siguen utilizándose los tres tipos originales de tumba en otras posiciones.

Las exportaciones están agrupadas en una malla por modelo y por material para reducir llamadas de dibujo; el archivo Blender conserva las piezas separadas para edición. La llama usa Kd > 1 en el MTL exportado, como espera el shader actual. Si se reexporta manualmente, conservar ese material del MTL o volver a establecer su Kd para mantener la emisión; el cargador actual no interpreta automáticamente toda la configuración de nodos de Blender.

## Corrección de orientación de las lápidas

En `Iluminacion.cpp` se agregaron **180° a la rotación Y** de las ocho sepulturas laterales, conservando su variación de ±12°. La tumba de La Alumbrada también se gira 180° en Y. La nueva lápida se exportó con el mismo convenio frontal que las tumbas anteriores, por lo que utiliza la misma corrección.

El centrado y el apoyo siguen calculándose a partir de los límites reales de cada modelo; la rotación no desplaza las tumbas ni modifica los caminos.

## Editar en Blender

Abrir `FuentesBlender/Mixquic_PrimerosModelos.blend`. Contiene:

- `Galeria_Modelos_Mixquic`: presentación de los tres modelos mediante instancias, con cámara y luces de estudio.
- Una escena independiente por modelo (`visitante_veladora`, `arreglo_cempasuchil`, `lapida_memoria`), con las piezas originales en coordenadas locales, listas para editar o reexportar.

Para reexportar, seleccionar la escena del modelo, seleccionar sus mallas y exportar Wavefront OBJ con normales, materiales, triangulación, Forward `-Z` y Up `Y`, a escala 1. El modelo humano exportado mira hacia +Z. La lápida exportada mira hacia −Z y el escenario la gira 180° en Y.

Las cámaras, luces y suelo de la galería son solo de estudio y no se exportan al juego. La iluminación vista en Blender es una presentación; el aspecto dentro de OpenGL utiliza el shader y las cinco luces existentes.

`modelos_manifest.json` registra dimensiones y triángulos. `Previsualizacion.png` muestra la galería renderizada en Blender.

No hace falta Python para abrir el `.blend`, editar manualmente los modelos, compilar ni ejecutar el proyecto. Los scripts de autoría se utilizaron como herramientas auxiliares fuera de la entrega de C++.

## Pruebas

- Creación, exportación y render ejecutados realmente en Blender 5.2.3 LTS.
- Inspección visual de la galería; se corrigieron la orientación de la inscripción y las uniones de las piernas antes de entregar.
- Compilación Debug x86: 0 errores y 0 advertencias.
- Ejecución real en OpenGL 3.3 con Intel UHD Graphics, carga de los tres modelos y 16 capturas de comprobación.
- Comprobaciones de nueve tumbas, recorrido libre y decoración sin invadir tumbas ni templo.
- Comprobaciones de WASD, flechas y mouse; se conservan las animaciones existentes y sus 401 muestras de trayectorias.
- Sin errores de OpenGL, recursos ni shaders durante la validación. No se afirma una sesión manual prolongada dentro de Visual Studio.

Se mantiene la configuración Debug x86, las bibliotecas y los shaders existentes. No se realizaron commits, push ni merges. Las referencias a `TumbaTransparente.obj` y `Blue+Mushroom.obj` permanecen comentadas.

## Archivos de código y recursos

- Modificado: `ConfigInicial/Iluminacion.cpp`.
- Nuevos: seis archivos OBJ/MTL en `ConfigInicial/Models/BlenderV11/`.
- Nuevos: `.blend`, manifiesto y vista previa en `FuentesBlender/`.
- Nuevo: este documento.
- `.gitignore`: excepción para versionar los nuevos OBJ como modelos 3D, evitando confundirlos con archivos intermedios del compilador. No se modifica la configuración remota de Git.
