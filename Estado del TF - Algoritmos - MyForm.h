#pragma once
#include "Windows.h"
#include "Clases.h"
#include "FormEnd.h"
#include "FormArchivos.h"

namespace TF {
	using namespace System::Media;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	public ref class MyForm : public Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			LoadGame();
			this->KeyPreview = true;
			this->Focus();


			this->SetStyle(System::Windows::Forms::ControlStyles::UserPaint, true);
			this->SetStyle(System::Windows::Forms::ControlStyles::AllPaintingInWmPaint, true);
			this->SetStyle(System::Windows::Forms::ControlStyles::OptimizedDoubleBuffer, true);
			this->UpdateStyles();

		}
		void LoadGame() {
			Graphics^ g = this->CreateGraphics();
			Juego_GMA = gcnew GMA(g);
			this->closed = false;
			formArchivo = gcnew FormArchivos;
		}
	protected:

		~MyForm()
		{
			if (components) {
				delete components;
			}
		}
	private: System::ComponentModel::IContainer^ components;
	private: System::Windows::Forms::Timer^ Timer;
		   bool closed;
		   GMA^ Juego_GMA;
		   FormArchivos^ formArchivo;

		   BufferedGraphicsContext^ bufferContext;
		   BufferedGraphics^ bufferGraphics;

#pragma region Windows Form Designer generated code

		 void InitializeComponent(void)
		 {
			 this->components = (gcnew System::ComponentModel::Container());
			 System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			 this->Timer = (gcnew System::Windows::Forms::Timer(this->components));
			 this->SuspendLayout();
			 // 
			 // Timer
			 // 
			 this->Timer->Enabled = true;
			 this->Timer->Interval = 70;
			 this->Timer->Tick += gcnew System::EventHandler(this, &MyForm::Timer_Tick);
			 // 
			 // MyForm
			 // 
			 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			 this->AutoSize = true;
			 this->BackColor = System::Drawing::SystemColors::Control;
			 this->ClientSize = System::Drawing::Size(1527, 793);
			 this->DoubleBuffered = true;
			 this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			 this->MaximumSize = System::Drawing::Size(1545, 840);
			 this->MinimumSize = System::Drawing::Size(1545, 840);
			 this->Name = L"MyForm";
			 this->Text = L"GMA";
			 this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &MyForm::MyForm_FormClosed);
			 this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
			 this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			 this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyUp);
			 this->ResumeLayout(false);

		 }
#pragma endregion
		void MyForm_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
			Graphics^ g = e->Graphics;
			Juego_GMA->ValidacionMundo();
			Juego_GMA->ReproduccionDelMundo(g, Timer);
			Juego_GMA->Dibujar(g);
		}
		void Timer_Tick(System::Object^ sender, System::EventArgs^ e) {
			Graphics^ g = this->CreateGraphics();
			String^ Fin = nullptr;
			if (!closed) {
				LoadFiles();
				Juego_GMA->CondicionesParaTempo();
				Juego_GMA->CondicionesParaEnemigos(g);
				Juego_GMA->CondicionesParaAliados(Timer);
				Juego_GMA->AccionesDelJugador(g);
				Juego_GMA->ValidacionDeEstados(Timer);
				Fin = Juego_GMA->getEnd();
				if (!String::IsNullOrEmpty(Fin)) {
					FormEnd^ formEnd = gcnew FormEnd(Fin);
					static bool end = false;
					if (!end) {
						formEnd->Show();
						end = true;
					}
				}
				if (Timer->Enabled) {
					this->Invalidate();
				}
			}
		}
		void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
			Graphics^ g = this->CreateGraphics();
			Juego_GMA->TeclasPulsadas(e, g);
		}
		void MyForm_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
			Juego_GMA->TeclasLevantadas(e);
		}
		void MyForm_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e) {
			closed = true;
			Juego_GMA = nullptr;
		}
		void LoadFiles() {
			Juego_GMA->setLapseFiles(Juego_GMA->getLapseFiles() + 0.1);
			if (Juego_GMA->getLapseFiles() > 10) {
				Juego_GMA->saveBin();
				Juego_GMA->saveTXT();
				Juego_GMA->setLapseFiles(0);
			}
		}
	};
}
