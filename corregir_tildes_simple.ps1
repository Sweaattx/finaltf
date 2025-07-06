# Script para corregir tildes y caracteres especiales
Write-Host "Corrigiendo tildes y caracteres especiales..." -ForegroundColor Yellow

# Obtener todos los archivos .h y .cpp
$files = Get-ChildItem -Path "." -Filter "*.h" -Recurse
$files += Get-ChildItem -Path "." -Filter "*.cpp" -Recurse

foreach ($file in $files) {
    Write-Host "Procesando: $($file.Name)" -ForegroundColor Green
    
    # Leer el contenido del archivo
    $content = Get-Content $file.FullName -Raw -Encoding UTF8
    
    # Reemplazar tildes
    $content = $content -replace "á", "a"
    $content = $content -replace "é", "e"
    $content = $content -replace "í", "i"
    $content = $content -replace "ó", "o"
    $content = $content -replace "ú", "u"
    $content = $content -replace "ñ", "n"
    $content = $content -replace "Á", "A"
    $content = $content -replace "É", "E"
    $content = $content -replace "Í", "I"
    $content = $content -replace "Ó", "O"
    $content = $content -replace "Ú", "U"
    $content = $content -replace "Ñ", "N"
    
    # Reemplazar palabras comunes con tildes
    $content = $content -replace "información", "informacion"
    $content = $content -replace "Información", "Informacion"
    $content = $content -replace "animación", "animacion"
    $content = $content -replace "verificación", "verificacion"
    $content = $content -replace "tamaño", "tamano"
    $content = $content -replace "dirección", "direccion"
    $content = $content -replace "configuración", "configuracion"
    $content = $content -replace "lógica", "logica"
    $content = $content -replace "análisis", "analisis"
    $content = $content -replace "diálogo", "dialogo"
    $content = $content -replace "límite", "limite"
    $content = $content -replace "límites", "limites"
    $content = $content -replace "según", "segun"
    $content = $content -replace "posición", "posicion"
    $content = $content -replace "período", "periodo"
    $content = $content -replace "sólido", "solido"
    $content = $content -replace "píxel", "pixel"
    $content = $content -replace "píxeles", "pixeles"
    $content = $content -replace "oscilación", "oscilacion"
    $content = $content -replace "opción", "opcion"
    $content = $content -replace "menú", "menu"
    $content = $content -replace "está", "esta"
    $content = $content -replace "así", "asi"
    $content = $content -replace "ética", "etica"
    $content = $content -replace "empatía", "empatia"
    $content = $content -replace "automática", "automatica"
    $content = $content -replace "automáticamente", "automaticamente"
    $content = $content -replace "basándose", "basandose"
    $content = $content -replace "estático", "estatico"
    $content = $content -replace "crítica", "critica"
    $content = $content -replace "más", "mas"
    $content = $content -replace "después", "despues"
    $content = $content -replace "parámetros", "parametros"
    $content = $content -replace "método", "metodo"
    $content = $content -replace "métodos", "metodos"
    $content = $content -replace "detección", "deteccion"
    
    # Escribir el contenido corregido
    Set-Content -Path $file.FullName -Value $content -Encoding UTF8
}

Write-Host "Correccion completada!" -ForegroundColor Green
