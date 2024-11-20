#pragma once
#include "MyForm.h"
#include "FormCredits.h"
#include "Clases.h"


namespace TF {
	using namespace System::Drawing::Text;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de FormMenu
	/// </summary>
	public ref class FormMenu : public System::Windows::Forms::Form
	{
	public:
		FormMenu(void)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//
			LoadMenu();
		}

		void LoadMenu() {
			images = gcnew array<Bitmap^>(30) {
				gcnew Bitmap("Imagenes\\Menu\\Menu1.jpg"),
				gcnew Bitmap("Imagenes\\Menu\\Menu2.jpg"),
				gcnew Bitmap("Imagenes\\Menu\\Menu3.jpg"),
				gcnew Bitmap("Imagenes\\Menu\\Menu4.jpg"),
				gcnew Bitmap("Imagenes\\Menu\\Menu5.jpg"),
				gcnew Bitmap("Imagenes\\Menu\\Menu6.jpg"),
				gcnew Bitmap("Imagenes\\Menu\\Menu7.jpg"),
				gcnew Bitmap("Imagenes\\Menu\\Menu8.jpg"),
				gcnew Bitmap("Imagenes\\Menu\\Menu9.jpg"),
				gcnew Bitmap("Imagenes\\Menu\\Menu10.jpg"),
				gcnew Bitmap("Imagenes\\Menu\\Menu11.jpg"),
				gcnew Bitmap("Imagenes\\Menu\\Menu12.jpg"),
				gcnew Bitmap("Imagenes\\Menu\\Menu13.jpg"),
				gcnew Bitmap("Imagenes\\Menu\\Menu14.jpg"),
				gcnew Bitmap("Imagenes\\Menu\\Menu15.jpg"),
				gcnew Bitmap("Imagenes\\Menu\\Menu16.jpg"),
				gcnew Bitmap("Imagenes\\Menu\\Menu17.jpg"),
				gcnew Bitmap("Imagenes\\Menu\\Menu18.jpg"),
				gcnew Bitmap("Imagenes\\Menu\\Menu19.jpg"),
				gcnew Bitmap("Imagenes\\Menu\\Menu20.jpg"),
				gcnew Bitmap("Imagenes\\Menu\\Menu21.jpg"),
				gcnew Bitmap("Imagenes\\Menu\\Menu22.jpg"),
				gcnew Bitmap("Imagenes\\Menu\\Menu23.jpg"),
				gcnew Bitmap("Imagenes\\Menu\\Menu24.jpg"),
				gcnew Bitmap("Imagenes\\Menu\\Menu25.jpg"),
				gcnew Bitmap("Imagenes\\Menu\\Menu26.jpg"),
				gcnew Bitmap("Imagenes\\Menu\\Menu27.jpg"),
				gcnew Bitmap("Imagenes\\Menu\\Menu28.jpg"),
				gcnew Bitmap("Imagenes\\Menu\\Menu29.jpg"),
				gcnew Bitmap("Imagenes\\Menu\\Menu30.jpg")
			};
			startIndex = 0;
			endIndex = 29;
			menuIndex = startIndex;
			message = gcnew Bitmap("Imagenes\\Menu\\Mensaje.png");
			menuMusic = gcnew SoundPlayer("Musicas\\Musica_GMA_Menu.wav");
			openingMusic = gcnew SoundPlayer("EfectosDeSonido\\Hero\\HeroJoining.wav");
			endingMusic = gcnew SoundPlayer("EfectosDeSonido\\Hero\\HeroDeath.wav");
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~FormMenu()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ btJugar;
	private: System::Windows::Forms::Button^ btCreditos;
	private: System::Windows::Forms::Button^ btSalir;
	protected:



	private:
		Bitmap^ message;
		array<Bitmap^>^ images;
		int menuIndex;
		int endIndex, startIndex;
		SoundPlayer^ menuMusic;

		SoundPlayer^ openingMusic;
		SoundPlayer^ endingMusic;
		System::Drawing::Font^ customFont;
	private: System::Windows::Forms::Timer^ Timer;
	private: System::ComponentModel::IContainer^ components;
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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(FormMenu::typeid));
			this->btJugar = (gcnew System::Windows::Forms::Button());
			this->btCreditos = (gcnew System::Windows::Forms::Button());
			this->btSalir = (gcnew System::Windows::Forms::Button());
			this->Timer = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// btJugar
			// 
			this->btJugar->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->btJugar->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btJugar->Font = (gcnew System::Drawing::Font(L"Minecrafter Alt", 19.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btJugar->ForeColor = System::Drawing::SystemColors::ControlDark;
			this->btJugar->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btJugar.Image")));
			this->btJugar->Location = System::Drawing::Point(293, 248);
			this->btJugar->Name = L"btJugar";
			this->btJugar->Size = System::Drawing::Size(371, 64);
			this->btJugar->TabIndex = 0;
			this->btJugar->Text = L"Jugar";
			this->btJugar->UseVisualStyleBackColor = false;
			this->btJugar->Click += gcnew System::EventHandler(this, &FormMenu::btJugar_Click);
			// 
			// btCreditos
			// 
			this->btCreditos->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->btCreditos->Font = (gcnew System::Drawing::Font(L"Minecrafter Alt", 19.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btCreditos->ForeColor = System::Drawing::SystemColors::ControlDark;
			this->btCreditos->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btCreditos.Image")));
			this->btCreditos->Location = System::Drawing::Point(293, 318);
			this->btCreditos->Name = L"btCreditos";
			this->btCreditos->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->btCreditos->Size = System::Drawing::Size(371, 64);
			this->btCreditos->TabIndex = 1;
			this->btCreditos->Text = L"Creditos";
			this->btCreditos->UseVisualStyleBackColor = false;
			this->btCreditos->Click += gcnew System::EventHandler(this, &FormMenu::btCreditos_Click);
			// 
			// btSalir
			// 
			this->btSalir->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->btSalir->Font = (gcnew System::Drawing::Font(L"Minecrafter Alt", 19.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btSalir->ForeColor = System::Drawing::SystemColors::ControlDark;
			this->btSalir->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btSalir.Image")));
			this->btSalir->Location = System::Drawing::Point(293, 388);
			this->btSalir->Name = L"btSalir";
			this->btSalir->Size = System::Drawing::Size(371, 64);
			this->btSalir->TabIndex = 2;
			this->btSalir->Text = L"Salir";
			this->btSalir->UseVisualStyleBackColor = false;
			this->btSalir->Click += gcnew System::EventHandler(this, &FormMenu::btSalir_Click);
			// 
			// Timer
			// 
			this->Timer->Enabled = true;
			this->Timer->Tick += gcnew System::EventHandler(this, &FormMenu::Timer_Tick);
			// 
			// FormMenu
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(957, 583);
			this->Controls->Add(this->btSalir);
			this->Controls->Add(this->btCreditos);
			this->Controls->Add(this->btJugar);
			this->DoubleBuffered = true;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximumSize = System::Drawing::Size(975, 630);
			this->MinimumSize = System::Drawing::Size(975, 630);
			this->Name = L"FormMenu";
			this->Text = L"GMA";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &FormMenu::FormMenu_FormClosed);
			this->Load += gcnew System::EventHandler(this, &FormMenu::FormMenu_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &FormMenu::FormMenu_Paint);
			this->ResumeLayout(false);

		}
#pragma endregion
		void FormMenu_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
			Graphics^ g = e->Graphics;
			System::Drawing::Imaging::ColorMatrix^ colorMatrix = gcnew System::Drawing::Imaging::ColorMatrix();
			System::Drawing::Imaging::ImageAttributes^ imageAttributes = gcnew System::Drawing::Imaging::ImageAttributes();

			colorMatrix->Matrix33 = 1.0f; // Alpha (opacidad)
			colorMatrix->Matrix44 = 1.0f; // W

			imageAttributes->SetColorMatrix(colorMatrix, System::Drawing::Imaging::ColorMatrixFlag::Default, System::Drawing::Imaging::ColorAdjustType::Bitmap);

			// Obtener dimensiones de la ventana para pantalla completa
			int screenWidth = g->VisibleClipBounds.Width;
			int screenHeight = g->VisibleClipBounds.Height;

			// Cargar la imagen como Bitmap
			Bitmap^ bitmap = gcnew Bitmap(images[menuIndex]);

			// Calcular el nuevo tamaño manteniendo la relación de aspecto
			float aspectRatio = (float)bitmap->Width / bitmap->Height;
			int newWidth = Math::Round(screenWidth * 1.5); // Aumenta el ancho en un 50%
			int newHeight = Math::Round(newWidth / aspectRatio);

			// Centrar la imagen en la pantalla con el ancho ajustado
			int x = (screenWidth - newWidth) / 2;
			int y = (screenHeight - newHeight) / 2;

			// Dibuja la imagen con el nuevo tamaño ajustado
			System::Drawing::Rectangle destRect = System::Drawing::Rectangle(x, y, newWidth, newHeight);
			g->DrawImage(bitmap, destRect, 0.0, 0.0, bitmap->Width, bitmap->Height, System::Drawing::GraphicsUnit::Pixel, imageAttributes);

			int messageWidth = 300;
			int messageHeight = 111;
			int messageX = (g->VisibleClipBounds.Width - messageWidth) / 2;
			int messageY = (g->VisibleClipBounds.Height - messageHeight) / 5;
			g->DrawImage(message, messageX, messageY, messageWidth, messageHeight);
		}

		void Timer_Tick(System::Object^ sender, System::EventArgs^ e) {
			++menuIndex;
			if (menuIndex > endIndex) {
				menuIndex = startIndex;
			}
			this->Invalidate();
		}
		void FormMenu_Load(System::Object^ sender, System::EventArgs^ e) {
			btJugar->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			btJugar->FlatAppearance->BorderSize = 0; // Quitar el borde

			btCreditos->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			btCreditos->FlatAppearance->BorderSize = 0; // Quitar el borde

			btSalir->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			btSalir->FlatAppearance->BorderSize = 0; // Quitar el borde
			menuMusic->PlayLooping();
		}
		void btSalir_Click(System::Object^ sender, System::EventArgs^ e) {
			endingMusic->PlaySync();
			this->Close();
		}
		void btJugar_Click(System::Object^ sender, System::EventArgs^ e) {
			openingMusic->PlaySync();
			MyForm^ formJuego = gcnew MyForm;
			formJuego->ShowDialog();
			menuMusic->PlayLooping();
		}
		void btCreditos_Click(System::Object^ sender, System::EventArgs^ e) {
			FormCredits^ formCreditos = gcnew FormCredits;
			formCreditos->ShowDialog();
		}
		void FormMenu_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e) {
			updateGuardianIndex();
		}
	};
}
