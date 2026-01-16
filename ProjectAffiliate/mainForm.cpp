#include "loginForm.h"
#include "registrationForm.h"


using namespace System;
using namespace System::Windows::Forms;
[STAThreadAttribute]
int main(array<System::String^>^ args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	// Create the main window and run it
	ECommerce::loginF^ form = gcnew ECommerce::loginF();
	Application::Run(form);
	return 0;
}
