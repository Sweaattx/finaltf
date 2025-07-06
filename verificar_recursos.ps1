# Script para verificar recursos necesarios
Write-Host "=== VERIFICACIÓN DE RECURSOS ===" -ForegroundColor Green
Write-Host ""

$recursosNecesarios = @(
    "jugador.png",
    "enemigo1_mundo1.png",
    "enemigo2_mundo1.png", 
    "enemigo3_mundo1.png",
    "enemigo1_mundo2.png",
    "enemigo2_mundo2.png",
    "enemigo3_mundo2.png",
    "mundo1.png",
    "mundo2.png",
    "mundo3.png",
    "menu_fondo.png"
)

Write-Host "Verificando directorio: recursos/" -ForegroundColor Yellow
$recursosFaltantes = @()

foreach ($archivo in $recursosNecesarios) {
    $rutaCompleta = "recursos\$archivo"
    if (Test-Path $rutaCompleta) {
        Write-Host "✅ $archivo - ENCONTRADO" -ForegroundColor Green
    } else {
        Write-Host "❌ $archivo - FALTA" -ForegroundColor Red
        $recursosFaltantes += $archivo
    }
}

Write-Host ""
if ($recursosFaltantes.Count -eq 0) {
    Write-Host "🎉 TODOS LOS RECURSOS ESTÁN DISPONIBLES" -ForegroundColor Green
} else {
    Write-Host "⚠️  RECURSOS FALTANTES:" -ForegroundColor Yellow
    foreach ($archivo in $recursosFaltantes) {
        Write-Host "  - $archivo" -ForegroundColor Red
    }
    Write-Host ""
    Write-Host "Por favor, copia estos archivos a la carpeta 'recursos/'" -ForegroundColor Yellow
}

Write-Host ""
Write-Host "Verificando directorio de Release..." -ForegroundColor Yellow
if (Test-Path "Release\recursos") {
    Write-Host "✅ Release\recursos\ - EXISTE" -ForegroundColor Green
} else {
    Write-Host "❌ Release\recursos\ - NO EXISTE" -ForegroundColor Red
}
