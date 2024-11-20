#pragma once

namespace TF {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de FormEnd
	/// </summary>
	public ref class FormEnd : public Form
	{
	public:
		FormEnd(String^ End)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//
			this->End = End;
			LoadImages();
		}
		void LoadImages() {
			images = gcnew array<Bitmap^>{
				gcnew Bitmap("Imagenes\\Sprites\\Events\\SpriteDeadRight3.png"),
				gcnew Bitmap("Imagenes\\Sprites\\Events\\SpriteWin2.png")
			};
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~FormEnd()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ lbGanador;
	protected:

	protected:

	private:
		String^ End;
		array<Bitmap^>^ images;
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(FormEnd::typeid));
			this->lbGanador = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// lbGanador
			// 
			this->lbGanador->AutoSize = true;
			this->lbGanador->Font = (gcnew System::Drawing::Font(L"Microsoft Tai Le", 36, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbGanador->Location = System::Drawing::Point(295, 96);
			this->lbGanador->Name = L"lbGanador";
			this->lbGanador->Size = System::Drawing::Size(57, 77);
			this->lbGanador->TabIndex = 0;
			this->lbGanador->Text = L"-";
			// 
			// FormEnd
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->ClientSize = System::Drawing::Size(636, 431);
			this->Controls->Add(this->lbGanador);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"FormEnd";
			this->Text = L"Final";
			this->Load += gcnew System::EventHandler(this, &FormEnd::FormEnd_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &FormEnd::FormEnd_Paint);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		void FormEnd_Load(System::Object^ sender, System::EventArgs^ e) {
			Graphics^ g = this->CreateGraphics();

			// Cambia el texto del Label según el estado
			if (End == "win") {
				this->lbGanador->Text = "¡VICTORIA!";
				this->lbGanador->Font = gcnew System::Drawing::Font("Courier New", 28, FontStyle::Bold); // Tamaño 28, Negrita, monoespaciada
				this->lbGanador->ForeColor = System::Drawing::Color::Lime; // Verde neón para un estilo ganador
			}
			else if (End == "lose") {
				this->lbGanador->Text = "DERROTA";
				this->lbGanador->Font = gcnew System::Drawing::Font("Courier New", 28, FontStyle::Bold);
				this->lbGanador->ForeColor = System::Drawing::Color::DarkRed; // Rojo oscuro para indicar pérdida
			}

			// Activa AutoSize para ajustar el tamaño del Label al texto
			this->lbGanador->AutoSize = true;

			// Actualiza el diseño para obtener el tamaño correcto
			this->lbGanador->PerformLayout();

			// Calcula la posición para centrar el Label en el formulario
			int x = (g->VisibleClipBounds.Width - this->lbGanador->Width) / 2;
			int y = (g->VisibleClipBounds.Height - this->lbGanador->Height) / 5;

			// Asigna la posición calculada
			this->lbGanador->Location = System::Drawing::Point(x, y);
		}

		void FormEnd_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
			Bitmap^ estado;
			Graphics^ g = e->Graphics;
			if (End == "win") {
				estado = images[1];
			}
			else if (End == "lose") {
				estado = images[0];
			}
			int width = 160;
			int height = 160;
			int x = (g->VisibleClipBounds.Width - width) / 2;
			int y = (g->VisibleClipBounds.Height - height) / 2 + 30;
			g->DrawImage(estado, x, y, width, height);
		}
	};
}
