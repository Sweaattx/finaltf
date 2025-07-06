# Script para corregir tildes y caracteres especiales
Write-Host "Corrigiendo tildes y caracteres especiales..." -ForegroundColor Yellow

# Obtener todos los archivos .h y .cpp
$files = Get-ChildItem -Path "." -Filter "*.h" -Recurse
$files += Get-ChildItem -Path "." -Filter "*.cpp" -Recurse

foreach ($file in $files) {
    Write-Host "Procesando: $($file.Name)" -ForegroundColor Green
    
    # Leer el contenido del archivo
    $content = Get-Content $file.FullName -Raw -Encoding UTF8
    
    # Reemplazar tildes y caracteres especiales
    $content = $content -replace "á", "a"
    $content = $content -replace "é", "e"
    $content = $content -replace "í", "i"
    $content = $content -replace "ó", "o"
    $content = $content -replace "ú", "u"
    $content = $content -replace "ü", "u"
    $content = $content -replace "ñ", "n"
    $content = $content -replace "Á", "A"
    $content = $content -replace "É", "E"
    $content = $content -replace "Í", "I"
    $content = $content -replace "Ó", "O"
    $content = $content -replace "Ú", "U"
    $content = $content -replace "Ü", "U"
    $content = $content -replace "Ñ", "N"
    
    # Reemplazar otros caracteres problemáticos
    $content = $content -replace "CORRECCIÓN", "CORRECCION"
    $content = $content -replace "FUNCIÓN", "FUNCION"
    $content = $content -replace "VERSIÓN", "VERSION"
    $content = $content -replace "información", "informacion"
    $content = $content -replace "Información", "Informacion"
    $content = $content -replace "animación", "animacion"
    $content = $content -replace "Animación", "Animacion"
    $content = $content -replace "verificación", "verificacion"
    $content = $content -replace "Verificación", "Verificacion"
    $content = $content -replace "tamaño", "tamano"
    $content = $content -replace "Tamaño", "Tamano"
    $content = $content -replace "dirección", "direccion"
    $content = $content -replace "Dirección", "Direccion"
    $content = $content -replace "configuración", "configuracion"
    $content = $content -replace "Configuración", "Configuracion"
    $content = $content -replace "lógica", "logica"
    $content = $content -replace "Lógica", "Logica"
    $content = $content -replace "análisis", "analisis"
    $content = $content -replace "Análisis", "Analisis"
    $content = $content -replace "diálogo", "dialogo"
    $content = $content -replace "Diálogo", "Dialogo"
    $content = $content -replace "límite", "limite"
    $content = $content -replace "Límite", "Limite"
    $content = $content -replace "límites", "limites"
    $content = $content -replace "Límites", "Limites"
    $content = $content -replace "según", "segun"
    $content = $content -replace "Según", "Segun"
    $content = $content -replace "posición", "posicion"
    $content = $content -replace "Posición", "Posicion"
    $content = $content -replace "período", "periodo"
    $content = $content -replace "Período", "Periodo"
    $content = $content -replace "sólido", "solido"
    $content = $content -replace "Sólido", "Solido"
    $content = $content -replace "píxel", "pixel"
    $content = $content -replace "Píxel", "Pixel"
    $content = $content -replace "píxeles", "pixeles"
    $content = $content -replace "Píxeles", "Pixeles"
    $content = $content -replace "oscilación", "oscilacion"
    $content = $content -replace "Oscilación", "Oscilacion"
    $content = $content -replace "opción", "opcion"
    $content = $content -replace "Opción", "Opcion"
    $content = $content -replace "menú", "menu"
    $content = $content -replace "Menú", "Menu"
    $content = $content -replace "está", "esta"
    $content = $content -replace "Está", "Esta"
    $content = $content -replace "así", "asi"
    $content = $content -replace "Así", "Asi"
    $content = $content -replace "ética", "etica"
    $content = $content -replace "Ética", "Etica"
    $content = $content -replace "empatía", "empatia"
    $content = $content -replace "Empatía", "Empatia"
    $content = $content -replace "automática", "automatica"
    $content = $content -replace "Automática", "Automatica"
    $content = $content -replace "automáticamente", "automaticamente"
    $content = $content -replace "Automáticamente", "Automaticamente"
    $content = $content -replace "basándose", "basandose"
    $content = $content -replace "Basándose", "Basandose"
    $content = $content -replace "estático", "estatico"
    $content = $content -replace "Estático", "Estatico"
    $content = $content -replace "crítica", "critica"
    $content = $content -replace "Crítica", "Critica"
    $content = $content -replace "más", "mas"
    $content = $content -replace "Más", "Mas"
    $content = $content -replace "después", "despues"
    $content = $content -replace "Después", "Despues"
    $content = $content -replace "parámetros", "parametros"
    $content = $content -replace "Parámetros", "Parametros"
    $content = $content -replace "método", "metodo"
    $content = $content -replace "Método", "Metodo"
    $content = $content -replace "métodos", "metodos"
    $content = $content -replace "Métodos", "Metodos"
    $content = $content -replace "detección", "deteccion"
    $content = $content -replace "Detección", "Deteccion"
    
    # Escribir el contenido corregido
    Set-Content -Path $file.FullName -Value $content -Encoding UTF8
}

Write-Host "Corrección completada!" -ForegroundColor Green
