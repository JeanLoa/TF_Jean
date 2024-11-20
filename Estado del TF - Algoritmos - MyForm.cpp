#include "FormMenu.h"
#include <iostream>

using namespace System::Windows::Forms;
void main() {
	srand(time(0));
	Application::EnableVisualStyles();
	Application::Run(gcnew TF::FormMenu());
}
