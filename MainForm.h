#pragma once
#include "GameManager.h"

namespace VigilanteDelEquilibrio {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class MainForm : public System::Windows::Forms::Form
    {
    private:
        GameManager^ gameManager;
        Timer^ gameTimer;
        array<bool>^ keysPressed;
        
    public:
        MainForm(void)
        {
            InitializeComponent();
            InitializeGame();
        }

    protected:
        ~MainForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::ComponentModel::Container ^components;

        void InitializeComponent(void)
        {
            this->SuspendLayout();
            // 
            // MainForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(800, 600);
            this->Name = L"MainForm";
            this->Text = L"Vigilante del Equilibrio";
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->KeyPreview = true;
            
            // Eventos
            this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainForm::MainForm_Paint);
            this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::MainForm_KeyDown);
            this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::MainForm_KeyUp);
            this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
            
            this->ResumeLayout(false);
        }
        
        void InitializeGame()
        {
            // Inicializar GameManager
            gameManager = gcnew GameManager();
            
            // Inicializar array de teclas presionadas
            keysPressed = gcnew array<bool>(256);
            
            // Configurar timer del juego
            gameTimer = gcnew Timer();
            gameTimer->Interval = 16; // ~60 FPS
            gameTimer->Tick += gcnew EventHandler(this, &MainForm::GameTimer_Tick);
            gameTimer->Start();
        }
        
        void MainForm_Load(System::Object^ sender, System::EventArgs^ e)
        {
            // Configurar ventana
            this->SetStyle(ControlStyles::AllPaintingInWmPaint | 
                          ControlStyles::UserPaint | 
                          ControlStyles::DoubleBuffer, true);
        }
        
        void MainForm_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e)
        {
            // Dibujar el juego
            if (gameManager != nullptr)
            {
                gameManager->Draw(e->Graphics);
            }
        }
        
        void MainForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
        {
            keysPressed[(int)e->KeyCode] = true;
            
            // AGREGAR: Activar/desactivar modo debug con F12
            if (e->KeyCode == Keys::F12) {
                if (gameManager != nullptr) {
                    gameManager->ToggleDebugMode();
                }
                return;
            }
            
            // AGREGAR: Activar/desactivar parpadeo con F11
            if (e->KeyCode == Keys::F11) {
                if (gameManager != nullptr) {
                    gameManager->ToggleBlinking();
                }
                return;
            }
            
            // Manejar entrada de teclas
            if (gameManager != nullptr)
            {
                gameManager->HandleKeyDown(e->KeyCode);
            }
        }
        
        void MainForm_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
        {
            keysPressed[(int)e->KeyCode] = false;
        }
        
        void GameTimer_Tick(System::Object^ sender, System::EventArgs^ e)
        {
            // Actualizar logica del juego
            if (gameManager != nullptr)
            {
                gameManager->Update();
                
                // Manejar entrada continua de movimiento
                HandleContinuousInput();
                
                // Redibujar
                this->Invalidate();
            }
        }
        
        void HandleContinuousInput()
        {
            // Verificar si estamos en gameplay
            if (gameManager->CurrentState == GameState::World1 ||
                gameManager->CurrentState == GameState::World2 ||
                gameManager->CurrentState == GameState::World3)
            {
                // CORRECCION: Obtener estado actual de todas las teclas de movimiento
                bool up = keysPressed[(int)Keys::W] || keysPressed[(int)Keys::Up];
                bool down = keysPressed[(int)Keys::S] || keysPressed[(int)Keys::Down];
                bool left = keysPressed[(int)Keys::A] || keysPressed[(int)Keys::Left];
                bool right = keysPressed[(int)Keys::D] || keysPressed[(int)Keys::Right];
                
                // CORRECCION CRITICA: Actualizar movimiento EN CADA FRAME
                // Esto asegura que el estado de movimiento siempre refleje el input actual
                gameManager->UpdatePlayerMovement(up, down, left, right);
            }
        }
    };
}
