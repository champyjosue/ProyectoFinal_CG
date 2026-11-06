$ErrorActionPreference = 'Stop'
$source = 'C:\Users\kaleb\OneDrive\Escritorio\ProyectoFinal_CG'
$destination = 'C:\Users\kaleb\OneDrive\Escritorio\PrototipoMixquicV1'
$validationRoot = Join-Path $PSScriptRoot 'capturas-Reubicado'
if (Test-Path -LiteralPath $destination) { throw 'La carpeta de destino ya existe; no se sobrescribira.' }

# Copia completa del proyecto y su historial. Se omiten caches y compilaciones antiguas.
# No se excluye *.obj: en Models son recursos Wavefront necesarios.
$excludedDirectories = @(
    (Join-Path $source '.vs'), (Join-Path $source 'bin'), (Join-Path $source 'obj'),
    (Join-Path $source 'x64'), (Join-Path $source 'ConfigInicial\x64'),
    (Join-Path $source 'ConfigInicial\Debug'), (Join-Path $source 'ConfigInicial\Release'))
& robocopy $source $destination /E /COPY:DAT /DCOPY:DAT /R:1 /W:1 /NFL /NDL /NJH /NJS /XD $excludedDirectories /XF 'prototipo-Aplicar-compilacion.log'
if ($LASTEXITCODE -ge 8) { throw "Error al copiar el proyecto: $LASTEXITCODE" }

$criticalFiles = @('ConfigInicial.sln','ConfigInicial\ConfigInicial.vcxproj',
    'ConfigInicial\Iluminacion.cpp','ConfigInicial\Model.h','ConfigInicial\Mesh.h',
    'ConfigInicial\Camera.h','ConfigInicial\Shader\lighting.frag','.git\config','.git\HEAD')
foreach ($relative in $criticalFiles) {
    if ((Get-FileHash (Join-Path $source $relative)).Hash -ne (Get-FileHash (Join-Path $destination $relative)).Hash) {
        throw "La copia no coincide: $relative"
    }
}
$pythonFiles = @(Get-ChildItem -LiteralPath $destination -Filter '*.py' -Recurse -File -Force)
if ($pythonFiles.Count) { throw 'La copia contiene scripts de Python inesperados.' }

$readmeFile = Join-Path $destination 'README.md'
$readme = Get-Content -LiteralPath $readmeFile -Raw -Encoding UTF8
$readme = $readme.Replace('# ProyectoFinal_CG', '# Panteon de Mixquic v1.0 - PrototipoMixquicV1')
$readme = $readme.Replace('Proyecto de Computacion Grafica con OpenGL, GLEW, GLFW, GLM, Assimp y SOIL2.',
    'Prototipo navegable del Panteon de Mixquic con OpenGL, GLEW, GLFW, GLM, Assimp y SOIL2. Distribucion, cambios y pruebas en [MIXQUIC_V1.md](MIXQUIC_V1.md). No requiere Python; se compila y ejecuta desde Visual Studio.')
[IO.File]::WriteAllText($readmeFile,$readme,[Text.UTF8Encoding]::new($false))
$documentationFile = Join-Path $destination 'MIXQUIC_V1.md'
$documentation = Get-Content -LiteralPath $documentationFile -Raw -Encoding UTF8
$documentation = $documentation.Replace('desde la carpeta `ProyectoFinal_CG`', 'desde la carpeta `PrototipoMixquicV1` del escritorio')
$documentation += "`n## Ubicacion de entrega`n`nEl proyecto completo esta en ``PrototipoMixquicV1`` del escritorio. La carpeta anterior ``ProyectoFinal_CG`` se conserva como respaldo. No se requieren archivos de Python para compilar, ejecutar ni generar las capturas; las herramientas auxiliares de preparacion permanecen fuera del proyecto entregado.`n"
[IO.File]::WriteAllText($documentationFile,$documentation,[Text.UTF8Encoding]::new($false))

$msbuild = 'C:\Program Files\Microsoft Visual Studio\18\Community\MSBuild\Current\Bin\MSBuild.exe'
& $msbuild (Join-Path $destination 'ConfigInicial.sln') /t:Build /p:Configuration=Debug /p:Platform=x86 /p:PreferredToolArchitecture=x64 /m:1 /nr:false /v:minimal /nologo "/flp:logfile=$PSScriptRoot\reubicado-compilacion.log;verbosity=normal"
if ($LASTEXITCODE -ne 0) { throw 'La compilacion en la nueva ruta fallo.' }
New-Item -ItemType Directory -Path $validationRoot -Force | Out-Null
$process = Start-Process (Join-Path $destination 'bin\Win32\Debug\ConfigInicial.exe') -ArgumentList @('--validar-escena',('"'+$validationRoot+'"')) -WorkingDirectory (Join-Path $destination 'ConfigInicial') -WindowStyle Hidden -RedirectStandardOutput "$validationRoot\stdout.log" -RedirectStandardError "$validationRoot\stderr.log" -PassThru
$processHandle = $process.Handle
if (-not $process.WaitForExit(60000)) { Stop-Process -Id $process.Id; throw 'La prueba de la nueva ruta excedio 60 segundos.' }
$process.Refresh()
if ($process.ExitCode -ne 0) { throw "La prueba termino con codigo $($process.ExitCode)." }
$errors = Get-Content "$validationRoot\stderr.log" -Raw
if (-not [string]::IsNullOrWhiteSpace($errors)) { throw $errors }
Get-Content "$validationRoot\stdout.log"
Write-Output "Proyecto listo en: $destination"
Write-Output 'Debug x86 compilado y ejecutado desde la nueva ruta. No requiere Python.'
