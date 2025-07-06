# Script para crear iconos del HUD y sistema de inventario
param(
    [string]$OutputPath = "recursos"
)

Write-Host "Creando iconos para HUD mejorado y sistema de inventario..." -ForegroundColor Yellow

# Crear directorio si no existe
if (!(Test-Path $OutputPath)) {
    New-Item -ItemType Directory -Path $OutputPath
}

Add-Type -AssemblyName System.Drawing

# Función para crear icono simple
function Create-Icon {
    param(
        [string]$Name,
        [int]$Width = 32,
        [int]$Height = 32,
        [System.Drawing.Color]$BackColor = [System.Drawing.Color]::Transparent,
        [System.Drawing.Color]$MainColor = [System.Drawing.Color]::Red
    )
    
    $bitmap = New-Object System.Drawing.Bitmap($Width, $Height)
    $graphics = [System.Drawing.Graphics]::FromImage($bitmap)
    $graphics.Clear($BackColor)
    
    switch ($Name) {
        "corazon" {
            # Crear corazón rojo
            $brush = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::Red)
            $graphics.FillEllipse($brush, 8, 6, 8, 8)
            $graphics.FillEllipse($brush, 16, 6, 8, 8)
            $points = @(
                [System.Drawing.Point]::new(12, 14),
                [System.Drawing.Point]::new(20, 14),
                [System.Drawing.Point]::new(16, 24)
            )
            $graphics.FillPolygon($brush, $points)
        }
        "reloj" {
            # Crear reloj
            $brush = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::Blue)
            $graphics.FillEllipse($brush, 4, 4, 24, 24)
            $whiteBrush = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::White)
            $graphics.FillEllipse($whiteBrush, 6, 6, 20, 20)
            $pen = New-Object System.Drawing.Pen([System.Drawing.Color]::Black, 2)
            $graphics.DrawLine($pen, 16, 16, 16, 10)
            $graphics.DrawLine($pen, 16, 16, 20, 16)
        }
        "cohete" {
            # Crear cohete
            $brush = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::Orange)
            $graphics.FillRectangle($brush, 12, 8, 8, 16)
            $points = @(
                [System.Drawing.Point]::new(12, 8),
                [System.Drawing.Point]::new(20, 8),
                [System.Drawing.Point]::new(16, 4)
            )
            $graphics.FillPolygon($brush, $points)
            $redBrush = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::Red)
            $graphics.FillRectangle($redBrush, 14, 24, 4, 4)
        }
        "mundo1" {
            # Crear icono mundo 1 (verde)
            $brush = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::Green)
            $graphics.FillEllipse($brush, 4, 4, 24, 24)
            $darkBrush = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::DarkGreen)
            $graphics.FillEllipse($darkBrush, 8, 8, 6, 6)
            $graphics.FillEllipse($darkBrush, 18, 12, 4, 4)
        }
        "mundo2" {
            # Crear icono mundo 2 (azul tecnológico)
            $brush = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::CornflowerBlue)
            $graphics.FillEllipse($brush, 4, 4, 24, 24)
            $silverBrush = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::Silver)
            $graphics.FillRectangle($silverBrush, 10, 10, 4, 4)
            $graphics.FillRectangle($silverBrush, 18, 14, 4, 4)
            $graphics.FillRectangle($silverBrush, 14, 18, 4, 4)
        }
        "mundo3" {
            # Crear icono mundo 3 (dorado futurista)
            $brush = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::Gold)
            $graphics.FillEllipse($brush, 4, 4, 24, 24)
            $purpleBrush = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::Purple)
            $graphics.FillEllipse($purpleBrush, 12, 8, 8, 8)
            $graphics.FillEllipse($purpleBrush, 8, 16, 4, 4)
            $graphics.FillEllipse($purpleBrush, 20, 20, 4, 4)
        }
        default {
            # Crear icono genérico
            $brush = New-Object System.Drawing.SolidBrush($MainColor)
            $graphics.FillEllipse($brush, 4, 4, 24, 24)
        }
    }
    
    $graphics.Dispose()
    $filePath = Join-Path $OutputPath "$Name.png"
    $bitmap.Save($filePath, [System.Drawing.Imaging.ImageFormat]::Png)
    $bitmap.Dispose()
    
    Write-Host "Creado: $filePath" -ForegroundColor Green
}

# Crear iconos del HUD
Create-Icon -Name "corazon"
Create-Icon -Name "reloj" 
Create-Icon -Name "cohete"
Create-Icon -Name "mundo1"
Create-Icon -Name "mundo2"
Create-Icon -Name "mundo3"

# Crear iconos de recursos
Create-Icon -Name "recurso_empatia" -MainColor ([System.Drawing.Color]::Pink)
Create-Icon -Name "recurso_etica" -MainColor ([System.Drawing.Color]::LightBlue)
Create-Icon -Name "recurso_sostenibilidad" -MainColor ([System.Drawing.Color]::LightGreen)
Create-Icon -Name "recurso_ia" -MainColor ([System.Drawing.Color]::Purple)
Create-Icon -Name "recurso_bigdata" -MainColor ([System.Drawing.Color]::Orange)
Create-Icon -Name "recurso_automatizacion" -MainColor ([System.Drawing.Color]::Red)

Write-Host "Todos los iconos han sido creados exitosamente!" -ForegroundColor Green
