# Script para generar iconos PNG para el HUD del juego Vigilante del Equilibrio
# Asegurar que el directorio recursos existe
$recursosPath = ".\recursos"
if (-not (Test-Path $recursosPath)) {
    New-Item -ItemType Directory -Path $recursosPath
}

# Función para crear imagen PNG con texto/formas
function Create-IconPNG {
    param(
        [string]$filename,
        [string]$text,
        [int]$width = 64,
        [int]$height = 64,
        [string]$bgColor = "Red",
        [string]$textColor = "White"
    )
    
    $path = Join-Path $recursosPath $filename
    
    Add-Type -AssemblyName System.Drawing
    $bitmap = New-Object System.Drawing.Bitmap($width, $height)
    $graphics = [System.Drawing.Graphics]::FromImage($bitmap)
    
    # Fondo
    $brush = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::$bgColor)
    $graphics.FillRectangle($brush, 0, 0, $width, $height)
    
    # Texto
    $font = New-Object System.Drawing.Font("Arial", 14, [System.Drawing.FontStyle]::Bold)
    $textBrush = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::$textColor)
    $textSize = $graphics.MeasureString($text, $font)
    $x = ($width - $textSize.Width) / 2
    $y = ($height - $textSize.Height) / 2
    $graphics.DrawString($text, $font, $textBrush, $x, $y)
    
    # Guardar
    $bitmap.Save($path, [System.Drawing.Imaging.ImageFormat]::Png)
    
    # Limpiar
    $graphics.Dispose()
    $bitmap.Dispose()
    $brush.Dispose()
    $textBrush.Dispose()
    $font.Dispose()
    
    Write-Host "Creado: $filename"
}

# Función para crear corazón
function Create-HeartIcon {
    $path = Join-Path $recursosPath "corazon.png"
    
    Add-Type -AssemblyName System.Drawing
    $bitmap = New-Object System.Drawing.Bitmap(32, 32)
    $graphics = [System.Drawing.Graphics]::FromImage($bitmap)
    
    # Fondo transparente
    $graphics.Clear([System.Drawing.Color]::Transparent)
    
    # Corazón rojo
    $brush = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::Red)
    $points = @(
        [System.Drawing.Point]::new(16, 8),
        [System.Drawing.Point]::new(12, 4),
        [System.Drawing.Point]::new(8, 4),
        [System.Drawing.Point]::new(4, 8),
        [System.Drawing.Point]::new(4, 12),
        [System.Drawing.Point]::new(16, 24),
        [System.Drawing.Point]::new(28, 12),
        [System.Drawing.Point]::new(28, 8),
        [System.Drawing.Point]::new(24, 4),
        [System.Drawing.Point]::new(20, 4),
        [System.Drawing.Point]::new(16, 8)
    )
    $graphics.FillPolygon($brush, $points)
    
    $bitmap.Save($path, [System.Drawing.Imaging.ImageFormat]::Png)
    $graphics.Dispose()
    $bitmap.Dispose()
    $brush.Dispose()
    
    Write-Host "Creado: corazon.png"
}

# Función para crear reloj
function Create-ClockIcon {
    $path = Join-Path $recursosPath "reloj.png"
    
    Add-Type -AssemblyName System.Drawing
    $bitmap = New-Object System.Drawing.Bitmap(32, 32)
    $graphics = [System.Drawing.Graphics]::FromImage($bitmap)
    
    # Fondo transparente
    $graphics.Clear([System.Drawing.Color]::Transparent)
    
    # Círculo del reloj
    $brush = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::Blue)
    $graphics.FillEllipse($brush, 2, 2, 28, 28)
    
    # Fondo blanco
    $whiteBrush = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::White)
    $graphics.FillEllipse($whiteBrush, 4, 4, 24, 24)
    
    # Manecillas
    $pen = New-Object System.Drawing.Pen([System.Drawing.Color]::Black, 2)
    $graphics.DrawLine($pen, 16, 16, 16, 8)  # Hora
    $graphics.DrawLine($pen, 16, 16, 22, 16) # Minuto
    
    $bitmap.Save($path, [System.Drawing.Imaging.ImageFormat]::Png)
    $graphics.Dispose()
    $bitmap.Dispose()
    $brush.Dispose()
    $whiteBrush.Dispose()
    $pen.Dispose()
    
    Write-Host "Creado: reloj.png"
}

# Función para crear cohete
function Create-RocketIcon {
    $path = Join-Path $recursosPath "cohete.png"
    
    Add-Type -AssemblyName System.Drawing
    $bitmap = New-Object System.Drawing.Bitmap(32, 32)
    $graphics = [System.Drawing.Graphics]::FromImage($bitmap)
    
    # Fondo transparente
    $graphics.Clear([System.Drawing.Color]::Transparent)
    
    # Cohete
    $brush = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::Gold)
    $points = @(
        [System.Drawing.Point]::new(16, 2),
        [System.Drawing.Point]::new(12, 8),
        [System.Drawing.Point]::new(14, 24),
        [System.Drawing.Point]::new(18, 24),
        [System.Drawing.Point]::new(20, 8),
        [System.Drawing.Point]::new(16, 2)
    )
    $graphics.FillPolygon($brush, $points)
    
    # Llamas
    $flameBrush = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::Orange)
    $flamePoints = @(
        [System.Drawing.Point]::new(14, 24),
        [System.Drawing.Point]::new(16, 30),
        [System.Drawing.Point]::new(18, 24)
    )
    $graphics.FillPolygon($flameBrush, $flamePoints)
    
    $bitmap.Save($path, [System.Drawing.Imaging.ImageFormat]::Png)
    $graphics.Dispose()
    $bitmap.Dispose()
    $brush.Dispose()
    $flameBrush.Dispose()
    
    Write-Host "Creado: cohete.png"
}

Write-Host "Generando iconos del HUD..."

# Crear iconos principales
Create-HeartIcon
Create-ClockIcon
Create-RocketIcon

# Crear iconos de mundo
Create-IconPNG "icono_mundo1.png" "M1" 32 32 "Green" "White"
Create-IconPNG "icono_mundo2.png" "M2" 32 32 "Blue" "White"
Create-IconPNG "icono_mundo3.png" "M3" 32 32 "Purple" "White"

# Crear iconos de recursos
Create-IconPNG "recurso_empatia.png" "♥" 24 24 "Pink" "White"
Create-IconPNG "recurso_sabiduria.png" "◇" 24 24 "LightBlue" "White"
Create-IconPNG "recurso_valor.png" "★" 24 24 "Yellow" "Black"
Create-IconPNG "recurso_esperanza.png" "✦" 24 24 "LightGreen" "White"
Create-IconPNG "recurso_equilibrio.png" "⚖" 24 24 "Gold" "Black"

Write-Host "Todos los iconos han sido generados exitosamente!"
Write-Host "Archivos creados en: $recursosPath"
