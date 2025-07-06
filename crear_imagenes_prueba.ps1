# Script para crear imágenes de prueba
# Ejecutar desde PowerShell

Write-Host "Creando imágenes de prueba básicas..." -ForegroundColor Yellow

# Función para crear una imagen de color sólido
function Create-SolidImage {
    param(
        [string]$Path,
        [int]$Width,
        [int]$Height,
        [System.Drawing.Color]$Color
    )
    
    $bitmap = New-Object System.Drawing.Bitmap($Width, $Height)
    $graphics = [System.Drawing.Graphics]::FromImage($bitmap)
    $brush = New-Object System.Drawing.SolidBrush($Color)
    
    $graphics.FillRectangle($brush, 0, 0, $Width, $Height)
    
    $bitmap.Save($Path, [System.Drawing.Imaging.ImageFormat]::Png)
    
    $graphics.Dispose()
    $brush.Dispose()
    $bitmap.Dispose()
}

# Función para crear un spritesheet básico
function Create-BasicSpritesheet {
    param(
        [string]$Path,
        [int]$SpriteWidth,
        [int]$SpriteHeight,
        [System.Drawing.Color]$Color
    )
    
    $totalWidth = $SpriteWidth * 4
    $totalHeight = $SpriteHeight * 4
    
    $bitmap = New-Object System.Drawing.Bitmap($totalWidth, $totalHeight)
    $graphics = [System.Drawing.Graphics]::FromImage($bitmap)
    $brush = New-Object System.Drawing.SolidBrush($Color)
    $pen = New-Object System.Drawing.Pen([System.Drawing.Color]::Black, 1)
    
    # Llenar con color base
    $graphics.FillRectangle($brush, 0, 0, $totalWidth, $totalHeight)
    
    # Dibujar grid
    for ($i = 0; $i -le 4; $i++) {
        $graphics.DrawLine($pen, $i * $SpriteWidth, 0, $i * $SpriteWidth, $totalHeight)
        $graphics.DrawLine($pen, 0, $i * $SpriteHeight, $totalWidth, $i * $SpriteHeight)
    }
    
    $bitmap.Save($Path, [System.Drawing.Imaging.ImageFormat]::Png)
    
    $graphics.Dispose()
    $brush.Dispose()
    $pen.Dispose()
    $bitmap.Dispose()
}

# Cargar System.Drawing
Add-Type -AssemblyName System.Drawing

# Crear directorio recursos si no existe
if (!(Test-Path "recursos")) {
    New-Item -ItemType Directory -Path "recursos"
}

# Crear spritesheet del jugador (azul)
Create-BasicSpritesheet "recursos\jugador.png" 16 24 ([System.Drawing.Color]::CornflowerBlue)
Write-Host "Creado: jugador.png" -ForegroundColor Green

# Crear enemigos mundo 1 (tonos verdes)
Create-BasicSpritesheet "recursos\enemigo1_mundo1.png" 16 16 ([System.Drawing.Color]::ForestGreen)
Create-BasicSpritesheet "recursos\enemigo2_mundo1.png" 16 16 ([System.Drawing.Color]::DarkGreen)
Create-BasicSpritesheet "recursos\enemigo3_mundo1.png" 16 16 ([System.Drawing.Color]::OliveDrab)
Write-Host "Creados: enemigos mundo 1" -ForegroundColor Green

# Crear enemigos mundo 2 (tonos azules/metálicos)
Create-BasicSpritesheet "recursos\enemigo1_mundo2.png" 16 16 ([System.Drawing.Color]::SteelBlue)
Create-BasicSpritesheet "recursos\enemigo2_mundo2.png" 16 16 ([System.Drawing.Color]::DarkSlateBlue)
Create-BasicSpritesheet "recursos\enemigo3_mundo2.png" 16 16 ([System.Drawing.Color]::MidnightBlue)
Write-Host "Creados: enemigos mundo 2" -ForegroundColor Green

# Crear fondos
Create-SolidImage "recursos\mundo1.png" 800 600 ([System.Drawing.Color]::ForestGreen)
Create-SolidImage "recursos\mundo2.png" 800 600 ([System.Drawing.Color]::DarkBlue)
Create-SolidImage "recursos\mundo3.png" 800 600 ([System.Drawing.Color]::Gray)
Create-SolidImage "recursos\menu_fondo.png" 800 600 ([System.Drawing.Color]::DarkSlateBlue)
Write-Host "Creados: fondos de mundos y menú" -ForegroundColor Green

Write-Host ""
Write-Host "¡Imágenes de prueba creadas exitosamente!" -ForegroundColor Green
Write-Host "Estas son imágenes básicas para testing. Para la versión final," -ForegroundColor Yellow
Write-Host "reemplaza con sprites detallados según las especificaciones." -ForegroundColor Yellow
