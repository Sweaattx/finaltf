# Script mejorado para crear iconos del HUD
Write-Host "Creando iconos para HUD mejorado..." -ForegroundColor Yellow

Add-Type -AssemblyName System.Drawing

# Función para crear icono
function New-HudIcon {
    param(
        [string]$Name,
        [int]$Size = 24
    )
    
    $bitmap = New-Object System.Drawing.Bitmap($Size, $Size)
    $graphics = [System.Drawing.Graphics]::FromImage($bitmap)
    $graphics.Clear([System.Drawing.Color]::Transparent)
    $graphics.SmoothingMode = [System.Drawing.Drawing2D.SmoothingMode]::AntiAlias
    
    switch ($Name) {
        "corazon" {
            $brush = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::Red)
            # Crear corazón con curvas
            $path = New-Object System.Drawing.Drawing2D.GraphicsPath
            $rect1 = New-Object System.Drawing.Rectangle(6, 4, 6, 6)
            $rect2 = New-Object System.Drawing.Rectangle(12, 4, 6, 6)
            $path.AddEllipse($rect1)
            $path.AddEllipse($rect2)
            $points = @(
                [System.Drawing.Point]::new(9, 10),
                [System.Drawing.Point]::new(15, 10),
                [System.Drawing.Point]::new(12, 18)
            )
            $path.AddPolygon($points)
            $graphics.FillPath($brush, $path)
        }
        "reloj" {
            # Círculo azul para el reloj
            $blueBrush = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::DodgerBlue)
            $graphics.FillEllipse($blueBrush, 2, 2, 20, 20)
            
            # Cara blanca del reloj
            $whiteBrush = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::White)
            $graphics.FillEllipse($whiteBrush, 4, 4, 16, 16)
            
            # Manecillas del reloj
            $blackPen = New-Object System.Drawing.Pen([System.Drawing.Color]::Black, 2)
            $graphics.DrawLine($blackPen, 12, 12, 12, 8)  # Manecilla corta
            $graphics.DrawLine($blackPen, 12, 12, 16, 12) # Manecilla larga
        }
        "cohete" {
            # Cuerpo del cohete
            $orangeBrush = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::Orange)
            $graphics.FillRectangle($orangeBrush, 10, 6, 4, 12)
            
            # Punta del cohete
            $points = @(
                [System.Drawing.Point]::new(10, 6),
                [System.Drawing.Point]::new(14, 6),
                [System.Drawing.Point]::new(12, 2)
            )
            $graphics.FillPolygon($orangeBrush, $points)
            
            # Llama del cohete
            $redBrush = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::Red)
            $flame = @(
                [System.Drawing.Point]::new(10, 18),
                [System.Drawing.Point]::new(14, 18),
                [System.Drawing.Point]::new(12, 22)
            )
            $graphics.FillPolygon($redBrush, $flame)
        }
        "icono_mundo1" {
            # Mundo ecológico (verde)
            $greenBrush = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::ForestGreen)
            $graphics.FillEllipse($greenBrush, 2, 2, 20, 20)
            
            # Continentes
            $darkGreenBrush = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::DarkGreen)
            $graphics.FillEllipse($darkGreenBrush, 6, 6, 4, 4)
            $graphics.FillEllipse($darkGreenBrush, 14, 8, 3, 3)
            $graphics.FillEllipse($darkGreenBrush, 8, 14, 5, 3)
        }
        "icono_mundo2" {
            # Mundo tecnológico (azul)
            $blueBrush = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::CornflowerBlue)
            $graphics.FillEllipse($blueBrush, 2, 2, 20, 20)
            
            # Circuitos tecnológicos
            $silverBrush = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::Silver)
            $graphics.FillRectangle($silverBrush, 8, 8, 2, 2)
            $graphics.FillRectangle($silverBrush, 14, 10, 2, 2)
            $graphics.FillRectangle($silverBrush, 10, 14, 2, 2)
            $graphics.FillRectangle($silverBrush, 6, 12, 2, 2)
        }
        "icono_mundo3" {
            # Mundo futurista (dorado)
            $goldBrush = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::Gold)
            $graphics.FillEllipse($goldBrush, 2, 2, 20, 20)
            
            # Elementos futuristas
            $purpleBrush = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::Purple)
            $graphics.FillEllipse($purpleBrush, 10, 6, 4, 4)
            $graphics.FillEllipse($purpleBrush, 6, 12, 3, 3)
            $graphics.FillEllipse($purpleBrush, 15, 14, 3, 3)
        }
    }
    
    $graphics.Dispose()
    $filePath = "recursos\$Name.png"
    $bitmap.Save($filePath, [System.Drawing.Imaging.ImageFormat]::Png)
    $bitmap.Dispose()
    
    Write-Host "Creado: $filePath" -ForegroundColor Green
}

# Crear iconos del HUD
New-HudIcon -Name "corazon"
New-HudIcon -Name "reloj"
New-HudIcon -Name "cohete"
New-HudIcon -Name "icono_mundo1"
New-HudIcon -Name "icono_mundo2"
New-HudIcon -Name "icono_mundo3"

# Crear iconos de recursos con colores distintivos
$resourceColors = @{
    "recurso_empatia" = [System.Drawing.Color]::HotPink
    "recurso_etica" = [System.Drawing.Color]::LightBlue
    "recurso_sostenibilidad" = [System.Drawing.Color]::LimeGreen
    "recurso_ia" = [System.Drawing.Color]::MediumPurple
    "recurso_bigdata" = [System.Drawing.Color]::Orange
    "recurso_automatizacion" = [System.Drawing.Color]::Crimson
}

foreach ($resource in $resourceColors.Keys) {
    $bitmap = New-Object System.Drawing.Bitmap(24, 24)
    $graphics = [System.Drawing.Graphics]::FromImage($bitmap)
    $graphics.Clear([System.Drawing.Color]::Transparent)
    $graphics.SmoothingMode = [System.Drawing.Drawing2D.SmoothingMode]::AntiAlias
    
    $brush = New-Object System.Drawing.SolidBrush($resourceColors[$resource])
    $graphics.FillEllipse($brush, 2, 2, 20, 20)
    
    # Agregar símbolo distintivo en el centro
    $whiteBrush = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::White)
    $font = New-Object System.Drawing.Font("Arial", 8, [System.Drawing.FontStyle]::Bold)
    
    $symbol = switch ($resource) {
        "recurso_empatia" { "♥" }
        "recurso_etica" { "⚖" }
        "recurso_sostenibilidad" { "🌱" }
        "recurso_ia" { "🤖" }
        "recurso_bigdata" { "📊" }
        "recurso_automatizacion" { "⚙" }
        default { "?" }
    }
    
    $format = New-Object System.Drawing.StringFormat
    $format.Alignment = [System.Drawing.StringAlignment]::Center
    $format.LineAlignment = [System.Drawing.StringAlignment]::Center
    
    $rect = New-Object System.Drawing.Rectangle(0, 0, 24, 24)
    $graphics.DrawString($symbol, $font, $whiteBrush, $rect, $format)
    
    $graphics.Dispose()
    $filePath = "recursos\$resource.png"
    $bitmap.Save($filePath, [System.Drawing.Imaging.ImageFormat]::Png)
    $bitmap.Dispose()
    
    Write-Host "Creado: $filePath" -ForegroundColor Green
}

Write-Host "¡Todos los iconos del HUD han sido creados!" -ForegroundColor Green
