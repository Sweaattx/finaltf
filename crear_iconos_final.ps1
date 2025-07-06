# Script simplificado para crear iconos del HUD
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
            # Crear corazón simple
            $graphics.FillEllipse($brush, 4, 6, 8, 8)
            $graphics.FillEllipse($brush, 12, 6, 8, 8)
            $points = @(
                [System.Drawing.Point]::new(8, 14),
                [System.Drawing.Point]::new(16, 14),
                [System.Drawing.Point]::new(12, 20)
            )
            $graphics.FillPolygon($brush, $points)
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
            $graphics.DrawLine($blackPen, 12, 12, 12, 8)
            $graphics.DrawLine($blackPen, 12, 12, 16, 12)
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

# Crear iconos de recursos con colores distintivos y letras
$resourceData = @{
    "recurso_empatia" = @{ Color = [System.Drawing.Color]::HotPink; Letter = "E" }
    "recurso_etica" = @{ Color = [System.Drawing.Color]::LightBlue; Letter = "T" }
    "recurso_sostenibilidad" = @{ Color = [System.Drawing.Color]::LimeGreen; Letter = "S" }
    "recurso_ia" = @{ Color = [System.Drawing.Color]::MediumPurple; Letter = "I" }
    "recurso_bigdata" = @{ Color = [System.Drawing.Color]::Orange; Letter = "B" }
    "recurso_automatizacion" = @{ Color = [System.Drawing.Color]::Crimson; Letter = "A" }
}

foreach ($resource in $resourceData.Keys) {
    $bitmap = New-Object System.Drawing.Bitmap(24, 24)
    $graphics = [System.Drawing.Graphics]::FromImage($bitmap)
    $graphics.Clear([System.Drawing.Color]::Transparent)
    $graphics.SmoothingMode = [System.Drawing.Drawing2D.SmoothingMode]::AntiAlias
    
    $brush = New-Object System.Drawing.SolidBrush($resourceData[$resource].Color)
    $graphics.FillEllipse($brush, 2, 2, 20, 20)
    
    # Agregar letra distintiva en el centro
    $whiteBrush = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::White)
    $font = New-Object System.Drawing.Font("Arial", 10, [System.Drawing.FontStyle]::Bold)
    
    $format = New-Object System.Drawing.StringFormat
    $format.Alignment = [System.Drawing.StringAlignment]::Center
    $format.LineAlignment = [System.Drawing.StringAlignment]::Center
    
    $rect = New-Object System.Drawing.Rectangle(0, 0, 24, 24)
    $graphics.DrawString($resourceData[$resource].Letter, $font, $whiteBrush, $rect, $format)
    
    $graphics.Dispose()
    $filePath = "recursos\$resource.png"
    $bitmap.Save($filePath, [System.Drawing.Imaging.ImageFormat]::Png)
    $bitmap.Dispose()
    
    Write-Host "Creado: $filePath" -ForegroundColor Green
}

Write-Host "Todos los iconos del HUD han sido creados exitosamente!" -ForegroundColor Green
