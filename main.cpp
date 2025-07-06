#include "stdafx.h"
#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
    // Habilitar estilos visuales
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    
    // Verificar existencia de directorio de recursos
    if (!System::IO::Directory::Exists("recursos"))
    {
        MessageBox::Show("No se encontro el directorio 'recursos'. Asegurate de que el directorio existe y contiene todos los archivos necesarios.", 
                        "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        return -1;
    }
    
    // Crear directorio FILES si no existe
    if (!System::IO::Directory::Exists("FILES"))
    {
        try
        {
            System::IO::Directory::CreateDirectory("FILES");
        }
        catch (System::Exception^ e)
        {
            MessageBox::Show("No se pudo crear el directorio FILES: " + e->Message, 
                            "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return -1;
        }
    }
    
    // Crear y ejecutar el formulario principal
    try
    {
        VigilanteDelEquilibrio::MainForm form;
        Application::Run(%form);
    }
    catch (System::Exception^ e)
    {
        MessageBox::Show("Error al iniciar el juego: " + e->Message, 
                        "Error Fatal", MessageBoxButtons::OK, MessageBoxIcon::Error);
        return -1;
    }
    
    return 0;
}
