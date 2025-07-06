# Script de compilación para el juego Vigilante del Equilibrio
# Busca automáticamente el compilador de C++ y compila el proyecto

Write-Host "Buscando compilador de C++..."

# Buscar diferentes versiones de Visual Studio
$vsPaths = @(
    "C:\Program Files\Microsoft Visual Studio\2022\*\VC\Auxiliary\Build\vcvarsall.bat",
    "C:\Program Files\Microsoft Visual Studio\2019\*\VC\Auxiliary\Build\vcvarsall.bat",
    "C:\Program Files (x86)\Microsoft Visual Studio\2019\*\VC\Auxiliary\Build\vcvarsall.bat",
    "C:\Program Files (x86)\Microsoft Visual Studio\2017\*\VC\Auxiliary\Build\vcvarsall.bat"
)

$vcvarsPath = $null
foreach ($path in $vsPaths) {
    $found = Get-ChildItem $path -ErrorAction SilentlyContinue | Select-Object -First 1
    if ($found) {
        $vcvarsPath = $found.FullName
        break
    }
}

if ($vcvarsPath) {
    Write-Host "Encontrado Visual Studio en: $vcvarsPath"
    
    # Crear un archivo batch temporal para compilar
    $batchContent = @"
@echo off
call "$vcvarsPath" x64
cl /clr /EHa main.cpp /Fe:VigilanteDelEquilibrio.exe /link /SUBSYSTEM:WINDOWS /ENTRY:main
"@
    
    $batchFile = ".\compile_temp.bat"
    $batchContent | Out-File -FilePath $batchFile -Encoding ASCII
    
    Write-Host "Compilando el proyecto..."
    & cmd /c $batchFile
    
    # Limpiar archivo temporal
    Remove-Item $batchFile -ErrorAction SilentlyContinue
    
    if (Test-Path ".\VigilanteDelEquilibrio.exe") {
        Write-Host "Compilación exitosa! Ejecutable creado: VigilanteDelEquilibrio.exe"
        Write-Host "Ejecutando el juego..."
        Start-Process ".\VigilanteDelEquilibrio.exe"
    } else {
        Write-Host "Error en la compilación."
    }
} else {
    Write-Host "No se encontró Visual Studio instalado."
    Write-Host "Opciones alternativas:"
    Write-Host "1. Instalar Visual Studio Community (gratuito)"
    Write-Host "2. Usar Visual Studio Code con la extensión C/C++"
    Write-Host "3. Compilar manualmente con otro compilador"
}
