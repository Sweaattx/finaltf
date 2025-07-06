# Vigilante del Equilibrio - Instrucciones de Compilación

## Requisitos del Sistema
- Windows 7 o superior
- Visual Studio 2019 o 2022 (con C++/CLI support)
- .NET Framework 4.7.2 o superior

## Configuración del Proyecto

### 1. Abrir Visual Studio
- Abrir el archivo `VigilanteDelEquilibrio.sln` en Visual Studio

### 2. Configurar la Plataforma
- En la barra de herramientas, asegurarse de que la plataforma esté configurada como **x86**
- Seleccionar **Release** como configuración para la versión final

### 3. Verificar Referencias
El proyecto debe incluir las siguientes referencias:
- System
- System.Data
- System.Drawing
- System.Windows.Forms
- System.Xml
- Microsoft.VisualBasic

### 4. Estructura de Archivos
```
VigilanteDelEquilibrio/
├── main.cpp (Punto de entrada)
├── MainForm.h (Formulario principal)
├── GameManager.h (Lógica del juego)
├── VigilanteDelEquilibrio.vcxproj (Archivo de proyecto)
├── VigilanteDelEquilibrio.sln (Solución)
├── recursos/ (Directorio de recursos gráficos)
│   └── [archivos .png requeridos]
└── FILES/ (Directorio de datos)
    └── PARAMETERS.txt (Parámetros del juego)
```

## Compilación

### Modo Debug
1. Seleccionar **Debug** en la configuración
2. Presionar F5 o Build → Build Solution

### Modo Release
1. Seleccionar **Release** en la configuración
2. Build → Build Solution
3. El ejecutable se generará en `Release/`

## Despliegue
1. Copiar el ejecutable generado
2. Copiar la carpeta `recursos/` al mismo directorio que el ejecutable
3. Copiar la carpeta `FILES/` al mismo directorio que el ejecutable
4. Asegurarse de que los archivos gráficos estén en su lugar

## Resolución de Problemas

### Error: No se encuentra el directorio recursos
- Verificar que la carpeta `recursos/` esté en el mismo directorio que el ejecutable
- Verificar que todos los archivos PNG requeridos estén presentes

### Error: No se puede escribir en FILES
- Verificar permisos de escritura en el directorio
- Ejecutar como administrador si es necesario

### Error de compilación: CLR Support
- Ir a Project Properties → Configuration Properties → General
- Asegurarse de que "Common Language Runtime Support" esté en "Common Language Runtime Support (/clr)"

### Error: No se encuentra .NET Framework
- Instalar .NET Framework 4.7.2 o superior
- Verificar que el TargetFrameworkVersion sea correcto

## Controles del Juego
- **Movimiento**: W, A, S, D o flechas direccionales
- **Acción/Construir**: Espacio (solo en mundo 3)
- **Confirmación**: Enter
- **Pausa/Menú**: Escape

## Características Implementadas
✅ Sistema de spritesheets 4x4 con animación en 4 direcciones
✅ Tres mundos diferentes con mecánicas específicas
✅ Sistema de enemigos con 3 tipos de comportamiento
✅ Recolección de 6 tipos de recursos
✅ Sistema de construcción en mundo 3
✅ Almacenamiento de parámetros y puntuaciones
✅ Interfaces de usuario completas
✅ Sistema de ranking
✅ Manejo de errores y verificaciones

## Notas Adicionales
- El juego está optimizado para 800x600 píxeles
- Utiliza doble buffer para evitar parpadeo
- Gestiona memoria de forma eficiente
- Incluye efectos visuales según especificaciones
