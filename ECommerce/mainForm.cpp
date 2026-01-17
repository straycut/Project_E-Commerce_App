#include "loginForm.h"
#include "registrationForm.h"
using namespace ECommerce;
using namespace std;

using namespace System;
using namespace System::Windows::Forms;
[STAThreadAttribute]
int main(array<System::String^>^ args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	// Create the main window and run it
	loginF^ form = gcnew loginF();
	Application::Run(form);
	return 0;
}
