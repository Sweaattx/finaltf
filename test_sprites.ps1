Write-Host "=== VIGILANTE DEL EQUILIBRIO - PRUEBA DE SPRITES ===" -ForegroundColor Green
Write-Host ""

# Verificar que los archivos de imagen existen
Write-Host "Verificando archivos de imagen..." -ForegroundColor Yellow
$imageFiles = @(
    "recursos\jugador.png",
    "recursos\enemigo1_mundo1.png", 
    "recursos\enemigo2_mundo1.png",
    "recursos\enemigo3_mundo1.png",
    "recursos\menu_fondo.png",
    "recursos\mundo1.png"
)

foreach ($file in $imageFiles) {
    if (Test-Path $file) {
        try {
            $img = New-Object System.Drawing.Bitmap $file
            Write-Host "✓ $file - Dimensiones: $($img.Width)x$($img.Height)" -ForegroundColor Green
            $img.Dispose()
        } catch {
            Write-Host "✗ $file - Error al cargar" -ForegroundColor Red
        }
    } else {
        Write-Host "✗ $file - NO ENCONTRADO" -ForegroundColor Red
    }
}

Write-Host ""
Write-Host "=== INSTRUCCIONES DE PRUEBA ===" -ForegroundColor Cyan
Write-Host "1. Compila el proyecto desde Visual Studio"
Write-Host "2. Ejecuta el juego"
Write-Host "3. Presiona F12 para activar modo debug"
Write-Host "4. Verifica que los sprites se vean completos (32x32 pixeles)"
Write-Host "5. Al cargar el juego, veras dialogos con informacion de dimensiones"
Write-Host ""
Write-Host "CAMBIOS APLICADOS:" -ForegroundColor Yellow
Write-Host "- Deteccion automatica de tamaño de frame basada en dimensiones de imagen"
Write-Host "- Sprites ahora se dibujan con tamaño 32x32 (DrawFrameLarge)"
Write-Host "- Modo debug muestra informacion detallada de rectangulos"
Write-Host "- Mensajes de advertencia si las dimensiones no coinciden"
