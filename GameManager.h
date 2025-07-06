#pragma once
#include "stdafx.h"

// Enumeraciones para el juego
public enum class GameState {
    Menu,
    World1,
    World2,
    World3,
    GameOver,
    Victory,
    Ranking
};

// Constantes del HUD
#define HUD_HEIGHT 200
#define GAME_AREA_TOP HUD_HEIGHT
#define GAME_AREA_HEIGHT (600 - HUD_HEIGHT)

public enum class Direction {
    Down = 0,
    Left = 1,
    Right = 2,
    Up = 3
};

public enum class ResourceType {
    Empatia,
    Etica,
    Sostenibilidad,
    IA,
    BigData,
    Automatizacion
};

public enum class EnemyType {
    Linear,
    Random,
    Chase
};

// Estructura para puntuaciones
public ref struct ScoreEntry {
    String^ nombre;
    int puntuacion;
    
    ScoreEntry(String^ n, int p) {
        nombre = n;
        puntuacion = p;
    }
};

// Clase base GameObject
public ref class GameObject abstract {
protected:
    float x, y;
    float width, height;
    bool active;
    
public:
    GameObject(float posX, float posY, float w, float h) {
        x = posX;
        y = posY;
        width = w;
        height = h;
        active = true;
    }
    
    virtual void Update() abstract;
    virtual void Draw(Graphics^ g) abstract;
    
    bool CheckCollision(GameObject^ other) {
        if (!active || !other->active) return false;
        
        return (x < other->x + other->width &&
                x + width > other->x &&
                y < other->y + other->height &&
                y + height > other->y);
    }
    
    property float X { float get() { return x; } void set(float value) { x = value; } }
    property float Y { float get() { return y; } void set(float value) { y = value; } }
    property float Width { float get() { return width; } }
    property float Height { float get() { return height; } }
    property bool Active { bool get() { return active; } void set(bool value) { active = value; } }
};

// Clase para gestionar spritesheets
public ref class SpriteSheet {
private:
    Bitmap^ spriteImage;
    int frameWidth, frameHeight;
    int rows, cols;
    
public:
    SpriteSheet(String^ filename, int fw, int fh, int r, int c) {
        frameWidth = fw;
        frameHeight = fh;
        rows = r;
        cols = c;
        
        try {
            spriteImage = gcnew Bitmap(filename);
            
            // COMENTADO: Verificacion de dimensiones (para evitar dialogos repetitivos)
            /*
            // DEBUG: Verificar dimensiones de la imagen cargada
            int imageWidth = spriteImage->Width;
            int imageHeight = spriteImage->Height;
            int expectedWidth = cols * frameWidth;
            int expectedHeight = rows * frameHeight;
            
            if (imageWidth != expectedWidth || imageHeight != expectedHeight) {
                String^ warningMsg = String::Format(
                    "ADVERTENCIA: Dimensiones de imagen no coinciden\n" +
                    "Archivo: {0}\n" +
                    "Tamano real: {1}x{2}\n" +
                    "Tamano esperado: {3}x{4}\n" +
                    "Frame: {5}x{6}, Grid: {7}x{8}",
                    filename, imageWidth, imageHeight, expectedWidth, expectedHeight,
                    frameWidth, frameHeight, cols, rows);
                MessageBox::Show(warningMsg);
            }
            */
        }
        catch (Exception^ e) {
            MessageBox::Show("Error cargando sprite: " + filename + "\n" + e->Message);
            spriteImage = gcnew Bitmap(fw, fh);
        }
    }
    
    void DrawFrame(Graphics^ g, int row, int col, float x, float y) {
        if (spriteImage == nullptr) return;
        
        System::Drawing::Rectangle sourceRect = System::Drawing::Rectangle(col * frameWidth, row * frameHeight, frameWidth, frameHeight);
        System::Drawing::Rectangle destRect = System::Drawing::Rectangle((int)x, (int)y, frameWidth, frameHeight);
        
        g->DrawImage(spriteImage, destRect, sourceRect, GraphicsUnit::Pixel);
    }
    
    void DrawFrame(Graphics^ g, int row, int col, float x, float y, float scale) {
        if (spriteImage == nullptr) return;
        
        System::Drawing::Rectangle sourceRect = System::Drawing::Rectangle(col * frameWidth, row * frameHeight, frameWidth, frameHeight);
        System::Drawing::Rectangle destRect = System::Drawing::Rectangle((int)x, (int)y, (int)(frameWidth * scale), (int)(frameHeight * scale));
        
        g->DrawImage(spriteImage, destRect, sourceRect, GraphicsUnit::Pixel);
    }
    
    // VERSION MEJORADA: Dibujar frame con tamano personalizado
    void DrawFrameCustomSize(Graphics^ g, int row, int col, float x, float y, int customWidth, int customHeight) {
        if (spriteImage == nullptr) return;
        
        System::Drawing::Rectangle sourceRect = System::Drawing::Rectangle(col * frameWidth, row * frameHeight, frameWidth, frameHeight);
        System::Drawing::Rectangle destRect = System::Drawing::Rectangle((int)x, (int)y, customWidth, customHeight);
        
        g->DrawImage(spriteImage, destRect, sourceRect, GraphicsUnit::Pixel);
    }
    
    // FUNCION DE DEBUG: Dibujar frame con informacion de debug
    void DrawFrameDebug(Graphics^ g, int row, int col, float x, float y, String^ debugText) {
        if (spriteImage == nullptr) return;
        
        System::Drawing::Rectangle sourceRect = System::Drawing::Rectangle(col * frameWidth, row * frameHeight, frameWidth, frameHeight);
        System::Drawing::Rectangle destRect = System::Drawing::Rectangle((int)x, (int)y, frameWidth, frameHeight);
        
        // Dibujar el sprite
        g->DrawImage(spriteImage, destRect, sourceRect, GraphicsUnit::Pixel);
        
        // Dibujar borde del sprite para debug
        Pen^ debugPen = gcnew Pen(Color::Red, 1);
        g->DrawRectangle(debugPen, destRect);
        
        // Mostrar informacion de debug
        Font^ debugFont = gcnew Font("Arial", 8);
        SolidBrush^ debugBrush = gcnew SolidBrush(Color::Yellow);
        String^ info = String::Format("{0}\nSrc: {1},{2},{3}x{4}\nDest: {5},{6},{7}x{8}", 
            debugText, sourceRect.X, sourceRect.Y, sourceRect.Width, sourceRect.Height,
            destRect.X, destRect.Y, destRect.Width, destRect.Height);
        g->DrawString(info, debugFont, debugBrush, x, y - 60);
    }
    
    // FUNCION PARA DETECTAR AUTOMATICAMENTE EL TAMANO DE FRAME
    static void DetectFrameSize(String^ filename, int% detectedFrameWidth, int% detectedFrameHeight) {
        try {
            Bitmap^ testImage = gcnew Bitmap(filename);
            int imageWidth = testImage->Width;
            int imageHeight = testImage->Height;
            
            // Asumiendo grid 4x4
            detectedFrameWidth = imageWidth / 4;
            detectedFrameHeight = imageHeight / 4;
            
            // COMENTADO: No mostrar dialogo cada vez
            /*
            MessageBox::Show(String::Format(
                "Analisis de imagen: {0}\n" +
                "Dimensiones: {1}x{2}\n" +
                "Frame detectado: {3}x{4}",
                filename, imageWidth, imageHeight, detectedFrameWidth, detectedFrameHeight));
            */
                
            delete testImage;
        }
        catch (Exception^ e) {
            detectedFrameWidth = 16;
            detectedFrameHeight = 16;
            MessageBox::Show("Error detectando tamano: " + e->Message);
        }
    }
    
    // VERSION SIMPLE: Dibujar frame con tamano fijo grande (para debugging)
    void DrawFrameLarge(Graphics^ g, int row, int col, float x, float y) {
        if (spriteImage == nullptr) return;
        
        System::Drawing::Rectangle sourceRect = System::Drawing::Rectangle(col * frameWidth, row * frameHeight, frameWidth, frameHeight);
        System::Drawing::Rectangle destRect = System::Drawing::Rectangle((int)x, (int)y, 32, 32); // Tamano fijo grande
        
        g->DrawImage(spriteImage, destRect, sourceRect, GraphicsUnit::Pixel);
    }
};

// Clase Player
public ref class Player : public GameObject {
private:
    int vidas;
    float velocidad;
    Direction direccion;
    int frameActual;
    int frameCounter;
    bool invulnerable;
    int invulnerabilityTimer;
    SpriteSheet^ spriteSheet;
    bool moving;
    bool blinkingEnabled; // Control local del parpadeo
    
    // Recursos recolectados
    array<int>^ recursos;
    
public:
    Player(float posX, float posY, float vel, int v) : GameObject(posX, posY, 16, 16) {
        vidas = v;
        velocidad = vel;
        direccion = Direction::Down;
        frameActual = 0;
        frameCounter = 0;
        invulnerable = false;
        invulnerabilityTimer = 0;
        moving = false;
        blinkingEnabled = false; // Parpadeo DESACTIVADO por defecto
        recursos = gcnew array<int>(6);
        
        // DETECTAR AUTOMATICAMENTE EL TAMANO DEL FRAME
        int detectedWidth, detectedHeight;
        SpriteSheet::DetectFrameSize("recursos/jugador.png", detectedWidth, detectedHeight);
        
        // Cargar spritesheet del jugador con tamano detectado
        spriteSheet = gcnew SpriteSheet("recursos/jugador.png", detectedWidth, detectedHeight, 4, 4);
        
        // Ajustar el tamano del GameObject basandose en el frame detectado
        width = detectedWidth;
        height = detectedHeight;
    }
    
    void Move(bool up, bool down, bool left, bool right) {
        float newX = x;
        float newY = y;
        
        // IMPORTANTE: Resetear moving al inicio - CORRECCION DEL BUG
        moving = false;
        
        if (up) {
            newY -= velocidad;
            direccion = Direction::Up;
            moving = true;
        }
        else if (down) {
            newY += velocidad;
            direccion = Direction::Down;
            moving = true;
        }
        else if (left) {
            newX -= velocidad;
            direccion = Direction::Left;
            moving = true;
        }
        else if (right) {
            newX += velocidad;
            direccion = Direction::Right;
            moving = true;
        }
        
        // Verificar limites de pantalla
        if (newX >= 0 && newX <= 800 - width) {
            x = newX;
        }
        if (newY >= GAME_AREA_TOP && newY <= 600 - height) {
            y = newY;
        }
    }
    
    void AddResource(ResourceType tipo) {
        recursos[(int)tipo]++;
    }
    
    void Damage() {
        if (!invulnerable) {
            vidas--;
            invulnerable = true;
            invulnerabilityTimer = 60; // 1 segundo a 60 FPS (mas corto)
        }
    }
    
    virtual void Update() override {
        // Actualizar invulnerabilidad
        if (invulnerable) {
            invulnerabilityTimer--;
            if (invulnerabilityTimer <= 0) {
                invulnerable = false;
            }
        }
        
        // CORRECCION: Actualizar animacion SOLO cuando hay movimiento
        if (moving) {
            frameCounter++;
            if (frameCounter >= 10) { // Cambiar frame cada 10 updates
                frameCounter = 0;
                frameActual = (frameActual + 1) % 4;
            }
        }
        else {
            // CORRECCION: Mantener frame estatico cuando no hay movimiento
            frameActual = 0; // Frame de reposo
            frameCounter = 0; // Resetear contador
        }
    }
    
    virtual void Draw(Graphics^ g) override {
        if (!active) return;
        
        // Efecto de parpadeo SOLO durante invulnerabilidad real (despues de recibir dano)
        if (invulnerable && blinkingEnabled && (invulnerabilityTimer % 15 < 5)) {
            return; // No dibujar para crear efecto de parpadeo
        }
        
        // Usar el tamano original detectado de la imagen
        spriteSheet->DrawFrame(g, (int)direccion, frameActual, x, y);
    }
    
    // FUNCION DE DEBUG: Dibujar con informacion de debug
    void DrawDebug(Graphics^ g) {
        if (!active) return;
        
        // Efecto de parpadeo durante invulnerabilidad
        if (invulnerable && (invulnerabilityTimer % 10 < 5)) {
            return; // No dibujar para crear efecto de parpadeo
        }
        
        String^ debugText = String::Format("Player\nDir: {0}\nFrame: {1}\nMoving: {2}\nInvulnerable: {3}\nTimer: {4}", 
            (int)direccion, frameActual, moving, invulnerable, invulnerabilityTimer);
        spriteSheet->DrawFrameDebug(g, (int)direccion, frameActual, x, y, debugText);
        
        // MOSTRAR TODAS LAS DIRECCIONES PARA DEBUG
        TestDirections(g);
    }
    
    // FUNCION DE DEBUG: Probar todas las direcciones
    void TestDirections(Graphics^ g) {
        if (!active) return;
        
        // Dibujar los 4 frames en diferentes posiciones para ver el mapeo
        for (int i = 0; i < 4; i++) {
            spriteSheet->DrawFrame(g, i, frameActual, x + (i * 80), y - 100);
            
            // Etiquetas para cada frame
            Font^ font = gcnew Font("Arial", 8);
            SolidBrush^ brush = gcnew SolidBrush(Color::White);
            String^ label = "";
            switch (i) {
                case 0: label = "Row 0"; break;
                case 1: label = "Row 1"; break;
                case 2: label = "Row 2"; break;
                case 3: label = "Row 3"; break;
            }
            g->DrawString(label, font, brush, x + (i * 80), y - 120);
            delete font;
            delete brush;
        }
    }
    
    property int Vidas { int get() { return vidas; } }
    property bool Invulnerable { bool get() { return invulnerable; } }
    property array<int>^ Recursos { array<int>^ get() { return recursos; } }
    
    // Control del parpadeo
    property bool BlinkingEnabled { 
        bool get() { return blinkingEnabled; }
        void set(bool value) { blinkingEnabled = value; }
    }
    
    void ToggleBlinking() {
        blinkingEnabled = !blinkingEnabled;
    }
    
    // METODOS PARA CONTROLAR INVULNERABILIDAD
    void SetInvulnerable(bool state) {
        invulnerable = state;
        if (!state) {
            invulnerabilityTimer = 0;
        }
    }
    
    void SetInvulnerabilityTimer(int timer) {
        invulnerabilityTimer = timer;
    }
};

// Clase Enemy
public ref class Enemy : public GameObject {
private:
    EnemyType tipo;
    int mundo;
    Direction direccion;
    int frameActual;
    int frameCounter;
    float velocidad;
    SpriteSheet^ spriteSheet;
    Random^ random;
    int changeDirectionTimer;
    Player^ target;
    
public:
    Enemy(float posX, float posY, EnemyType t, int m, Player^ player) : GameObject(posX, posY, 16, 16) {
        tipo = t;
        mundo = m;
        direccion = Direction::Down;
        frameActual = 0;
        frameCounter = 0;
        velocidad = 2.0f;
        random = gcnew Random();
        changeDirectionTimer = 0;
        target = player;
        
        // Cargar spritesheet segun tipo y mundo con deteccion automatica
        String^ filename = String::Format("recursos/enemigo{0}_mundo{1}.png", (int)t + 1, m);
        
        int detectedWidth, detectedHeight;
        SpriteSheet::DetectFrameSize(filename, detectedWidth, detectedHeight);
        
        spriteSheet = gcnew SpriteSheet(filename, detectedWidth, detectedHeight, 4, 4);
        
        // Ajustar el tamano del GameObject basandose en el frame detectado
        width = detectedWidth;
        height = detectedHeight;
    }
    
    virtual void Update() override {
        if (!active) return;
        
        float newX = x;
        float newY = y;
        
        switch (tipo) {
            case EnemyType::Linear:
                UpdateLinearMovement(newX, newY);
                break;
            case EnemyType::Random:
                UpdateRandomMovement(newX, newY);
                break;
            case EnemyType::Chase:
                UpdateChaseMovement(newX, newY);
                break;
        }
        
        // Verificar limites y actualizar posicion
        bool wasMoving = false; // CORRECCION: Trackear si realmente se movio
        
        if (newX >= 0 && newX <= 800 - width) {
            if (Math::Abs(newX - x) > 0.01f) wasMoving = true; // CORRECCION: Verificar movimiento real
            x = newX;
        } else {
            // Cambiar direccion horizontal
            if (direccion == Direction::Left) direccion = Direction::Right;
            else if (direccion == Direction::Right) direccion = Direction::Left;
        }
        
        if (newY >= GAME_AREA_TOP && newY <= 600 - height) {
            if (Math::Abs(newY - y) > 0.01f) wasMoving = true; // CORRECCION: Verificar movimiento real
            y = newY;
        } else {
            // Cambiar direccion vertical
            if (direccion == Direction::Up) direccion = Direction::Down;
            else if (direccion == Direction::Down) direccion = Direction::Up;
        }
        
        // CORRECCION: Actualizar animacion SOLO cuando hay movimiento real
        if (wasMoving) {
            frameCounter++;
            if (frameCounter >= 15) {
                frameCounter = 0;
                frameActual = (frameActual + 1) % 4;
            }
        } else {
            // CORRECCION: Mantener frame estatico cuando no hay movimiento
            frameActual = 0;
            frameCounter = 0;
        }
    }
    
private:
    void UpdateLinearMovement(float& newX, float& newY) {
        switch (direccion) {
            case Direction::Up: newY -= velocidad; break;
            case Direction::Down: newY += velocidad; break;
            case Direction::Left: newX -= velocidad; break;
            case Direction::Right: newX += velocidad; break;
        }
    }
    
    void UpdateRandomMovement(float& newX, float& newY) {
        changeDirectionTimer++;
        if (changeDirectionTimer >= 60) { // Cambiar direccion cada segundo
            changeDirectionTimer = 0;
            direccion = (Direction)(random->Next(4));
        }
        
        UpdateLinearMovement(newX, newY);
    }
    
    void UpdateChaseMovement(float& newX, float& newY) {
        if (target != nullptr) {
            float dx = target->X - x;
            float dy = target->Y - y;
            
            if (Math::Abs(dx) > Math::Abs(dy)) {
                if (dx > 0) {
                    direccion = Direction::Right;
                    newX += velocidad;
                } else {
                    direccion = Direction::Left;
                    newX -= velocidad;
                }
            } else {
                if (dy > 0) {
                    direccion = Direction::Down;
                    newY += velocidad;
                } else {
                    direccion = Direction::Up;
                    newY -= velocidad;
                }
            }
        }
    }
    
public:
    virtual void Draw(Graphics^ g) override {
        if (!active) return;
        // Usar el tamano original detectado de la imagen
        spriteSheet->DrawFrame(g, (int)direccion, frameActual, x, y);
    }
};

// Clase Resource
public ref class Resource : public GameObject {
private:
    ResourceType tipo;
    int mundo;
    float oscillationTimer;
    float baseY;
    
public:
    Resource(float posX, float posY, ResourceType t, int m) : GameObject(posX, posY, 12, 12) {
        tipo = t;
        mundo = m;
        oscillationTimer = 0;
        baseY = posY;
    }
    
    property ResourceType Type {
        ResourceType get() { return tipo; }
    }
    
    property int Mundo {
        int get() { return mundo; }
    }
    
    virtual void Update() override {
        if (!active) return;
        
        // Efecto de oscilacion
        oscillationTimer += 0.1f;
        y = baseY + (float)Math::Sin(oscillationTimer) * 3;
    }
    
    virtual void Draw(Graphics^ g) override {
        if (!active) return;
        
        // Dibujar recurso con color segun tipo
        Color color;
        switch (tipo) {
            case ResourceType::Empatia: color = Color::Green; break;
            case ResourceType::Etica: color = Color::SaddleBrown; break;
            case ResourceType::Sostenibilidad: color = Color::Gold; break;
            case ResourceType::IA: color = Color::Blue; break;
            case ResourceType::BigData: color = Color::Purple; break;
            case ResourceType::Automatizacion: color = Color::Red; break;
        }
        
        SolidBrush^ brush = gcnew SolidBrush(color);
        g->FillEllipse(brush, x, y, width, height);
        delete brush;
    }
};

// Clase World
public ref class World {
private:
    Bitmap^ background;
    int worldType;
    array<bool, 2>^ constructionMap; // Para mundo 3
    int constructedTiles;
    int totalTiles;
    
public:
    World(int type) {
        worldType = type;
        
        // Cargar fondo
        String^ filename = String::Format("recursos/mundo{0}.png", type);
        try {
            background = gcnew Bitmap(filename);
        }
        catch (Exception^ e) {
            // Crear un fondo de color solido si no se encuentra la imagen
            background = gcnew Bitmap(800, 600);
            Graphics^ g = Graphics::FromImage(background);
            Color bgColor;
            switch (type) {
                case 1: bgColor = Color::ForestGreen; break;
                case 2: bgColor = Color::DarkBlue; break;
                case 3: bgColor = Color::Gray; break;
                default: bgColor = Color::Black; break;
            }
            g->Clear(bgColor);
            delete g;
        }
        
        // Inicializar mapa de construccion para mundo 3
        if (type == 3) {
            constructionMap = gcnew array<bool, 2>(40, 30); // 20x20 tiles de 20x20 pixeles
            constructedTiles = 0;
            totalTiles = 40 * 30;
        }
    }
    
    void Draw(Graphics^ g) {
        if (background != nullptr) {
            // Dibujar fondo en el area de juego, no en toda la pantalla
            g->DrawImage(background, 0, GAME_AREA_TOP, 800, GAME_AREA_HEIGHT);
        }
        
        // Dibujar construcciones en mundo 3
        if (worldType == 3) {
            DrawConstructions(g);
        }
    }
    
    void BuildTile(float x, float y) {
        if (worldType != 3) return;
        
        int tileX = (int)(x / 20);
        int tileY = (int)(y / 20);
        
        if (tileX >= 0 && tileX < 40 && tileY >= 0 && tileY < 30) {
            if (!constructionMap[tileX, tileY]) {
                constructionMap[tileX, tileY] = true;
                constructedTiles++;
            }
        }
    }
    
private:
    void DrawConstructions(Graphics^ g) {
        SolidBrush^ brush = gcnew SolidBrush(Color::Yellow);
        
        for (int i = 0; i < 40; i++) {
            for (int j = 0; j < 30; j++) {
                if (constructionMap[i, j]) {
                    g->FillRectangle(brush, i * 20, j * 20, 20, 20);
                }
            }
        }
        
        delete brush;
    }
    
public:
    property float ConstructionPercentage {
        float get() {
            if (worldType != 3) return 0;
            return (float)constructedTiles / totalTiles * 100;
        }
    }
};

// Clase principal GameManager
public ref class GameManager {
private:
    GameState currentState;
    Player^ player;
    System::Collections::Generic::List<Enemy^>^ enemies;
    System::Collections::Generic::List<Resource^>^ resources;
    World^ currentWorld;
    
    // Configuracion del juego
    int vidas;
    int tiempo;
    float velocidad;
    
    // Variables de juego
    int puntuacion;
    int tiempoRestante;
    int menuSelection;
    
    // MODO DEBUG
    bool debugMode;
    
    // OPCION: Desactivar parpadeo de invulnerabilidad
    bool disableBlinking;
    
    // Recursos de fondo
    Bitmap^ menuBackground;
    
    // Iconos del HUD
    Bitmap^ iconoCorazon;
    Bitmap^ iconoReloj;
    Bitmap^ iconoCohete;
    Bitmap^ iconoMundo1;
    Bitmap^ iconoMundo2;
    Bitmap^ iconoMundo3;
    
    // Iconos de recursos para inventario
    Bitmap^ iconoRecursoEmpatia;
    Bitmap^ iconoRecursoSabiduria;
    Bitmap^ iconoRecursoValor;
    Bitmap^ iconoRecursoEsperanza;
    Bitmap^ iconoRecursoEquilibrio;
    
    // Ranking
    System::Collections::Generic::List<ScoreEntry^>^ ranking;
    
public:
    GameManager() {
        LoadParameters();
        InitializeGame();
        LoadRanking();
    }
    
private:
    void LoadParameters() {
        // Valores por defecto
        vidas = 3;
        tiempo = 300;
        velocidad = 5;
        
        try {
            array<String^>^ lines = File::ReadAllLines("FILES/PARAMETERS.txt");
            for each (String^ line in lines) {
                array<String^>^ parts = line->Split('=');
                if (parts->Length == 2) {
                    String^ key = parts[0]->Trim();
                    int value = Convert::ToInt32(parts[1]->Trim());
                    
                    if (key == "VIDAS") vidas = value;
                    else if (key == "TIEMPO") tiempo = value;
                    else if (key == "VELOCIDAD") velocidad = value;
                }
            }
        }
        catch (Exception^ e) {
            MessageBox::Show("Error cargando parametros: " + e->Message);
        }
    }
    
    void InitializeGame() {
        currentState = GameState::Menu;
        menuSelection = 0;
        debugMode = false; // INICIALIZAR MODO DEBUG
        disableBlinking = false; // INICIALIZAR OPCION DE PARPADEO
        
        // Cargar fondo del menu
        try {
            menuBackground = gcnew Bitmap("recursos/menu_fondo.png");
        }
        catch (Exception^ e) {
            menuBackground = gcnew Bitmap(800, 600);
            Graphics^ g = Graphics::FromImage(menuBackground);
            g->Clear(Color::DarkBlue);
            delete g;
        }
        
        // Cargar iconos del HUD
        try {
            iconoCorazon = gcnew Bitmap("recursos/corazon.png");
            iconoReloj = gcnew Bitmap("recursos/reloj.png");
            iconoCohete = gcnew Bitmap("recursos/cohete.png");
            iconoMundo1 = gcnew Bitmap("recursos/icono_mundo1.png");
            iconoMundo2 = gcnew Bitmap("recursos/icono_mundo2.png");
            iconoMundo3 = gcnew Bitmap("recursos/icono_mundo3.png");
            iconoRecursoEmpatia = gcnew Bitmap("recursos/recurso_empatia.png");
            iconoRecursoSabiduria = gcnew Bitmap("recursos/recurso_sabiduria.png");
            iconoRecursoValor = gcnew Bitmap("recursos/recurso_valor.png");
            iconoRecursoEsperanza = gcnew Bitmap("recursos/recurso_esperanza.png");
            iconoRecursoEquilibrio = gcnew Bitmap("recursos/recurso_equilibrio.png");
        }
        catch (Exception^ e) {
            // En caso de error, crear iconos por defecto
            iconoCorazon = gcnew Bitmap(32, 32);
            iconoReloj = gcnew Bitmap(32, 32);
            iconoCohete = gcnew Bitmap(32, 32);
            iconoMundo1 = gcnew Bitmap(32, 32);
            iconoMundo2 = gcnew Bitmap(32, 32);
            iconoMundo3 = gcnew Bitmap(32, 32);
            iconoRecursoEmpatia = gcnew Bitmap(24, 24);
            iconoRecursoSabiduria = gcnew Bitmap(24, 24);
            iconoRecursoValor = gcnew Bitmap(24, 24);
            iconoRecursoEsperanza = gcnew Bitmap(24, 24);
            iconoRecursoEquilibrio = gcnew Bitmap(24, 24);
        }
        
        enemies = gcnew System::Collections::Generic::List<Enemy^>();
        resources = gcnew System::Collections::Generic::List<Resource^>();
        ranking = gcnew System::Collections::Generic::List<ScoreEntry^>();
    }
    
    void LoadRanking() {
        try {
            if (File::Exists("FILES/SCORES.bin")) {
                FileStream^ fs = gcnew FileStream("FILES/SCORES.bin", FileMode::Open);
                BinaryReader^ br = gcnew BinaryReader(fs);
                
                while (fs->Position < fs->Length) {
                    array<Byte>^ nameBytes = br->ReadBytes(20);
                    String^ name = System::Text::Encoding::ASCII->GetString(nameBytes)->Trim('\0');
                    int score = br->ReadInt32();
                    ranking->Add(gcnew ScoreEntry(name, score));
                }
                
                br->Close();
                fs->Close();
            }
        }
        catch (Exception^ e) {
            MessageBox::Show("Error cargando ranking: " + e->Message);
        }
    }
    
    void SaveRanking() {
        try {
            FileStream^ fs = gcnew FileStream("FILES/SCORES.bin", FileMode::Create);
            BinaryWriter^ bw = gcnew BinaryWriter(fs);
            
            for each (ScoreEntry^ entry in ranking) {
                array<Byte>^ nameBytes = gcnew array<Byte>(20);
                array<Byte>^ nameData = System::Text::Encoding::ASCII->GetBytes(entry->nombre);
                Array::Copy(nameData, nameBytes, Math::Min(nameData->Length, 20));
                
                bw->Write(nameBytes);
                bw->Write(entry->puntuacion);
            }
            
            bw->Close();
            fs->Close();
        }
        catch (Exception^ e) {
            MessageBox::Show("Error guardando ranking: " + e->Message);
        }
    }
    
public:
    void StartGame() {
        player = gcnew Player(400, 300 + GAME_AREA_TOP, velocidad, vidas);
        puntuacion = 0;
        tiempoRestante = tiempo * 60; // Convertir a frames (60 FPS)
        
        // ELIMINAR PERIODO DE GRACIA: El player empieza normal, sin invulnerabilidad
        // No hay parpadeo inicial - el player puede recibir dano inmediatamente si lo toca un enemigo
        
        StartWorld1();
    }
    
    void StartWorld1() {
        currentState = GameState::World1;
        currentWorld = gcnew World(1);
        
        // Limpiar entidades
        enemies->Clear();
        resources->Clear();
        
        // Crear enemigos del mundo 1 en posiciones alejadas del player
        // Player esta en (400, 300), asi que colocar enemigos lejos
        Enemy^ enemy1 = gcnew Enemy(50, 50 + GAME_AREA_TOP, (EnemyType)0, 1, player);    // Esquina superior izquierda
        Enemy^ enemy2 = gcnew Enemy(700, 100 + GAME_AREA_TOP, (EnemyType)1, 1, player);  // Esquina superior derecha
        Enemy^ enemy3 = gcnew Enemy(100, 500, (EnemyType)2, 1, player);  // Esquina inferior izquierda
        
        enemies->Add(enemy1);
        enemies->Add(enemy2);
        enemies->Add(enemy3);
        
        // Crear recursos del mundo 1 (solo los primeros 3 tipos: Empatia, Etica, Sostenibilidad)
        Random^ random = gcnew Random();
        for (int i = 0; i < 3; i++) { // Solo tipos 0, 1, 2 para mundo 1
            for (int j = 0; j < 4; j++) { // 4 de cada tipo = 12 recursos totales
                Resource^ resource = gcnew Resource(
                    random->Next(50, 750),
                    random->Next(50 + GAME_AREA_TOP, 550),
                    (ResourceType)i,
                    1
                );
                resources->Add(resource);
            }
        }
    }
    
    void StartWorld2() {
        currentState = GameState::World2;
        currentWorld = gcnew World(2);
        
        // Limpiar entidades
        enemies->Clear();
        resources->Clear();
        
        // Crear enemigos del mundo 2 en posiciones alejadas del player
        Enemy^ enemy1 = gcnew Enemy(60, 80 + GAME_AREA_TOP, (EnemyType)0, 2, player);    // Esquina superior izquierda
        Enemy^ enemy2 = gcnew Enemy(720, 120 + GAME_AREA_TOP, (EnemyType)1, 2, player);  // Esquina superior derecha
        Enemy^ enemy3 = gcnew Enemy(120, 520, (EnemyType)2, 2, player);  // Esquina inferior izquierda
        
        enemies->Add(enemy1);
        enemies->Add(enemy2);
        enemies->Add(enemy3);
        
        // Crear recursos del mundo 2 (solo los tipos 3, 4, 5: IA, BigData, Automatizacion)
        Random^ random = gcnew Random();
        for (int i = 3; i < 6; i++) { // Solo tipos 3, 4, 5 para mundo 2
            for (int j = 0; j < 4; j++) { // 4 de cada tipo = 12 recursos totales
                Resource^ resource = gcnew Resource(
                    random->Next(50, 750),
                    random->Next(50 + GAME_AREA_TOP, 550),
                    (ResourceType)i,
                    2
                );
                resources->Add(resource);
            }
        }
    }
    
    void StartWorld3() {
        currentState = GameState::World3;
        currentWorld = gcnew World(3);
        
        // Limpiar entidades
        enemies->Clear();
        resources->Clear();
        
        // En el mundo 3, crear recursos especiales (mezcla de todos los tipos)
        Random^ random = gcnew Random();
        for (int i = 0; i < 6; i++) { // Todos los tipos de recursos
            for (int j = 0; j < 2; j++) { // 2 de cada tipo = 12 recursos totales
                Resource^ resource = gcnew Resource(
                    random->Next(50, 750),
                    random->Next(50 + GAME_AREA_TOP, 550),
                    (ResourceType)i,
                    3
                );
                resources->Add(resource);
            }
        }
    }
    
    void Update() {
        switch (currentState) {
            case GameState::Menu:
                // Logica del menu manejada por eventos de teclado
                break;
                
            case GameState::World1:
            case GameState::World2:
            case GameState::World3:
                UpdateGameplay();
                break;
                
            case GameState::GameOver:
            case GameState::Victory:
            case GameState::Ranking:
                // Logica de pantallas estaticas
                break;
        }
    }
    
private:
    void UpdateGameplay() {
        // Actualizar tiempo
        tiempoRestante--;
        if (tiempoRestante <= 0) {
            currentState = GameState::GameOver;
            return;
        }
        
        // Actualizar player
        if (player != nullptr) {
            player->Update();
            
            // Verificar vidas
            if (player->Vidas <= 0) {
                currentState = GameState::GameOver;
                return;
            }
        }
        
        // Actualizar enemigos
        for each (Enemy^ enemy in enemies) {
            enemy->Update();
            
            // Verificar colision con player SOLO si no esta invulnerable
            if (enemy->CheckCollision(player) && !player->Invulnerable) {
                player->Damage();
            }
        }
        
        // Actualizar recursos
        for each (Resource^ resource in resources) {
            resource->Update();
            
            // Verificar colision con player
            if (resource->CheckCollision(player)) {
                player->AddResource(resource->Type);
                puntuacion += 100;
                resource->Active = false;
            }
        }
        
        // Remover recursos inactivos
        for (int i = resources->Count - 1; i >= 0; i--) {
            if (!resources[i]->Active) {
                resources->RemoveAt(i);
            }
        }
        
        // Verificar condiciones de victoria por mundo
        CheckWorldCompletion();
    }
    
    void CheckWorldCompletion() {
        switch (currentState) {
            case GameState::World1:
                if (HasAllResourcesFromWorld(1)) {
                    StartWorld2();
                }
                break;
                
            case GameState::World2:
                if (HasAllResourcesFromWorld(2)) {
                    StartWorld3();
                }
                break;
                
            case GameState::World3:
                if (HasAllResourcesFromWorld(3)) {
                    currentState = GameState::Victory;
                }
                break;
        }
    }
    
    bool HasAllResourcesFromWorld(int world) {
        // Contar recursos activos que pertenecen al mundo actual
        int activeResourcesFromWorld = 0;
        for (int i = 0; i < resources->Count; i++) {
            if (resources[i]->Active && resources[i]->Mundo == world) {
                activeResourcesFromWorld++;
            }
        }
        
        // Si no hay recursos activos del mundo actual, significa que todos fueron recolectados
        return activeResourcesFromWorld == 0;
    }
    
    int GetTotalResourcesInCurrentWorld() {
        int currentWorldNum = 0;
        switch (currentState) {
            case GameState::World1: currentWorldNum = 1; break;
            case GameState::World2: currentWorldNum = 2; break;
            case GameState::World3: currentWorldNum = 3; break;
            default: return 0;
        }
        
        // Cada mundo tiene 12 recursos totales
        return 12;
    }
    
    int GetCollectedResourcesInCurrentWorld() {
        int currentWorldNum = 0;
        switch (currentState) {
            case GameState::World1: currentWorldNum = 1; break;
            case GameState::World2: currentWorldNum = 2; break;
            case GameState::World3: currentWorldNum = 3; break;
            default: return 0;
        }
        
        int totalResources = GetTotalResourcesInCurrentWorld();
        int activeResources = 0;
        
        for (int i = 0; i < resources->Count; i++) {
            if (resources[i]->Active && resources[i]->Mundo == currentWorldNum) {
                activeResources++;
            }
        }
        
        return totalResources - activeResources;
    }
    
    // Funcion para obtener la cantidad recolectada de cada tipo de recurso
    int GetCollectedResourceCount(ResourceType type) {
        int currentWorldNum = 0;
        switch (currentState) {
            case GameState::World1: currentWorldNum = 1; break;
            case GameState::World2: currentWorldNum = 2; break;
            case GameState::World3: currentWorldNum = 3; break;
            default: return 0;
        }
        
        int totalOfType = 0;
        int activeOfType = 0;
        
        for (int i = 0; i < resources->Count; i++) {
            if (resources[i]->Mundo == currentWorldNum && resources[i]->Type == type) {
                totalOfType++;
                if (resources[i]->Active) {
                    activeOfType++;
                }
            }
        }
        
        return totalOfType - activeOfType;
    }
    
    // Funcion para obtener la puntuacion de cada tipo de recurso
    int GetResourceScore(ResourceType type) {
        return GetCollectedResourceCount(type) * 10; // 10 puntos por recurso
    }
    
public:
    void Draw(Graphics^ g) {
        switch (currentState) {
            case GameState::Menu:
                DrawMenu(g);
                break;
                
            case GameState::World1:
            case GameState::World2:
            case GameState::World3:
                DrawGameplay(g);
                break;
                
            case GameState::GameOver:
                DrawGameOver(g);
                break;
                
            case GameState::Victory:
                DrawVictory(g);
                break;
                
            case GameState::Ranking:
                DrawRanking(g);
                break;
        }
    }
    
private:
    void DrawMenu(Graphics^ g) {
        // Dibujar fondo
        g->DrawImage(menuBackground, 0, 0, 800, 600);
        
        // Titulo
        Font^ titleFont = gcnew Font("Arial", 24, FontStyle::Bold);
        SolidBrush^ titleBrush = gcnew SolidBrush(Color::White);
        String^ title = "VIGILANTE DEL EQUILIBRIO";
        SizeF titleSize = g->MeasureString(title, titleFont);
        g->DrawString(title, titleFont, titleBrush, 
                     (800 - titleSize.Width) / 2, 150);
        
        // Opciones del menu
        Font^ menuFont = gcnew Font("Arial", 18);
        array<String^>^ options = {"JUGAR", "RANKING", "SALIR"};
        
        for (int i = 0; i < options->Length; i++) {
            SolidBrush^ brush = (i == menuSelection) ? 
                gcnew SolidBrush(Color::Yellow) : gcnew SolidBrush(Color::White);
            
            SizeF optionSize = g->MeasureString(options[i], menuFont);
            g->DrawString(options[i], menuFont, brush,
                         (800 - optionSize.Width) / 2, 300 + i * 50);
            
            delete brush;
        }
        
        delete titleFont;
        delete titleBrush;
        delete menuFont;
    }
    
    void DrawGameplay(Graphics^ g) {
        // Dibujar mundo
        if (currentWorld != nullptr) {
            currentWorld->Draw(g);
        }
        
        // Dibujar recursos
        for each (Resource^ resource in resources) {
            resource->Draw(g);
        }
        
        // Dibujar enemigos
        for each (Enemy^ enemy in enemies) {
            enemy->Draw(g);
        }
        
        // Dibujar player
        if (player != nullptr) {
            if (debugMode) {
                player->DrawDebug(g);
            } else {
                player->Draw(g);
            }
        }
        
        // Dibujar HUD
        DrawHUD(g);
        
        // Mostrar informacion de debug si esta activo
        if (debugMode) {
            DrawDebugInfo(g);
        }
    }
    
    void DrawHUD(Graphics^ g) {
        // Fondo del HUD principal (mas alto para acomodar iconos)
        SolidBrush^ hudBrush = gcnew SolidBrush(Color::FromArgb(150, 0, 0, 0));
        g->FillRectangle(hudBrush, 0, 0, 800, 80);
        
        // Fondo del inventario
        SolidBrush^ inventoryBrush = gcnew SolidBrush(Color::FromArgb(120, 50, 50, 50));
        g->FillRectangle(inventoryBrush, 0, 80, 800, 120);
        
        // Fuentes
        Font^ hudFont = gcnew Font("Arial", 12, FontStyle::Bold);
        Font^ inventoryFont = gcnew Font("Arial", 10);
        SolidBrush^ textBrush = gcnew SolidBrush(Color::White);
        SolidBrush^ inventoryTextBrush = gcnew SolidBrush(Color::LightGray);
        
        // === SECCION PRINCIPAL DEL HUD ===
        int x = 10;
        int y = 15;
        
        // Vidas con corazones
        for (int i = 0; i < player->Vidas; i++) {
            g->DrawImage(iconoCorazon, x + (i * 35), y, 30, 30);
        }
        g->DrawString("x" + player->Vidas, hudFont, textBrush, x + (player->Vidas * 35), y + 8);
        
        // Tiempo con reloj
        x += 200;
        g->DrawImage(iconoReloj, x, y, 30, 30);
        int segundos = tiempoRestante / 60;
        g->DrawString(segundos + "s", hudFont, textBrush, x + 35, y + 8);
        
        // Puntuacion con cohete
        x += 150;
        g->DrawImage(iconoCohete, x, y, 30, 30);
        g->DrawString(puntuacion.ToString(), hudFont, textBrush, x + 35, y + 8);
        
        // Mundo actual con icono correspondiente
        x += 150;
        Bitmap^ iconoMundoActual = nullptr;
        String^ worldText = "";
        switch (currentState) {
            case GameState::World1: 
                iconoMundoActual = iconoMundo1; 
                worldText = "Humanista"; 
                break;
            case GameState::World2: 
                iconoMundoActual = iconoMundo2; 
                worldText = "Tecnologico"; 
                break;
            case GameState::World3: 
                iconoMundoActual = iconoMundo3; 
                worldText = "Equilibrio"; 
                break;
        }
        
        if (iconoMundoActual != nullptr) {
            g->DrawImage(iconoMundoActual, x, y, 30, 30);
            g->DrawString(worldText, hudFont, textBrush, x + 35, y + 8);
        }
        
        // Progreso general
        x += 150;
        int totalResources = GetTotalResourcesInCurrentWorld();
        int collectedResources = GetCollectedResourcesInCurrentWorld();
        g->DrawString(collectedResources + "/" + totalResources, hudFont, textBrush, x, y + 8);
        
        // === INVENTARIO VISUAL ===
        g->DrawString("INVENTARIO DE RECURSOS:", inventoryFont, inventoryTextBrush, 10, 90);
        
        // Configurar posiciones para el inventario
        int inventoryStartX = 10;
        int inventoryStartY = 110;
        int itemWidth = 150;
        int itemHeight = 80;
        
        // Recursos del mundo actual
        System::Collections::Generic::List<ResourceType>^ currentWorldResources = gcnew System::Collections::Generic::List<ResourceType>();
        
        switch (currentState) {
            case GameState::World1:
                currentWorldResources->Add(ResourceType::Empatia);
                currentWorldResources->Add(ResourceType::Etica);
                break;
            case GameState::World2:
                currentWorldResources->Add(ResourceType::Sostenibilidad);
                currentWorldResources->Add(ResourceType::IA);
                break;
            case GameState::World3:
                currentWorldResources->Add(ResourceType::BigData);
                currentWorldResources->Add(ResourceType::Automatizacion);
                break;
        }
        
        // Dibujar items del inventario
        for (int i = 0; i < currentWorldResources->Count; i++) {
            ResourceType type = currentWorldResources[i];
            int count = GetCollectedResourceCount(type);
            int score = GetResourceScore(type);
            
            int itemX = inventoryStartX + (i * itemWidth);
            int itemY = inventoryStartY;
            
            // Fondo del item
            SolidBrush^ itemBrush = gcnew SolidBrush(Color::FromArgb(80, 100, 100, 100));
            g->FillRectangle(itemBrush, itemX, itemY, itemWidth - 10, itemHeight - 10);
            
            // Icono del recurso
            Bitmap^ iconoRecurso = nullptr;
            String^ nombreRecurso = "";
            
            switch (type) {
                case ResourceType::Empatia:
                    iconoRecurso = iconoRecursoEmpatia;
                    nombreRecurso = "Empatia";
                    break;
                case ResourceType::Etica:
                    iconoRecurso = iconoRecursoSabiduria;
                    nombreRecurso = "Etica";
                    break;
                case ResourceType::Sostenibilidad:
                    iconoRecurso = iconoRecursoEsperanza;
                    nombreRecurso = "Sostenibilidad";
                    break;
                case ResourceType::IA:
                    iconoRecurso = iconoRecursoValor;
                    nombreRecurso = "IA";
                    break;
                case ResourceType::BigData:
                    iconoRecurso = iconoRecursoEquilibrio;
                    nombreRecurso = "BigData";
                    break;
                case ResourceType::Automatizacion:
                    iconoRecurso = iconoRecursoValor;
                    nombreRecurso = "Automatizacion";
                    break;
            }
            
            if (iconoRecurso != nullptr) {
                g->DrawImage(iconoRecurso, itemX + 5, itemY + 5, 20, 20);
            }
            
            // Texto del recurso
            g->DrawString(nombreRecurso, inventoryFont, inventoryTextBrush, itemX + 30, itemY + 5);
            g->DrawString("Cant: " + count, inventoryFont, inventoryTextBrush, itemX + 5, itemY + 25);
            g->DrawString("Pts: " + score, inventoryFont, inventoryTextBrush, itemX + 5, itemY + 45);
            
            delete itemBrush;
        }
        
        // Limpiar recursos
        delete hudBrush;
        delete inventoryBrush;
        delete hudFont;
        delete inventoryFont;
        delete textBrush;
        delete inventoryTextBrush;
    }
    
    void DrawGameOver(Graphics^ g) {
        g->Clear(Color::Black);
        
        Font^ gameOverFont = gcnew Font("Arial", 36, FontStyle::Bold);
        SolidBrush^ gameOverBrush = gcnew SolidBrush(Color::Red);
        
        String^ text = "GAME OVER";
        SizeF textSize = g->MeasureString(text, gameOverFont);
        g->DrawString(text, gameOverFont, gameOverBrush,
                     (800 - textSize.Width) / 2, 200);
        
        Font^ scoreFont = gcnew Font("Arial", 18);
        SolidBrush^ scoreBrush = gcnew SolidBrush(Color::White);
        
        String^ scoreText = "Puntuacion Final: " + puntuacion;
        SizeF scoreSize = g->MeasureString(scoreText, scoreFont);
        g->DrawString(scoreText, scoreFont, scoreBrush,
                     (800 - scoreSize.Width) / 2, 300);
        
        String^ instructionText = "Presiona ENTER para volver al menu";
        SizeF instructionSize = g->MeasureString(instructionText, scoreFont);
        g->DrawString(instructionText, scoreFont, scoreBrush,
                     (800 - instructionSize.Width) / 2, 400);
        
        delete gameOverFont;
        delete gameOverBrush;
        delete scoreFont;
        delete scoreBrush;
    }
    
    void DrawVictory(Graphics^ g) {
        g->Clear(Color::Black);
        
        Font^ victoryFont = gcnew Font("Arial", 36, FontStyle::Bold);
        SolidBrush^ victoryBrush = gcnew SolidBrush(Color::Gold);
        
        String^ text = "¡VICTORIA!";
        SizeF textSize = g->MeasureString(text, victoryFont);
        g->DrawString(text, victoryFont, victoryBrush,
                     (800 - textSize.Width) / 2, 200);
        
        Font^ scoreFont = gcnew Font("Arial", 18);
        SolidBrush^ scoreBrush = gcnew SolidBrush(Color::White);
        
        String^ scoreText = "Puntuacion Final: " + puntuacion;
        SizeF scoreSize = g->MeasureString(scoreText, scoreFont);
        g->DrawString(scoreText, scoreFont, scoreBrush,
                     (800 - scoreSize.Width) / 2, 300);
        
        String^ instructionText = "Presiona ENTER para continuar";
        SizeF instructionSize = g->MeasureString(instructionText, scoreFont);
        g->DrawString(instructionText, scoreFont, scoreBrush,
                     (800 - instructionSize.Width) / 2, 400);
        
        delete victoryFont;
        delete victoryBrush;
        delete scoreFont;
        delete scoreBrush;
    }
    
    void DrawRanking(Graphics^ g) {
        g->Clear(Color::DarkBlue);
        
        Font^ titleFont = gcnew Font("Arial", 24, FontStyle::Bold);
        SolidBrush^ titleBrush = gcnew SolidBrush(Color::White);
        
        String^ title = "RANKING DE PUNTUACIONES";
        SizeF titleSize = g->MeasureString(title, titleFont);
        g->DrawString(title, titleFont, titleBrush,
                     (800 - titleSize.Width) / 2, 50);
        
        Font^ rankingFont = gcnew Font("Arial", 14);
        SolidBrush^ rankingBrush = gcnew SolidBrush(Color::White);
        
        // Ordenar ranking
        for (int i = 0; i < ranking->Count - 1; i++) {
            for (int j = 0; j < ranking->Count - 1 - i; j++) {
                if (ranking[j]->puntuacion < ranking[j + 1]->puntuacion) {
                    ScoreEntry^ temp = ranking[j];
                    ranking[j] = ranking[j + 1];
                    ranking[j + 1] = temp;
                }
            }
        }
        
        for (int i = 0; i < Math::Min(10, ranking->Count); i++) {
            String^ rankText = String::Format("{0}. {1} - {2}",
                                            i + 1,
                                            ranking[i]->nombre,
                                            ranking[i]->puntuacion);
            g->DrawString(rankText, rankingFont, rankingBrush, 50.0f, 120.0f + i * 30.0f);
        }
        
        String^ instructionText = "Presiona ESC para volver al menu";
        SizeF instructionSize = g->MeasureString(instructionText, rankingFont);
        g->DrawString(instructionText, rankingFont, rankingBrush,
                     (800 - instructionSize.Width) / 2, 500);
        
        delete titleFont;
        delete titleBrush;
        delete rankingFont;
        delete rankingBrush;
    }
    
public:
    void UpdatePlayerMovement(bool up, bool down, bool left, bool right) {
        if (player != nullptr) {
            player->Move(up, down, left, right);
        }
    }
    
    void HandleKeyDown(Keys key) {
        switch (currentState) {
            case GameState::Menu:
                HandleMenuInput(key);
                break;
                
            case GameState::World1:
            case GameState::World2:
            case GameState::World3:
                HandleGameplayInput(key);
                break;
                
            case GameState::GameOver:
                if (key == Keys::Enter) {
                    currentState = GameState::Menu;
                }
                break;
                
            case GameState::Victory:
                if (key == Keys::Enter) {
                    // Solicitar nombre para ranking (usar nombre por defecto)
                    String^ name = "Jugador";
                    ranking->Add(gcnew ScoreEntry(name, puntuacion));
                    SaveRanking();
                    currentState = GameState::Ranking;
                }
                break;
                
            case GameState::Ranking:
                if (key == Keys::Escape) {
                    currentState = GameState::Menu;
                }
                break;
        }
    }
    
private:
    void HandleMenuInput(Keys key) {
        switch (key) {
            case Keys::Up:
                menuSelection = (menuSelection - 1 + 3) % 3;
                break;
            case Keys::Down:
                menuSelection = (menuSelection + 1) % 3;
                break;
            case Keys::Enter:
                switch (menuSelection) {
                    case 0: // JUGAR
                        StartGame();
                        break;
                    case 1: // RANKING
                        currentState = GameState::Ranking;
                        break;
                    case 2: // SALIR
                        Application::Exit();
                        break;
                }
                break;
        }
    }
    
    void HandleGameplayInput(Keys key) {
        // Movimiento del jugador
        bool up = (key == Keys::W || key == Keys::Up);
        bool down = (key == Keys::S || key == Keys::Down);
        bool left = (key == Keys::A || key == Keys::Left);
        bool right = (key == Keys::D || key == Keys::Right);
        
        if (up || down || left || right) {
            player->Move(up, down, left, right);
        }
        
        // Construccion en mundo 3
        if (key == Keys::Space && currentState == GameState::World3) {
            currentWorld->BuildTile(player->X, player->Y);
        }
        
        // Pausa/Menu
        if (key == Keys::Escape) {
            currentState = GameState::Menu;
        }
    }
    
public:
    property GameState CurrentState { GameState get() { return currentState; } }
    
    void DrawDebugInfo(Graphics^ g) {
        // Informacion de debug en la esquina superior derecha
        Font^ debugFont = gcnew Font("Arial", 10);
        SolidBrush^ debugBrush = gcnew SolidBrush(Color::Yellow);
        SolidBrush^ bgBrush = gcnew SolidBrush(Color::FromArgb(200, 0, 0, 0));
        
        String^ debugText = String::Format(
            "DEBUG MODE (F12 para desactivar)\n" +
            "Parpadeo: {0} (F11 para cambiar)\n" +
            "FPS: ~60\n" +
            "Sprites: 16x16 frames en 4x4 grids\n" +
            "Player pos: ({1}, {2})\n" +
            "Enemies: {3}\n" +
            "Resources: {4}",
            player ? (player->BlinkingEnabled ? "ON" : "OFF") : "N/A",
            player ? (int)player->X : 0,
            player ? (int)player->Y : 0,
            enemies->Count,
            resources->Count
        );
        
        // Fondo semi-transparente para el texto de debug
        g->FillRectangle(bgBrush, 580, 60, 210, 140);
        g->DrawString(debugText, debugFont, debugBrush, 590, 70);
        
        delete debugFont;
        delete debugBrush;
        delete bgBrush;
    }
    
    // Funcion para activar/desactivar debug mode
    void ToggleDebugMode() {
        debugMode = !debugMode;
    }
    
    // Funcion para activar/desactivar parpadeo de invulnerabilidad
    void ToggleBlinking() {
        if (player != nullptr) {
            player->ToggleBlinking();
        }
    }
    
    property bool DebugMode {
        bool get() { return debugMode; }
        void set(bool value) { debugMode = value; }
    }
    
    property bool DisableBlinking {
        bool get() { return disableBlinking; }
        void set(bool value) { disableBlinking = value; }
    }
};
