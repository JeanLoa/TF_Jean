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
	/// Resumen de FormCredits
	/// </summary>
	public ref class FormCredits : public System::Windows::Forms::Form
	{
	public:
		FormCredits(void)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//
			LoadImages();
		}
		void LoadImages() {
			images = gcnew array<Bitmap^>(3) {
					gcnew Bitmap("Creditos\\Jean.png"),
					gcnew Bitmap("Creditos\\Joaquin.png"),
					gcnew Bitmap("Creditos\\Juan.png")
			};
			messages = gcnew array<Bitmap^>(3) {
				gcnew Bitmap("Creditos\\Jean_Mensaje.png"),
					gcnew Bitmap("Creditos\\Joaquin_Mensaje.png"),
					gcnew Bitmap("Creditos\\Juan_Mensaje.png"),
			};
			credits = gcnew array<Bitmap^> {
					gcnew Bitmap("Creditos\\Fondo\\Fondo1.png"),
					gcnew Bitmap("Creditos\\Fondo\\Fondo2.png"),
					gcnew Bitmap("Creditos\\Fondo\\Fondo3.png"),
					gcnew Bitmap("Creditos\\Fondo\\Fondo4.png"),
					gcnew Bitmap("Creditos\\Fondo\\Fondo5.png"),
					gcnew Bitmap("Creditos\\Fondo\\Fondo6.png"),
					gcnew Bitmap("Creditos\\Fondo\\Fondo7.png"),
					gcnew Bitmap("Creditos\\Fondo\\Fondo8.png"),
					gcnew Bitmap("Creditos\\Fondo\\Fondo9.png"),
					gcnew Bitmap("Creditos\\Fondo\\Fondo10.png"),
					gcnew Bitmap("Creditos\\Fondo\\Fondo11.png"),
					gcnew Bitmap("Creditos\\Fondo\\Fondo12.png"),
					gcnew Bitmap("Creditos\\Fondo\\Fondo13.png"),
					gcnew Bitmap("Creditos\\Fondo\\Fondo14.png"),
					gcnew Bitmap("Creditos\\Fondo\\Fondo15.png"),
					gcnew Bitmap("Creditos\\Fondo\\Fondo16.png"),
					gcnew Bitmap("Creditos\\Fondo\\Fondo17.png"),
					gcnew Bitmap("Creditos\\Fondo\\Fondo18.png"),
					gcnew Bitmap("Creditos\\Fondo\\Fondo19.png"),
					gcnew Bitmap("Creditos\\Fondo\\Fondo20.png"),
					gcnew Bitmap("Creditos\\Fondo\\Fondo21.png"),
					gcnew Bitmap("Creditos\\Fondo\\Fondo22.png"),
					gcnew Bitmap("Creditos\\Fondo\\Fondo23.png"),
					gcnew Bitmap("Creditos\\Fondo\\Fondo24.png"),
					gcnew Bitmap("Creditos\\Fondo\\Fondo25.png"),
					gcnew Bitmap("Creditos\\Fondo\\Fondo26.png"),
					gcnew Bitmap("Creditos\\Fondo\\Fondo27.png"),
					gcnew Bitmap("Creditos\\Fondo\\Fondo28.png"),
					gcnew Bitmap("Creditos\\Fondo\\Fondo29.png"),
					gcnew Bitmap("Creditos\\Fondo\\Fondo30.png")
			};
			this->creditsStartIndex = 0;
			this->creditsEndIndex = 29;
			this->creditsIndex = 0;
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~FormCredits()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::ComponentModel::IContainer^ components;
	protected:

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>

		array<Bitmap^>^ credits;
		int creditsIndex;
		int creditsStartIndex;
		int creditsEndIndex;
		array<Bitmap^>^ images;
		array<Bitmap^>^ messages;
	private: System::Windows::Forms::Timer^ Timer;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(FormCredits::typeid));
			this->Timer = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// Timer
			// 
			this->Timer->Enabled = true;
			this->Timer->Tick += gcnew System::EventHandler(this, &FormCredits::Timer_Tick);
			// 
			// FormCredits
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(877, 447);
			this->DoubleBuffered = true;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"FormCredits";
			this->Text = L"Creditos";
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &FormCredits::FormCredits_Paint);
			this->ResumeLayout(false);

		}
#pragma endregion
		void FormCredits_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
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
			Bitmap^ bitmap = gcnew Bitmap(credits[creditsIndex]);

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
			for (int i = 0; i < 3; ++i) {
				// Posición de la imagen de fondo
				double imageX = (g->VisibleClipBounds.Width / 3) * (i + 0.1);
				double imageY = g->VisibleClipBounds.Height / 2.9;

				// Dibuja la imagen de fondo
				g->DrawImage(images[i], imageX, imageY, 160, 160);

				// Posición de la imagen del mensaje (ajustada para superponerla sobre la imagen de fondo)
				double messageX = imageX - 45; // Ajusta para centrar horizontalmente
				double messageY = imageY - 50; // Ajusta para colocarla sobre la imagen

				// Dibuja la imagen del mensaje encima de la imagen de fondo
				g->DrawImage(messages[i], messageX, messageY, 250, 92.5); // Ajusta el tamaño si es necesario
			}
		}
		void Timer_Tick(System::Object^ sender, System::EventArgs^ e) {
			creditsIndex++;
			if (creditsIndex > creditsEndIndex) {
				creditsIndex = creditsStartIndex;
			}
			this->Invalidate();
		}
	};
}
