# Script de compilación para Vigilante del Equilibrio
# Ejecutar desde PowerShell como     } else {
        Write-Host "No se encontro el ejecutable." -ForegroundColor Red
    }
}nistrador

Write-Host "=== Vigilante del Equilibrio - Script de Compilación ===" -ForegroundColor Green
Write-Host ""

# Verificar que estamos en el directorio correcto
if (!(Test-Path "VigilanteDelEquilibrio.sln")) {
    Write-Host "Error: No se encuentra el archivo de solución. Ejecuta este script desde el directorio del proyecto." -ForegroundColor Red
    exit 1
}

# Verificar Visual Studio
$vsPath = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\MSBuild.exe"
if (!(Test-Path $vsPath)) {
    $vsPath = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe"
}

if (!(Test-Path $vsPath)) {
    Write-Host "Error: No se encuentra MSBuild. Instala Visual Studio 2019 o 2022 con C++/CLI support." -ForegroundColor Red
    exit 1
}

Write-Host "Encontrado MSBuild en: $vsPath" -ForegroundColor Yellow

# Verificar estructura de directorios
Write-Host "Verificando estructura de directorios..." -ForegroundColor Yellow

if (!(Test-Path "recursos")) {
    New-Item -ItemType Directory -Path "recursos"
    Write-Host "Creado directorio recursos/" -ForegroundColor Green
}

if (!(Test-Path "FILES")) {
    New-Item -ItemType Directory -Path "FILES"
    Write-Host "Creado directorio FILES/" -ForegroundColor Green
}

if (!(Test-Path "FILES\PARAMETERS.txt")) {
    @"
VIDAS=3
TIEMPO=300
VELOCIDAD=5
"@ | Out-File -FilePath "FILES\PARAMETERS.txt" -Encoding ASCII
    Write-Host "Creado archivo PARAMETERS.txt" -ForegroundColor Green
}

# Compilar en modo Release
Write-Host "Compilando en modo Release..." -ForegroundColor Yellow
& $vsPath "VigilanteDelEquilibrio.sln" /p:Configuration=Release /p:Platform=x86

if ($LASTEXITCODE -eq 0) {
    Write-Host "¡Compilación exitosa!" -ForegroundColor Green
    
    # Copiar recursos al directorio de salida
    if (Test-Path "Release") {
        Write-Host "Copiando recursos al directorio de salida..." -ForegroundColor Yellow
        
        if (Test-Path "recursos") {
            Copy-Item -Path "recursos" -Destination "Release\" -Recurse -Force
            Write-Host "Copiado directorio recursos/" -ForegroundColor Green
        }
        
        if (Test-Path "FILES") {
            Copy-Item -Path "FILES" -Destination "Release\" -Recurse -Force
            Write-Host "Copiado directorio FILES/" -ForegroundColor Green
        }
        
        Write-Host ""
        Write-Host "=== COMPILACIÓN COMPLETADA ===" -ForegroundColor Green
        Write-Host "Ejecutable generado en: Release\VigilanteDelEquilibrio.exe" -ForegroundColor Cyan
        Write-Host ""
        Write-Host "RECORDATORIO: Asegúrate de que los archivos gráficos estén en Release\recursos\" -ForegroundColor Yellow
        Write-Host "Ver README_RECURSOS.md para la lista completa de archivos requeridos." -ForegroundColor Yellow
    }
} else {
    Write-Host "Error en la compilación. Revisa los errores en Visual Studio." -ForegroundColor Red
    exit 1
}

Write-Host ""
Write-Host "¿Deseas ejecutar el juego ahora? (S/N)" -ForegroundColor Cyan
$respuesta = Read-Host

if ($respuesta -eq "S" -or $respuesta -eq "s") {
    if (Test-Path "Release\VigilanteDelEquilibrio.exe") {
        Write-Host "Iniciando juego..." -ForegroundColor Green
        Start-Process "Release\VigilanteDelEquilibrio.exe"
    } else {
        Write-Host "No se encontró el ejecutable." -ForegroundColor Red
    }
}
