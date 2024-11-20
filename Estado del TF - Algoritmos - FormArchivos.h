#pragma once
#include "Clases.h"
namespace TF {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de FormArchivos
	/// </summary>
	public ref class FormArchivos : public System::Windows::Forms::Form
	{
	public:
		FormArchivos()
		{
			InitializeComponent();
			this->Show();
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~FormArchivos()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ListBox^ listFiles;
	private: System::Windows::Forms::Timer^ Timer;
	private: System::ComponentModel::IContainer^ components;
	protected:

	protected:

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(FormArchivos::typeid));
			this->listFiles = (gcnew System::Windows::Forms::ListBox());
			this->Timer = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// listFiles
			// 
			this->listFiles->FormattingEnabled = true;
			this->listFiles->ItemHeight = 16;
			this->listFiles->Location = System::Drawing::Point(12, 12);
			this->listFiles->Name = L"listFiles";
			this->listFiles->Size = System::Drawing::Size(702, 436);
			this->listFiles->TabIndex = 0;
			// 
			// Timer
			// 
			this->Timer->Enabled = true;
			this->Timer->Interval = 7000;
			this->Timer->Tick += gcnew System::EventHandler(this, &FormArchivos::Timer_Tick);
			// 
			// FormArchivos
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(726, 460);
			this->Controls->Add(this->listFiles);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"FormArchivos";
			this->Text = L"Lectura";
			this->Load += gcnew System::EventHandler(this, &FormArchivos::FormArchivos_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
		void readBin() {
			listFiles->Items->Clear();
			if (!Directory::Exists("datos")) {
				Directory::CreateDirectory("datos");
			}
			String^ filePath = "datos\\puntaje.bin";

			FileStream^ fileBin = gcnew FileStream(filePath, FileMode::OpenOrCreate, FileAccess::Read);
			BinaryReader^ bin = gcnew BinaryReader(fileBin);
			try {
				while (fileBin->Position < fileBin->Length) {
					String^ nombre = bin->ReadString();
					int puntaje = bin->ReadInt32();
					DateTime fecha = DateTime::FromBinary(bin->ReadInt64());
					listFiles->Items->Add("Nombre: " + nombre + ", Puntaje: " + puntaje + ", Fecha: " + fecha.ToString("dd-MM-yy HH:mm:ss"));
				}
			}
			catch (Exception^ ex) {
				MessageBox::Show("Error al leer el archivo " + ex->Message);
			}
			finally {
				fileBin->Close();
				bin->Close();
			}
		}
		void readTXT() {
			// Verificar si la carpeta existe, si no, crearla
			if (!Directory::Exists("datos")) {
				Directory::CreateDirectory("datos");
			}
			String^ filePath = "datos\\configuracion.txt";

			StreamReader^ fileTXT = gcnew StreamReader(filePath);
			try {
				while (!fileTXT->EndOfStream) {
					String^ linea = fileTXT->ReadLine();
					array<String^>^ partes = linea->Split(',');
					String^ enemigos = partes[0];
					String^ aliados = partes[1];
					String^ tiempo = partes[2];
					listFiles->Items->Add("Enemigos: " + enemigos + ", Aliados: " + aliados + ", Tiempo: " + tiempo);
				}
			}
			catch (Exception^ ex) {
				MessageBox::Show("Error al leer el archivo de texto" + ex->Message);
			}
			finally {
				fileTXT->Close();
			}
		}
		void Timer_Tick(System::Object^ sender, System::EventArgs^ e) {
			readBin();
			readTXT();
		}
		private: System::Void FormArchivos_Load(System::Object^ sender, System::EventArgs^ e) {
			listFiles->HorizontalScrollbar = true; // Habilita desplazamiento horizontal
			listFiles->ScrollAlwaysVisible = true; // Mantiene visible la barra de desplazamiento
		}
	};
}
