# Script de compilación para Vigilante del Equilibrio
Write-Host "Compilando Vigilante del Equilibrio..." -ForegroundColor Green

# Verificar si existe Visual Studio
$vsPath = ""
$vs2022Path = "${env:ProgramFiles}\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe"
$vs2019Path = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\MSBuild.exe"

if (Test-Path $vs2022Path) {
    $vsPath = $vs2022Path
    Write-Host "Usando Visual Studio 2022" -ForegroundColor Yellow
} elseif (Test-Path $vs2019Path) {
    $vsPath = $vs2019Path
    Write-Host "Usando Visual Studio 2019" -ForegroundColor Yellow
} else {
    Write-Host "No se encontró Visual Studio. Intentando con dotnet..." -ForegroundColor Red
    
    # Intentar con dotnet
    try {
        dotnet build VigilanteDelEquilibrio.vcxproj -c Release
        if ($LASTEXITCODE -eq 0) {
            Write-Host "Compilación exitosa con dotnet" -ForegroundColor Green
        } else {
            Write-Host "Error en la compilación con dotnet" -ForegroundColor Red
        }
    } catch {
        Write-Host "Error: No se pudo compilar con dotnet" -ForegroundColor Red
    }
    exit
}

# Compilar en Release
Write-Host "Compilando en modo Release..." -ForegroundColor Yellow
& $vsPath "VigilanteDelEquilibrio.vcxproj" /p:Configuration=Release /p:Platform=x86

if ($LASTEXITCODE -eq 0) {
    Write-Host "Compilación exitosa!" -ForegroundColor Green
    
    # Copiar recursos
    if (Test-Path "Release") {
        Write-Host "Copiando recursos..." -ForegroundColor Yellow
        
        # Crear directorios necesarios
        New-Item -ItemType Directory -Force -Path "Release\recursos" | Out-Null
        New-Item -ItemType Directory -Force -Path "Release\FILES" | Out-Null
        
        # Copiar archivos
        Copy-Item "recursos\*" "Release\recursos\" -Force
        Copy-Item "FILES\*" "Release\FILES\" -Force
        
        Write-Host "Recursos copiados exitosamente" -ForegroundColor Green
        
        # Verificar ejecutable
        if (Test-Path "Release\VigilanteDelEquilibrio.exe") {
            Write-Host "Ejecutable creado: Release\VigilanteDelEquilibrio.exe" -ForegroundColor Green
        } else {
            Write-Host "No se encontró el ejecutable." -ForegroundColor Red
        }
    } else {
        Write-Host "No se encontró la carpeta Release" -ForegroundColor Red
    }
} else {
    Write-Host "Error en la compilación" -ForegroundColor Red
}
