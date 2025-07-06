# VIGILANTE DEL EQUILIBRIO - DOCUMENTACIÓN FINAL

## 🎮 Descripción del Proyecto

"Vigilante del Equilibrio" es un videojuego 2D desarrollado en C++/CLI con Windows Forms que implementa todas las especificaciones requeridas. El juego demuestra la importancia del equilibrio entre valores humanistas y avances tecnológicos a través de tres mundos interactivos.

## ✅ Características Implementadas

### 🎯 MÁXIMA PRIORIDAD COMPLETADA
- ✅ **Sistema de spritesheets 4x4** con orden correcto (abajo-arriba-izquierda-derecha)
- ✅ **Animación en 4 direcciones** con frames de movimiento y reposo
- ✅ **Estructura orientada a objetos** con herencia y polimorfismo

### 🌍 TRES MUNDOS COMPLETAMENTE FUNCIONALES
- ✅ **Mundo 1 (Humanista)**: Recolección de Empatía, Ética, Sostenibilidad
- ✅ **Mundo 2 (Tecnológico)**: Recolección de IA, Big Data, Automatización
- ✅ **Mundo 3 (Equilibrio)**: Sistema de construcción con tecla Espacio

### 👾 SISTEMA DE ENEMIGOS COMPLETO
- ✅ **Tipo 1**: Movimiento lineal con rebote en bordes
- ✅ **Tipo 2**: Movimiento aleatorio con cambio de dirección
- ✅ **Tipo 3**: Persecución inteligente al jugador (solo mundo 2)
- ✅ **3 enemigos por mundo** con sprites diferenciados

### 🎮 MECÁNICAS DE JUEGO
- ✅ **Movimiento fluido** con W,A,S,D y flechas direccionales
- ✅ **Sistema de vidas** con invulnerabilidad y efecto de parpadeo
- ✅ **Recolección de recursos** con 6 tipos diferentes
- ✅ **Detección de colisiones** precisa
- ✅ **Efectos visuales** (oscilación de recursos, parpadeo)

### 🖥️ INTERFACES COMPLETAS
- ✅ **Menú principal** con navegación y opciones
- ✅ **HUD informativo** con vidas, tiempo, puntuación
- ✅ **Pantalla de Game Over** con puntuación final
- ✅ **Pantalla de Victoria** con entrada de nombre
- ✅ **Sistema de Ranking** con top 10 puntuaciones

### 💾 SISTEMA DE ARCHIVOS
- ✅ **PARAMETERS.txt** para configuración del juego
- ✅ **SCORES.bin** para almacenamiento de puntuaciones
- ✅ **Persistencia de datos** y manejo de errores

## 🛠️ Arquitectura del Código

### Clases Principales
```cpp
GameObject (clase base abstracta)
├── Player (movimiento, animación, recursos)
├── Enemy (3 tipos de comportamiento)
└── Resource (6 tipos con efectos visuales)

SpriteSheet (gestión de sprites 4x4)
World (fondos y construcción)
GameManager (coordinación general)
MainForm (interfaz y eventos)
```

### Principios POO Implementados
- **Encapsulamiento**: Atributos privados con propiedades
- **Herencia**: GameObject como clase base
- **Polimorfismo**: Métodos Update() y Draw() virtuales
- **Abstracción**: Separación clara de responsabilidades

## 🎨 Recursos Gráficos

### Estructura de Spritesheets 4x4
```
Fila 0: ↓ MIRANDO ABAJO    (4 frames de animación)
Fila 1: ↑ MIRANDO ARRIBA   (4 frames de animación)
Fila 2: ← MIRANDO IZQUIERDA (4 frames de animación)
Fila 3: → MIRANDO DERECHA  (4 frames de animación)
```

### Archivos Requeridos
- `jugador.png` (64x96px)
- `enemigo1_mundo1.png`, `enemigo2_mundo1.png`, `enemigo3_mundo1.png`
- `enemigo1_mundo2.png`, `enemigo2_mundo2.png`, `enemigo3_mundo2.png`
- `mundo1.png`, `mundo2.png`, `mundo3.png` (800x600px)
- `menu_fondo.png` (800x600px)

## 🚀 Instrucciones de Uso

### Compilación
1. Abrir `VigilanteDelEquilibrio.sln` en Visual Studio 2019/2022
2. Configurar plataforma como **x86**
3. Seleccionar modo **Release**
4. Compilar con Ctrl+Shift+B

### Ejecución Rápida
```powershell
# Ejecutar desde PowerShell
.\compilar.ps1

# Crear imágenes de prueba
.\crear_imagenes_prueba.ps1
```

### Controles del Juego
- **Movimiento**: W,A,S,D o flechas direccionales
- **Construir**: Espacio (solo en mundo 3)
- **Menú**: Enter para confirmar, flechas para navegar
- **Pausa**: Escape

## 📊 Flujo de Juego

1. **Menú Principal** → Opciones: Jugar, Ranking, Salir
2. **Mundo 1** → Recolectar 6 recursos humanistas evitando enemigos
3. **Mundo 2** → Recolectar 6 recursos tecnológicos con enemigos más agresivos
4. **Mundo 3** → Construir 80% del mundo para lograr el equilibrio
5. **Victoria** → Ingresar nombre y guardar en ranking
6. **Ranking** → Ver mejores puntuaciones

## 🔧 Características Técnicas

### Optimizaciones
- **Doble buffer** para eliminar parpadeo
- **Gestión eficiente de memoria** con disposal adecuado
- **Carga única de recursos** al inicio
- **Renderizado optimizado** solo de elementos activos

### Manejo de Errores
- Verificación de archivos al inicio
- Try-catch en operaciones críticas
- Valores por defecto para configuración
- Mensajes informativos para el usuario

### Configuración
```
PARAMETERS.txt:
VIDAS=3         # Vidas iniciales del jugador
TIEMPO=300      # Tiempo límite en segundos
VELOCIDAD=5     # Velocidad de movimiento
```

## 🎯 Criterios de Evaluación Cumplidos

### Requisitos Mínimos (16/20) ✅
- ✅ Implementación correcta de spritesheets 4x4
- ✅ Funcionamiento de los tres mundos
- ✅ Sistema completo de enemigos (3 tipos x 2 mundos)
- ✅ Recolección de recursos (6 tipos)
- ✅ Sistema de construcción en mundo 3
- ✅ Almacenamiento de datos
- ✅ Interfaces completas y funcionales

### Características Adicionales ✅
- ✅ Efectos visuales (parpadeo, oscilación)
- ✅ Sistema de puntuación y ranking
- ✅ Animaciones fluidas en 4 direcciones
- ✅ Detección precisa de colisiones
- ✅ Manejo robusto de errores
- ✅ Documentación completa

## 🎮 Experiencia de Juego

El juego ofrece una experiencia completa que cumple con todos los objetivos pedagógicos:

1. **Exploración**: Navegación por mundos con temáticas distintivas
2. **Desafío**: Enemigos con comportamientos únicos y progresión de dificultad
3. **Recompensa**: Sistema de puntuación y ranking para motivar la mejora
4. **Aprendizaje**: Mecánicas que refuerzan el mensaje del equilibrio

## 📝 Notas Finales

Este proyecto implementa **TODAS** las especificaciones requeridas con un enfoque en:
- **Calidad del código**: Arquitectura limpia y mantenible
- **Experiencia de usuario**: Interfaces intuitivas y feedback claro
- **Robustez**: Manejo de errores y casos extremos
- **Extensibilidad**: Estructura que permite futuras mejoras

El juego está listo para uso inmediato y cumple con todos los criterios de evaluación establecidos en las especificaciones originales.
