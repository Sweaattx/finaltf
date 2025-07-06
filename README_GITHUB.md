# Vigilante del Equilibrio

Un juego 2D desarrollado en C++/CLI con Windows Forms como parte de un proyecto universitario.

## Descripción

"Vigilante del Equilibrio" es un juego de aventura y recolección donde el jugador debe navegar a través de tres mundos diferentes, recolectando recursos mientras evita enemigos. El juego implementa una progresión estricta entre mundos y cuenta con un sistema de animaciones y colisiones.

## Características Principales

- **3 Mundos Únicos**: Cada mundo tiene su temática, enemigos y recursos específicos
- **Progresión Estricta**: Debes recolectar TODOS los recursos de un mundo antes de pasar al siguiente
- **Sistema de Animaciones**: Sprites animados con detección automática de tamaño
- **Sistema de Colisiones**: Detección precisa de colisiones con enemigos y recursos
- **Configuración Personalizable**: Parámetros del juego modificables desde archivo
- **Herramientas de Debug**: F12 para información de debug, F11 para desactivar parpadeo

## Requisitos del Sistema

- **Sistema Operativo**: Windows 10/11
- **Framework**: .NET Framework 4.7.2 o superior
- **IDE**: Visual Studio 2019/2022 con soporte para C++/CLI
- **Resolución**: 800x600 píxeles mínimo

## Instalación y Compilación

### 1. Clonar el Repositorio
```bash
git clone https://github.com/Sweaattx/finaltf.git
cd finaltf
```

### 2. Compilar el Proyecto

#### Opción A: Usando Visual Studio
1. Abrir `VigilanteDelEquilibrio.sln` en Visual Studio
2. Seleccionar configuración "Release" o "Debug"
3. Compilar el proyecto (Ctrl+Shift+B)

#### Opción B: Usando Script de PowerShell
```powershell
.\compilar_correcto.ps1
```

### 3. Ejecutar el Juego
```powershell
cd Release
.\VigilanteDelEquilibrio.exe
```

## Estructura del Proyecto

```
VigilanteDelEquilibrio/
├── GameManager.h          # Lógica principal del juego
├── MainForm.h             # Interfaz gráfica y eventos
├── main.cpp               # Punto de entrada
├── VigilanteDelEquilibrio.vcxproj  # Archivo de proyecto
├── VigilanteDelEquilibrio.sln      # Solución de Visual Studio
├── FILES/
│   └── PARAMETERS.txt     # Configuración del juego
├── recursos/              # Recursos gráficos
│   ├── jugador.png        # Spritesheet del jugador (4x4)
│   ├── enemigo*.png       # Sprites de enemigos
│   └── mundo*.png         # Fondos de los mundos
└── compilar_correcto.ps1  # Script de compilación
```

## Cómo Jugar

### Controles
- **Flechas/WASD**: Movimiento del jugador
- **ESC**: Pausar/Volver al menú
- **F12**: Mostrar información de debug
- **F11**: Activar/desactivar parpadeo de invulnerabilidad

### Objetivo
1. **Mundo 1**: Recolecta las 12 esferas rojas
2. **Mundo 2**: Recolecta las 12 esferas verdes  
3. **Mundo 3**: Recolecta las 12 esferas azules

### Mecánicas
- **Progresión Estricta**: Debes recolectar TODOS los recursos de un mundo antes de avanzar
- **Vidas**: Comienzas con 3 vidas, pierdes una al tocar enemigos
- **Tiempo**: Cada mundo tiene un tiempo límite
- **Enemigos**: Evita los enemigos que se mueven por el mapa

## Configuración

Edita `FILES/PARAMETERS.txt` para modificar:
- `VIDAS=3`: Número de vidas iniciales
- `TIEMPO=300`: Tiempo límite por mundo (segundos)
- `VELOCIDAD=5`: Velocidad de movimiento del jugador

## Características Técnicas

### Arquitectura
- **Patrón OOP**: Clases separadas para Player, Enemy, Resource, GameManager
- **Manejo de Estados**: Menú, juego, pausa, victoria, derrota
- **Detección Automática**: Tamaño de sprites detectado automáticamente
- **Gestión de Memoria**: Uso correcto de managed objects de .NET

### Optimizaciones
- **Animaciones Inteligentes**: Solo se animan cuando hay movimiento
- **Colisiones Precisas**: Detección basada en rectángulos de sprites
- **Carga Dinámica**: Recursos cargados según el mundo actual

## Desarrollo

### Compilación en Modo Debug
```powershell
# Compilar en modo Debug para desarrollo
MSBuild VigilanteDelEquilibrio.vcxproj /p:Configuration=Debug
```

### Herramientas de Debug
- **F12**: Muestra posición, velocidad, estado del jugador
- **F11**: Desactiva el parpadeo de invulnerabilidad
- **Información Visual**: Rectángulos de colisión y datos de sprites

## Contribución

Este es un proyecto universitario, pero si deseas contribuir:
1. Fork el repositorio
2. Crea una rama para tu función (`git checkout -b feature/nueva-funcion`)
3. Commit tus cambios (`git commit -am 'Agregar nueva función'`)
4. Push a la rama (`git push origin feature/nueva-funcion`)
5. Crear un Pull Request

## Licencia

Este proyecto fue desarrollado como parte de un curso universitario. Código disponible para fines educativos.

## Créditos

- **Desarrollo**: Proyecto universitario
- **Tecnologías**: C++/CLI, Windows Forms, .NET Framework
- **Herramientas**: Visual Studio, Git, PowerShell

## Changelog

### v1.0.0 (2025-07-06)
- Implementación completa del juego
- Sistema de progresión estricta entre mundos
- Corrección de bugs de animación y colisiones
- Eliminación de tildes para compatibilidad con IDE
- Sistema de debug implementado
- Documentación completa

---

**Estado**: ✅ Proyecto Completado y Verificado
**Última Actualización**: 6 de julio de 2025
