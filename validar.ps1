param([ValidateSet('Base','Prototipo','Aplicar')][string]$Modo = 'Base')
$ErrorActionPreference = 'Stop'
$stage = $PSScriptRoot
$destination = 'C:\Users\kaleb\OneDrive\Escritorio\ProyectoFinal_CG'
$msbuild = 'C:\Program Files\Microsoft Visual Studio\18\Community\MSBuild\Current\Bin\MSBuild.exe'
function Compilar([string]$root, [string]$logName) {
    & $msbuild (Join-Path $root 'ConfigInicial.sln') /t:Build /p:Configuration=Debug /p:Platform=x86 /p:PreferredToolArchitecture=x64 /m:1 /nr:false /v:minimal /nologo "/flp:logfile=$stage\$logName;verbosity=normal"
    if ($LASTEXITCODE -ne 0) { throw 'Error de compilacion Debug x86.' }
}
if ($Modo -eq 'Base') {
    Compilar $stage 'base-compilacion.log'
    $p = Start-Process (Join-Path $stage 'bin\Win32\Debug\ConfigInicial.exe') -WorkingDirectory (Join-Path $stage 'ConfigInicial') -WindowStyle Hidden -RedirectStandardOutput "$stage\base.stdout.log" -RedirectStandardError "$stage\base.stderr.log" -PassThru
    try {
        if ($p.WaitForExit(15000)) { throw "La base termino antes de tiempo: $($p.ExitCode)" }
        $p.Refresh()
        Write-Output "Base activa tras 15 segundos. Responde: $($p.Responding)"
    } finally {
        if (-not $p.HasExited) { [void]$p.CloseMainWindow(); if (-not $p.WaitForExit(3000)) { Stop-Process -Id $p.Id } }
    }
    $log = (Get-Content "$stage\base.stdout.log" -Raw) + (Get-Content "$stage\base.stderr.log" -Raw)
    if (-not [string]::IsNullOrWhiteSpace($log)) { throw $log }
    Write-Output 'Base funcional verificada sin errores de recursos ni shaders.'
    exit
}
if ($Modo -eq 'Aplicar') {
    $hashes = Get-Content "$stage\base-hashes.json" -Raw | ConvertFrom-Json
    foreach ($property in $hashes.PSObject.Properties) {
        if ((Get-FileHash (Join-Path $destination $property.Name)).Hash -ne $property.Value) { throw "El archivo $($property.Name) cambio; revisar antes de aplicar." }
    }
    foreach ($relative in @('ConfigInicial\Iluminacion.cpp','ConfigInicial\Model.h','ConfigInicial\Mesh.h','ConfigInicial\Camera.h','ConfigInicial\Shader\lighting.frag','MIXQUIC_V1.md')) {
        Copy-Item -LiteralPath (Join-Path $stage $relative) -Destination (Join-Path $destination $relative) -Force
    }
    $stage = $destination
}
Compilar $stage ("prototipo-$Modo-compilacion.log")
$captures = Join-Path $PSScriptRoot ("capturas-$Modo")
New-Item -ItemType Directory -Path $captures -Force | Out-Null
$p = Start-Process (Join-Path $stage 'bin\Win32\Debug\ConfigInicial.exe') -ArgumentList @('--validar-escena', ('"' + $captures + '"')) -WorkingDirectory (Join-Path $stage 'ConfigInicial') -WindowStyle Hidden -RedirectStandardOutput "$captures\stdout.log" -RedirectStandardError "$captures\stderr.log" -PassThru
$processHandle = $p.Handle
if (-not $p.WaitForExit(60000)) { Stop-Process -Id $p.Id; throw 'La validacion excedio 60 segundos.' }
$p.Refresh()
if ($p.ExitCode -ne 0) { throw "Error en validacion grafica: $($p.ExitCode). Ver $captures" }
Get-Content "$captures\stdout.log"
$errors = Get-Content "$captures\stderr.log" -Raw
if (-not [string]::IsNullOrWhiteSpace($errors)) { throw $errors }
Write-Output "Validacion finalizada: $captures"
