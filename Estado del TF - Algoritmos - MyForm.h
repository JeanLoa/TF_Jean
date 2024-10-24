#pragma once
#include "Windows.h"
#include "Clases.h"

namespace TF {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	/// <summary>
	/// Resumen de MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			LoadBullets();
			LoadFloors();
			LoadAllies();
			LoadHero();
			LoadWorlds();
			LoadPortals();
			LoadMessage();
			LoadEnemies();
			this->KeyPreview = true;
			this->Focus();


			this->SetStyle(System::Windows::Forms::ControlStyles::UserPaint, true);
			this->SetStyle(System::Windows::Forms::ControlStyles::AllPaintingInWmPaint, true);
			this->SetStyle(System::Windows::Forms::ControlStyles::OptimizedDoubleBuffer, true);
			this->UpdateStyles();
			//
			//TODO: agregar código de constructor aquí
			//
		}

		void LoadBullets() {
			imagesBala = gcnew array<Bitmap^>(6) {
					gcnew Bitmap("Imagenes\\Bala\\BalaRight1.png"),
					gcnew Bitmap("Imagenes\\Bala\\BalaRight2.png"),
					gcnew Bitmap("Imagenes\\Bala\\BalaRight3.png"),
					gcnew Bitmap("Imagenes\\Bala\\BalaLeft1.png"),
					gcnew Bitmap("Imagenes\\Bala\\BalaLeft2.png"),
					gcnew Bitmap("Imagenes\\Bala\\BalaLeft3.png")
			};
		}

		void LoadAllies() {
			array<Bitmap^>^ images = gcnew array<Bitmap^>(4) {
				gcnew Bitmap("Imagenes\\Aliado\\AllieRight1.png"),
				gcnew Bitmap("Imagenes\\Aliado\\AllieRight2.png"),
				gcnew Bitmap("Imagenes\\Aliado\\AllieLeft1.png"),
				gcnew Bitmap("Imagenes\\Aliado\\AllieLeft2.png")
			};
			aliados_1 = gcnew Aliados;
			generarAliados(aliados_1, images);
			aliados_2 = gcnew Aliados;
			generarAliados(aliados_2, images);
			aliados_3 = gcnew Aliados;
			generarAliados(aliados_2, images);
			aliados_4 = gcnew Aliados;
			generarAliados(aliados_2, images);
		}
		void generarAliados(Aliados^ allies, cli::array<Bitmap^>^ imgs) {
			Graphics^ g = this->CreateGraphics();
			for (int i = 0; i < 3; ++i) {
				allies->agregarSprite(gcnew Aliado((g->VisibleClipBounds.Width / 3) * (i + 0.5), defaultFloorY, 0, 80, 80, imgs));
			}
		}
		void LoadEnemies() {
			array<Bitmap^>^ images = gcnew array<Bitmap^>(8) {
				gcnew Bitmap("Imagenes\\Enemigo\\EnemyDefaultRight1.png"),
				gcnew Bitmap("Imagenes\\Enemigo\\EnemyDefaultLeft1.png"),
				gcnew Bitmap("Imagenes\\Enemigo\\EnemyRunRight1.png"),
				gcnew Bitmap("Imagenes\\Enemigo\\EnemyRunRight2.png"),
				gcnew Bitmap("Imagenes\\Enemigo\\EnemyRunRight3.png"),
				gcnew Bitmap("Imagenes\\Enemigo\\EnemyRunLeft1.png"),
				gcnew Bitmap("Imagenes\\Enemigo\\EnemyRunLeft2.png"),
				gcnew Bitmap("Imagenes\\Enemigo\\EnemyRunLeft3.png")
			};

			enemigos_1 = gcnew Enemigos;
			generarEnemigos(enemigos_1, images, suelos_1);
			
			enemigos_2 = gcnew Enemigos;
			generarEnemigos(enemigos_2, images, suelos_2);

			enemigos_3 = gcnew Enemigos;
			generarEnemigos(enemigos_3, images, suelos_3);

			enemigos_4 = gcnew Enemigos;
			generarEnemigos(enemigos_4, images, suelos_4);
			
		}

		void generarEnemigos(Enemigos^ enemies, cli::array<Bitmap^>^ images, Suelos^ suelos) {
			List<int>^ indexWarning = gcnew List<int>();
			for (int i = 0; i < 10; ++i) {
				if (i < 8) {
					int index;
					do {
						index = randnum(0, suelos->getN() - 1);
					} while (indexWarning->Contains(index));
					indexWarning->Add(index);
					int width = suelos->getSuelo(index)->getWidth();
					int x = suelos->getSuelo(index)->getX() + width / 2 - margendeErrorX * 2;
					int y = suelos->getSuelo(index)->getY() - margendeErrorY * 5;
					enemies->agregarEnemigo(gcnew Enemigo(x, y, randDX(), 80, 80, images));
				}
				else {
					enemies->agregarEnemigo(gcnew Enemigo(200 * randnum(1, 5), defaultFloorY, randDX(), 80, 80, images));
				}
			}
		}

		void LoadFloors() {
			// Aumentar el ancho mas 50 y la altura mas 10 por imprecisiones del formulario
			suelos_1 = gcnew Suelos;
			suelos_1->agregarSuelo(gcnew Suelo(175, 522, 213, 35));
			suelos_1->agregarSuelo(gcnew Suelo(437, 457, 214, 35));
			suelos_1->agregarSuelo(gcnew Suelo(175, 298, 241, 35));
			suelos_1->agregarSuelo(gcnew Suelo(218, 171, 212, 35));
			suelos_1->agregarSuelo(gcnew Suelo(474, 205, 213, 35));
			suelos_1->agregarSuelo(gcnew Suelo(688, 544, 131, 35));
			suelos_1->agregarSuelo(gcnew Suelo(679, 352, 187, 35));
			suelos_1->agregarSuelo(gcnew Suelo(762, 156, 158, 35));
			suelos_1->agregarSuelo(gcnew Suelo(922, 271, 131, 35));
			suelos_1->agregarSuelo(gcnew Suelo(850, 422, 266, 35));
			suelos_1->agregarSuelo(gcnew Suelo(1091, 189, 186, 35));
			suelos_1->agregarSuelo(gcnew Suelo(1126, 326, 242, 35));
			suelos_1->agregarSuelo(gcnew Suelo(1141, 490, 214, 35));
			suelos_1->agregarSuelo(gcnew Suelo(1334, 550, 131, 35));

			suelos_2 = gcnew Suelos;
			suelos_2->agregarSuelo(gcnew Suelo(159, 548, 230, 35));
			suelos_2->agregarSuelo(gcnew Suelo(146, 378, 306, 35));
			suelos_2->agregarSuelo(gcnew Suelo(126, 175, 179, 35));
			suelos_2->agregarSuelo(gcnew Suelo(349, 250, 204, 35));
			suelos_2->agregarSuelo(gcnew Suelo(590, 134, 230, 35));
			suelos_2->agregarSuelo(gcnew Suelo(600, 311, 281, 35));
			suelos_2->agregarSuelo(gcnew Suelo(510, 507, 265, 35));
			suelos_2->agregarSuelo(gcnew Suelo(900, 204, 230, 35));
			suelos_2->agregarSuelo(gcnew Suelo(873, 428, 201, 35));
			suelos_2->agregarSuelo(gcnew Suelo(1258, 127, 230, 35));
			suelos_2->agregarSuelo(gcnew Suelo(1148, 354, 228, 35));
			suelos_2->agregarSuelo(gcnew Suelo(1092, 539, 253, 35));

			suelos_3 = gcnew Suelos;
			suelos_3->agregarSuelo(gcnew Suelo(131, 372, 241, 35));
			suelos_3->agregarSuelo(gcnew Suelo(239, 207, 214, 35));
			suelos_3->agregarSuelo(gcnew Suelo(347, 529, 294, 35));
			suelos_3->agregarSuelo(gcnew Suelo(457, 326, 213, 35));
			suelos_3->agregarSuelo(gcnew Suelo(542, 124, 239, 35));
			suelos_3->agregarSuelo(gcnew Suelo(684, 406, 269, 35));
			suelos_3->agregarSuelo(gcnew Suelo(864, 211, 241, 35));
			suelos_3->agregarSuelo(gcnew Suelo(840, 560, 185, 35));
			suelos_3->agregarSuelo(gcnew Suelo(1084, 497, 187, 35));
			suelos_3->agregarSuelo(gcnew Suelo(1147, 318, 239, 35));

			suelos_4 = gcnew Suelos;
			suelos_4->agregarSuelo(gcnew Suelo(139, 151, 255, 35));
			suelos_4->agregarSuelo(gcnew Suelo(192, 345, 204, 35));
			suelos_4->agregarSuelo(gcnew Suelo(373, 486, 203, 35));
			suelos_4->agregarSuelo(gcnew Suelo(447, 264, 204, 35));
			suelos_4->agregarSuelo(gcnew Suelo(700, 423, 178, 35));
			suelos_4->agregarSuelo(gcnew Suelo(907, 234, 230, 35));
			suelos_4->agregarSuelo(gcnew Suelo(1126, 314, 101, 35));
			suelos_4->agregarSuelo(gcnew Suelo(994, 497, 230, 35));
			suelos_4->agregarSuelo(gcnew Suelo(1268, 182, 204, 35));
			suelos_4->agregarSuelo(gcnew Suelo(1248, 385, 152, 35));

			suelos_5 = gcnew Suelos;
		}
		void LoadPortals() {
			// Aumentar el ancho mas 50 y la altura mas 10 por imprecisiones del formulario
			portal_1_f = gcnew Portal(1182, 370, 80, 120, gcnew array<Image^>(1) {
					Image::FromFile("Imagenes\\Portales\\Portal1.jpg")
			});
			portal_2_f = gcnew Portal(357, 70, 140, 180, gcnew array<Image^>(4) {
					Image::FromFile("Imagenes\\Portales\\Portal2_0.jpg"),
					Image::FromFile("Imagenes\\Portales\\Portal2_1.jpg"),
					Image::FromFile("Imagenes\\Portales\\Portal2_2.jpg"),
					Image::FromFile("Imagenes\\Portales\\Portal2_3.jpg")
			});
			portal_3_f = gcnew Portal(1182, 140, 140, 180, gcnew array<Image^>(4) {
					Image::FromFile("Imagenes\\Portales\\Portal3_0.jpg"),
					Image::FromFile("Imagenes\\Portales\\Portal3_1.jpg"),
					Image::FromFile("Imagenes\\Portales\\Portal3_2.jpg"),
					Image::FromFile("Imagenes\\Portales\\Portal3_3.jpg")
			});
			portal_4_f = gcnew Portal(172, 179, 196, 166, gcnew array<Image^>(4) {
					Image::FromFile("Imagenes\\Portales\\Portal4_0.png"),
					Image::FromFile("Imagenes\\Portales\\Portal4_1.png"),
					Image::FromFile("Imagenes\\Portales\\Portal4_2.png"),
					Image::FromFile("Imagenes\\Portales\\Portal4_3.png")
			});
			//portal_5_f = gcnew Portal();

			portal_2_b = gcnew Portal(1330, 515, 80, 120, gcnew array<Image^>(1) {
					Image::FromFile("Imagenes\\Portales\\Portal1.jpg")
			});
			portal_3_b = gcnew Portal(160, 455, 140, 180, gcnew array<Image^>(4) {
					Image::FromFile("Imagenes\\Portales\\Portal2_0.jpg"),
					Image::FromFile("Imagenes\\Portales\\Portal2_1.jpg"),
					Image::FromFile("Imagenes\\Portales\\Portal2_2.jpg"),
					Image::FromFile("Imagenes\\Portales\\Portal2_3.jpg")
			});
			portal_4_b = gcnew Portal(1330, 455, 140, 180, gcnew array<Image^>(4) {
					Image::FromFile("Imagenes\\Portales\\Portal3_0.jpg"),
					Image::FromFile("Imagenes\\Portales\\Portal3_1.jpg"),
					Image::FromFile("Imagenes\\Portales\\Portal3_2.jpg"),
					Image::FromFile("Imagenes\\Portales\\Portal3_3.jpg")
			});
			//portal_5_b = gcnew Portal();
		}
		void LoadWorlds() {
			Graphics^ g = this->CreateGraphics();
			mundo_1 = gcnew Mundo(0, 0, g->VisibleClipBounds.Width, g->VisibleClipBounds.Height, gcnew array<Image^>(1) {
					Image::FromFile("Imagenes\\Mundos\\Mundo1.jpg")
			});
			mundo_2 = gcnew Mundo(0, 0, g->VisibleClipBounds.Width, g->VisibleClipBounds.Height, gcnew array<Image^>(1) {
					Image::FromFile("Imagenes\\Mundos\\Mundo2.jpg")
			});
			mundo_3 = gcnew Mundo(0, 0, g->VisibleClipBounds.Width, g->VisibleClipBounds.Height, gcnew array<Image^>(2) {
					Image::FromFile("Imagenes\\Mundos\\Mundo3_0.jpg"),
					Image::FromFile("Imagenes\\Mundos\\Mundo3_1.jpg")
			});
			mundo_4 = gcnew Mundo(0, 0, g->VisibleClipBounds.Width, g->VisibleClipBounds.Height, gcnew array<Image^>(3) {
					Image::FromFile("Imagenes\\Mundos\\Mundo4_0.jpg"),
					Image::FromFile("Imagenes\\Mundos\\Mundo4_1.jpg"),
					Image::FromFile("Imagenes\\Mundos\\Mundo4_2.jpg")
			});
			mundo_5 = gcnew Mundo(0, 0, g->VisibleClipBounds.Width, g->VisibleClipBounds.Height, gcnew array<Image^>(5) {
					Image::FromFile("Imagenes\\Mundos\\Mundo4_0.jpg"),
					Image::FromFile("Imagenes\\Mundos\\Mundo4_1.jpg"),
					Image::FromFile("Imagenes\\Mundos\\Mundo4_2.jpg"),
			});
		}
		void LoadHero() {
			sprites = gcnew array<Bitmap^>(42);

			// Carga cada sprite desde su ubicación
			sprites[0] = gcnew Bitmap("Imagenes\\Sprites\\Run\\SpriteDefaultRight1.png");
			sprites[1] = gcnew Bitmap("Imagenes\\Sprites\\Run\\SpriteDefaultRight2.png");
			sprites[2] = gcnew Bitmap("Imagenes\\Sprites\\Run\\SpriteDefaultLeft1.png");
			sprites[3] = gcnew Bitmap("Imagenes\\Sprites\\Run\\SpriteDefaultLeft2.png");

			sprites[4] = gcnew Bitmap("Imagenes\\Sprites\\Run\\SpriteRunRight1.png");
			sprites[5] = gcnew Bitmap("Imagenes\\Sprites\\Run\\SpriteRunRight2.png");
			sprites[6] = gcnew Bitmap("Imagenes\\Sprites\\Run\\SpriteRunRight3.png");

			sprites[7] = gcnew Bitmap("Imagenes\\Sprites\\Run\\SpriteRunLeft1.png");
			sprites[8] = gcnew Bitmap("Imagenes\\Sprites\\Run\\SpriteRunLeft2.png");
			sprites[9] = gcnew Bitmap("Imagenes\\Sprites\\Run\\SpriteRunLeft3.png");

			sprites[10] = gcnew Bitmap("Imagenes\\Sprites\\Jump\\SpriteJumpRight1.png");
			sprites[11] = gcnew Bitmap("Imagenes\\Sprites\\Jump\\SpriteJumpRight2.png");
			sprites[12] = gcnew Bitmap("Imagenes\\Sprites\\Jump\\SpriteJumpLeft1.png");
			sprites[13] = gcnew Bitmap("Imagenes\\Sprites\\Jump\\SpriteJumpLeft2.png");

			sprites[14] = gcnew Bitmap("Imagenes\\Sprites\\Fall\\SpriteFallRight1.png");
			sprites[15] = gcnew Bitmap("Imagenes\\Sprites\\Fall\\SpriteFallRight2.png");
			sprites[16] = gcnew Bitmap("Imagenes\\Sprites\\Fall\\SpriteFallLeft1.png");
			sprites[17] = gcnew Bitmap("Imagenes\\Sprites\\Fall\\SpriteFallLeft1.png");

			sprites[18] = gcnew Bitmap("Imagenes\\Sprites\\Attack\\SpritePunchRight1.png");
			sprites[19] = gcnew Bitmap("Imagenes\\Sprites\\Attack\\SpritePunchRight2.png");
			sprites[20] = gcnew Bitmap("Imagenes\\Sprites\\Attack\\SpritePunchRight3.png");
			sprites[21] = gcnew Bitmap("Imagenes\\Sprites\\Attack\\SpritePunchRight4.png");

			sprites[22] = gcnew Bitmap("Imagenes\\Sprites\\Attack\\SpritePunchLeft1.png");
			sprites[23] = gcnew Bitmap("Imagenes\\Sprites\\Attack\\SpritePunchLeft2.png");
			sprites[24] = gcnew Bitmap("Imagenes\\Sprites\\Attack\\SpritePunchLeft3.png");
			sprites[25] = gcnew Bitmap("Imagenes\\Sprites\\Attack\\SpritePunchLeft4.png");

			sprites[26] = gcnew Bitmap("Imagenes\\Sprites\\Attack\\SpriteShootRight1.png");
			sprites[27] = gcnew Bitmap("Imagenes\\Sprites\\Attack\\SpriteShootLeft1.png");

			sprites[28] = gcnew Bitmap("Imagenes\\Sprites\\Slide\\SpriteSlidingRight1.png");
			sprites[29] = gcnew Bitmap("Imagenes\\Sprites\\Slide\\SpriteSlidingLeft1.png");

			sprites[30] = gcnew Bitmap("Imagenes\\Sprites\\Run\\LimSpriteRunningRight1.png");
			sprites[31] = gcnew Bitmap("Imagenes\\Sprites\\Run\\LimSpriteRunningLeft1.png");

			sprites[32] = gcnew Bitmap("Imagenes\\Sprites\\Fall\\LimSpriteFallingRight1.png");
			sprites[33] = gcnew Bitmap("Imagenes\\Sprites\\Fall\\LimSpriteFallingLeft1.png");

			sprites[34] = gcnew Bitmap("Imagenes\\Sprites\\Events\\SpriteJoining1.png");
			sprites[35] = gcnew Bitmap("Imagenes\\Sprites\\Events\\SpriteLeaving1.png");

			sprites[36] = gcnew Bitmap("Imagenes\\Sprites\\Events\\SpriteDeadRight1.png");
			sprites[37] = gcnew Bitmap("Imagenes\\Sprites\\Events\\SpriteDeadRight2.png");
			sprites[36] = gcnew Bitmap("Imagenes\\Sprites\\Events\\SpriteDeadRight3.png");

			sprites[37] = gcnew Bitmap("Imagenes\\Sprites\\Events\\SpriteDeadLeft1.png");
			sprites[38] = gcnew Bitmap("Imagenes\\Sprites\\Events\\SpriteDeadLeft2.png");
			sprites[39] = gcnew Bitmap("Imagenes\\Sprites\\Events\\SpriteDeadLeft3.png");

			sprites[40] = gcnew Bitmap("Imagenes\\Sprites\\Events\\SpriteWin1.png");
			sprites[41] = gcnew Bitmap("Imagenes\\Sprites\\Events\\SpriteWin2.png");

			hero = gcnew Heroe(100, 570 - margendeErrorY, 10, 80, 80, sprites);
		}
		void LoadMessage() {
			messages_f = gcnew array<Image^>(2) {
					Image::FromFile("Imagenes\\Mensajes\\Mensaje1_0.png"),
					Image::FromFile("Imagenes\\Mensajes\\Mensaje1_1.png")
			};
			messages_b = gcnew array<Image^>(2) {
					Image::FromFile("Imagenes\\Mensajes\\Mensaje2_0.png"),
					Image::FromFile("Imagenes\\Mensajes\\Mensaje2_1.png")
			};
		}
	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~MyForm()
		{
			if (components) {
				delete components;
			}
			for (int i = 0; i < sprites->Length; i++) {
				delete sprites[i];
			}
		}
	private: System::ComponentModel::IContainer^ components;
	protected:

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>
		array<Bitmap^>^ sprites; // Arreglo para almacenar tus sprites
	private:

		System::Windows::Forms::Timer^ Timer;
		// Auxiliar
		float lapse = 0.0f;
		// Sprite
		Heroe^ hero;
		int heroIndex = 0;
		// Determina el rango de índices de los sprites
		int startIndex = 0; // Índice inicial del sprite actual
		int endIndex = 1;   // Índice final para el ciclo de sprites
		// Movimientos
		bool sliding = false;
		float slideStrength = 20.0f;
		float slideSpeed;
		bool running = true;
		bool movingLeft = false;
		bool movingRight = false;
		// Salto y caida
		bool jumping = false;
		bool falling = false;
		float jumpStrength = 40.0f;
		float gravity = 5.0f;
		float aceleration = 2.0f;
		float jumpSpeed;
		// Ataques
		bool punching = false;
		bool punchingStarted = false;
		bool shooting = false;
		// Daño
		bool beingAttacked = false;
		bool attacking = false;
		int enemigoAtacado = -1;
		// Suelos
		int defaultFloorY = 570;

		int margendeErrorY = 20;
		int margendeErrorX = 35;

		String^ lastMove = "";

		Portal^ portal_1_f;
		Portal^ portal_2_f;
		Portal^ portal_3_f;
		Portal^ portal_4_f;
		Portal^ portal_5_f;

		Portal^ portal_1_b;
		Portal^ portal_2_b;
		Portal^ portal_3_b;
		Portal^ portal_4_b;
		Portal^ portal_5_b;
						 
		int imagePortalIndex_f = 0;
		int imagePortalStartIndex_f = 0;
		int imagePortalEndIndex_f = 0;

		int imagePortalIndex_b = 0;
		int imagePortalStartIndex_b = 0;
		int imagePortalEndIndex_b = 0;

		Aliados^ aliados_1;
		Aliados^ aliados_2;
		Aliados^ aliados_3;
		Aliados^ aliados_4;
		Aliados^ aliados_5;
		Aliados^ aliadosActuales;

		Recursos^ recursos_1;
		Recursos^ recursos_2;
		Recursos^ recursos_3;
		Recursos^ recursos_4;
		Recursos^ recursosActuales;

		Suelos^ suelos_1;
		Suelos^ suelos_2;
		Suelos^ suelos_3;
		Suelos^ suelos_4;
		Suelos^ suelos_5;
		Suelos^ suelosActuales;

		Enemigos^ enemigos_1;
		Enemigos^ enemigos_2;
		Enemigos^ enemigos_3;
		Enemigos^ enemigos_4;
		Enemigos^ enemigos_5;
		Enemigos^ enemigosActuales;

		Mundo^ mundo_1;
		Mundo^ mundo_2;
		Mundo^ mundo_3;
		Mundo^ mundo_4;
		Mundo^ mundo_5;
		Mundo^ mundo_victoria;

		bool val_mundo_1 = true;
		bool val_mundo_2 = false;
		bool val_mundo_3 = false;
		bool val_mundo_4 = true;
		bool val_mundo_5 = false;
		bool val_mundo_victoria = false;

		int prevX_1;
		int prevY_1;

		int prevX_2;
		int prevY_2;

		int prevX_3;
		int prevY_3;

		int prevX_4;
		int prevY_4;

		int imageWorldIndex = 0;
		int imageWorldStartIndex = 0;
		int imageWorldEndIndex = 0;

		bool readyToTravelForward = false;
		bool readyToTravelBackward = false;
		bool joining = false;
		bool leaving = false;

		array<Image^>^ messages_b;
		array<Image^>^ messages_f;
		int messageIndex = 0;
		
		array<Bitmap^>^ imagesBala;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
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
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(773, 409);
			this->DoubleBuffered = true;
			this->Name = L"MyForm";
			this->Text = L"Juego";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyUp);
			this->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MyForm_MouseClick);
			this->ResumeLayout(false);
		}
#pragma endregion
		void MyForm_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
			Graphics^ g = e->Graphics;

			Mundo^ mundoActual;
			Portal^ portalActual_f;
			Portal^ portalActual_b;

			if (val_mundo_1) {
				mundoActual = mundo_1;
				portalActual_f = portal_1_f;
				portalActual_b = nullptr;
				enemigosActuales = enemigos_1;
				aliadosActuales = aliados_1;

				imageWorldStartIndex = 0;
				imageWorldEndIndex = 0;

				imagePortalStartIndex_f = 0;
				imagePortalEndIndex_f = 0;
			}
			else if (val_mundo_2) {
				mundoActual = mundo_2;
				portalActual_f = portal_2_f;
				portalActual_b = portal_2_b;
				enemigosActuales = enemigos_2;
				aliadosActuales = aliados_2;
				
				imageWorldStartIndex = 0;
				imageWorldEndIndex = 0;
				
				imagePortalStartIndex_f = 0;
				imagePortalEndIndex_f = 3;

				imagePortalStartIndex_b = 0;
				imagePortalEndIndex_b = 0;
			}
			else if (val_mundo_3) {
				mundoActual = mundo_3;
				portalActual_f = portal_3_f;
				portalActual_b = portal_3_b;
				enemigosActuales = enemigos_3;
				aliadosActuales = aliados_3;

				imageWorldStartIndex = 0;
				imageWorldEndIndex = 1;

				imagePortalStartIndex_f = 0;
				imagePortalEndIndex_f = 3;

				imagePortalStartIndex_b = 0;
				imagePortalEndIndex_b = 3;
			}
			else if (val_mundo_4) {
				mundoActual = mundo_4;
				portalActual_f = portal_4_f;
				portalActual_b = portal_4_b;
				enemigosActuales = enemigos_4;
				aliadosActuales = aliados_4;

				imageWorldStartIndex = 0;
				imageWorldEndIndex = 2;

				imagePortalStartIndex_f = 0;
				imagePortalEndIndex_f = 3;

				imagePortalStartIndex_b = 0;
				imagePortalEndIndex_b = 3;
			}
			else if (val_mundo_5) {
				portalActual_f = nullptr;
				portalActual_b = portal_5_b;
				mundoActual = mundo_5;
				imageWorldStartIndex = 0;
				imageWorldEndIndex = 4;
			}
			if (mundoActual != nullptr) {
				System::Drawing::Imaging::ColorMatrix^ colorMatrix = gcnew System::Drawing::Imaging::ColorMatrix();
				colorMatrix->Matrix33 = 1.0f;

				System::Drawing::Imaging::ImageAttributes^ imageAttributes = gcnew System::Drawing::Imaging::ImageAttributes();
				imageAttributes->SetColorMatrix(colorMatrix, System::Drawing::Imaging::ColorMatrixFlag::Default, System::Drawing::Imaging::ColorAdjustType::Bitmap);

				System::Drawing::Rectangle destRect = System::Drawing::Rectangle(0, 0, this->ClientSize.Width, this->ClientSize.Height);
				e->Graphics->DrawImage(mundoActual->getImagenes()[imageWorldIndex], destRect, mundoActual->getX(), mundoActual->getY(), mundoActual->getImagenes()[imageWorldIndex]->Width, mundoActual->getImagenes()[imageWorldIndex]->Height, System::Drawing::GraphicsUnit::Pixel, imageAttributes);
				++imageWorldIndex;
				if (imageWorldIndex > imageWorldEndIndex) {
					imageWorldIndex = imageWorldStartIndex;
				}

				if (portalActual_f != nullptr) {

					portalActual_f->dibujarSprite(g, imagePortalIndex_f);
					++imagePortalIndex_f;
					if (imagePortalIndex_f > imagePortalEndIndex_f) {
						imagePortalIndex_f = imagePortalStartIndex_f;
					}

					if (hero->getY() + hero->getHeight() >= portalActual_f->getY() &&
						hero->getY() <= portalActual_f->getY() + portalActual_f->getHeight() &&
						hero->getX() + hero->getWidth() >= portalActual_f->getX() + margendeErrorX &&
						hero->getX() <= portalActual_f->getX() + portalActual_f->getWidth() - margendeErrorX) {
						readyToTravelForward = true;


						int mensajeAncho = messages_f[messageIndex]->Width;
						int mensajeAlto = messages_f[messageIndex]->Height;

						// Calcular la posición de la imagen centrada horizontalmente sobre el portal
						int mensajeX = portalActual_f->getX() + (portalActual_f->getWidth() / 2) - (mensajeAncho / 2);
						int mensajeY = portalActual_f->getY() - mensajeAlto; // Justo encima del portal
						g->DrawImage(messages_f[messageIndex], System::Drawing::Rectangle(mensajeX, mensajeY, mensajeAncho, mensajeAlto), 0, 0, mensajeAncho, mensajeAlto, GraphicsUnit::Pixel);
						++messageIndex;
						if (messageIndex > 1) {
							messageIndex = 0;
						}
					}
					else {
						readyToTravelForward = false;
					}
				}
				if (portalActual_b != nullptr) {

					portalActual_b->dibujarSprite(g, imagePortalIndex_b);
					++imagePortalIndex_b;
					if (imagePortalIndex_b > imagePortalEndIndex_b) {
						imagePortalIndex_b = imagePortalStartIndex_b;
					}

					if (hero->getY() + hero->getHeight() >= portalActual_b->getY() &&
						hero->getY() <= portalActual_b->getY() + portalActual_b->getHeight() &&
						hero->getX() + hero->getWidth() >= portalActual_b->getX() + margendeErrorX &&
						hero->getX() <= portalActual_b->getX() + portalActual_b->getWidth() - margendeErrorX) {
						readyToTravelBackward = true;


						int mensajeAncho = messages_b[messageIndex]->Width;
						int mensajeAlto = messages_b[messageIndex]->Height;

						// Calcular la posición de la imagen centrada horizontalmente sobre el portal
						int mensajeX = portalActual_b->getX() + (portalActual_b->getWidth() / 2) - (mensajeAncho / 2);
						int mensajeY = portalActual_b->getY() - mensajeAlto; // Justo encima del portal
						g->DrawImage(messages_b[messageIndex], System::Drawing::Rectangle(mensajeX, mensajeY, mensajeAncho, mensajeAlto), 0, 0, mensajeAncho, mensajeAlto, GraphicsUnit::Pixel);
						++messageIndex;
						if (messageIndex > 1) {
							messageIndex = 0;
						}
					}
					else {
						readyToTravelBackward = false;
					}
				}
			}
			if (enemigosActuales != nullptr) {
				for (int i = 0; i < enemigosActuales->getN(); ++i) {
					Enemigo^ enemigoActual = enemigosActuales->getEnemigo(i);
					enemigoActual->dibujarEnemigo(g);
					enemigoActual->setIndex(enemigoActual->getIndex() + 1);
					if (enemigoActual->getIndex() > enemigoActual->getEndIndex()) {
						enemigoActual->setIndex(enemigoActual->getStartIndex());
					}
				}
			}
			if (aliadosActuales != nullptr) {
				for (int i = 0; i < aliadosActuales->getN(); ++i) {
					Aliado^ aliadoActual = aliadosActuales->getSprite(i);
					aliadoActual->dibujarAliado(g);
					aliadoActual->setIndex(aliadoActual->getIndex() + 1);
					if (aliadoActual->getIndex() > aliadoActual->getEndIndex()) {
						aliadoActual->setIndex(aliadoActual->getStartIndex());
					}
				}
			}
			if (hero->getArma() != nullptr) {
				hero->disparar(g);
				for (int i = hero->getArma()->getN() - 1; i >= 0; --i) {
					Bala^ balaActual = hero->getArma()->getBala(i);
					int startIndex = balaActual->getStartIndex();
					int endIndex = balaActual->getEndIndex();
					int index = balaActual->getIndex();
					balaActual->setIndex(index + 1);
					if (balaActual->getIndex() > endIndex) {
						balaActual->setIndex(startIndex);
					}
					if (balaActual->getX() < 0 || balaActual->getX() + balaActual->getWidth() > g->VisibleClipBounds.Width) {
						hero->getArma()->eliminarBala(i);
					}
				}
			}
			if (hero != nullptr) {
				hero->dibujarSprite(g, heroIndex);
			}

		}
		void Timer_Tick(System::Object^ sender, System::EventArgs^ e) {

			Graphics^ g = this->CreateGraphics();

			if (val_mundo_1) {
				suelosActuales = suelos_1;
				enemigosActuales = enemigos_1;
			}
			else if (val_mundo_2) {
				suelosActuales = suelos_2;
				enemigosActuales = enemigos_2;
			}
			else if (val_mundo_3) {
				suelosActuales = suelos_3;
				enemigosActuales = enemigos_3;
			}
			else if (val_mundo_4) {
				suelosActuales = suelos_4;
				enemigosActuales = enemigos_4;
			}
			else if (val_mundo_5) {
				suelosActuales = suelos_5;
				enemigosActuales = enemigos_5;
			}

			
			
			for (int i = 0; i < enemigosActuales->getN(); ++i) {
				Enemigo^ enemigoActual = enemigosActuales->getEnemigo(i);

				for (int j = 0; j < suelosActuales->getN(); ++j) {
					Suelo^ sueloActual = suelosActuales->getSuelo(j);
					int sueloX = sueloActual->getX();
					int sueloY = sueloActual->getY();
					int sueloWidth = sueloActual->getWidth();
					int sueloHeight = sueloActual->getHeight();

					int pieSpriteY = enemigoActual->getY() + enemigoActual->getHeight() - margendeErrorY;

					if (pieSpriteY >= sueloY &&
						pieSpriteY <= sueloY + sueloHeight &&
						enemigoActual->getX() + enemigoActual->getWidth() >= sueloX + margendeErrorX &&
						enemigoActual->getX() <= sueloX + sueloWidth - margendeErrorX * 2) {
						enemigoActual->setFall(false);
						break;
					}
					else if (pieSpriteY > defaultFloorY + margendeErrorY * 2) {
						enemigoActual->setFall(false);
						break;
					}
					else {
						enemigoActual->setFall(true);
					}
				}
				if (enemigoActual->getFall() == true) {

					enemigoActual->setY(enemigoActual->getY() + enemigoActual->getGravity());
					enemigoActual->setGravity(enemigoActual->getGravity() + aceleration);
					if (enemigoActual->getY() + enemigoActual->getHeight() > defaultFloorY + margendeErrorY * 3) {

						enemigoActual->setY(defaultFloorY);
						enemigoActual->setFall(false);
						enemigoActual->setGravity(5);
					}

					for (int i = 0; i < suelosActuales->getN(); ++i) {
						Suelo^ sueloActual = suelosActuales->getSuelo(i);

						int sueloX = sueloActual->getX();
						int sueloY = sueloActual->getY();
						int sueloWidth = sueloActual->getWidth();
						int sueloHeight = sueloActual->getHeight();

						int pieSpriteY = enemigoActual->getY() + enemigoActual->getHeight() - margendeErrorY;

						if (pieSpriteY >= sueloY &&
							pieSpriteY <= sueloY + sueloHeight &&
							enemigoActual->getX() + enemigoActual->getWidth() >= sueloX + margendeErrorX &&
							enemigoActual->getX() <= sueloX + sueloWidth - margendeErrorX * 2) {

							enemigoActual->setY(sueloY - enemigoActual->getHeight() + margendeErrorY);
							enemigoActual->setFall(false);
							enemigoActual->setGravity(5);
						}
					}
				}


				if (enemigosActuales->getEnemigo(i)->getVidas() <= 0) {
					enemigosActuales->eliminarEnemigo(i);
				}

				bool colisionConSuelo = false;

				// Verificar colisiones con suelos
				for (int j = 0; j < suelosActuales->getN(); ++j) {
					Suelo^ sueloActual = suelosActuales->getSuelo(j);
					int sueloX = sueloActual->getX();
					int sueloY = sueloActual->getY();
					int sueloWidth = sueloActual->getWidth();
					int sueloHeight = sueloActual->getHeight();

					int pieSpriteY = enemigoActual->getY() + enemigoActual->getHeight() - margendeErrorY;

					if (pieSpriteY >= sueloY &&
						pieSpriteY <= sueloY + sueloHeight &&
						enemigoActual->getX() + enemigoActual->getWidth() >= sueloX + margendeErrorX * 2 &&
						enemigoActual->getX() <= sueloX + sueloWidth - margendeErrorX * 3.5 || enemigoActual->getY() == defaultFloorY) {
						colisionConSuelo = true;  // Está sobre un suelo
						break;  // Salir del bucle de suelos, ya que encontramos uno
					}
				}

				bool colisionConMapa = false;
				if (enemigoActual->getX() + enemigoActual->getWidth() > g->VisibleClipBounds.Width ||
					enemigoActual->getX() < 0) {
					colisionConMapa = true;
				}

				// Cambiar de dirección si NO está sobre ningún suelo o si colisiona con los límites del mapa
				if (!colisionConSuelo || colisionConMapa) {
					enemigoActual->setDX(enemigoActual->getDX() * -1);  // Cambiar de dirección
					enemigoActual->setIndex(enemigoActual->getStartIndex());  // Reiniciar índice de animación
				}

				// Actualizar la posición del enemigo
				enemigoActual->setX(enemigoActual->getX() + enemigoActual->getDX());
			}

			
			if (!falling) {
				for (int i = 0; i < suelosActuales->getN(); ++i) {
					Suelo^ sueloActual = suelosActuales->getSuelo(i);

					int sueloX = sueloActual->getX();
					int sueloY = sueloActual->getY();
					int sueloWidth = sueloActual->getWidth();
					int sueloHeight = sueloActual->getHeight();

					int pieSpriteY = hero->getY() + hero->getHeight() - margendeErrorY;

					if (pieSpriteY >= sueloY &&
						pieSpriteY <= sueloY + sueloHeight &&
						hero->getX() + hero->getWidth() >= sueloX + margendeErrorX &&
						hero->getX() <= sueloX + sueloWidth - margendeErrorX * 2) {
						falling = false;
						break;
					}
					else if (pieSpriteY > defaultFloorY + margendeErrorY * 2) {
						falling = false;
						break;
					}
					else {
						falling = true;
					}
				}
			}
			// Actualiza la posición del sprite al moverse
			if (sliding) {
				if (lastMove == "right" || movingRight) {
					hero->setX(hero->getX() + slideSpeed);
					lastMove = "right";  // Guarda la última dirección
				}
				else if (lastMove == "left" || movingLeft) {
					hero->setX(hero->getX() - slideSpeed);
					lastMove = "left";  // Guarda la última dirección
				}
				slideSpeed *= 0.95;
				if (hero->getX() < 0) {
					hero->setX(0);
				}
				else if (hero->getX() + hero->getWidth() > g->VisibleClipBounds.Width) {
					hero->setX(g->VisibleClipBounds.Width - hero->getWidth());
				}
			}
			if (running || jumping || falling) {
				joining = false;
				if (movingRight) {
					hero->setX(hero->getX() + hero->getDX());
					lastMove = "right";  // Guarda la última dirección
				}
				else if (movingLeft) {
					hero->setX(hero->getX() - hero->getDX());
					lastMove = "left";  // Guarda la última dirección
				}
				if (hero->getX() < 0) {
					hero->setX(0);
				}
				else if (hero->getX() + hero->getWidth() > g->VisibleClipBounds.Width) {
					hero->setX(g->VisibleClipBounds.Width - hero->getWidth());
				}
			}

			if (running) {
				if (movingRight) {
					startIndex = 4; // Primer sprite de movimiento a la derecha
					endIndex = 6;   // Último sprite de movimiento a la derecha
				}
				else if (movingLeft) {
					startIndex = 7; // Primer sprite de movimiento a la izquierda
					endIndex = 9;   // Último sprite de movimiento a la izquierda
				}
				else { // Si no se está moviendo
					if (lastMove == "right") {
						startIndex = 0; // Último sprite estático mirando a la derecha
						endIndex = 1;   // Mantener el mismo sprite
					}
					else if (lastMove == "left") {
						startIndex = 2; // Último sprite estático mirando a la izquierda
						endIndex = 3;   // Mantener el mismo sprite
					}
				}
				heroIndex++;
				if (heroIndex > endIndex) {
					heroIndex = startIndex;
				}
				if (hero->getX() == 0) {
					heroIndex = 31;
				}
				else if (hero->getX() + hero->getWidth() == g->VisibleClipBounds.Width) {
					heroIndex = 30;
				}
			}

			if (jumping) {
				punching = false;
				shooting = false;
				running = false;
				if (jumpSpeed > 0) {
					// Mostrar el sprite inicial de salto
					if (jumpSpeed == jumpStrength) {
						if (lastMove == "right" || movingRight) {
							heroIndex = 10;
						}
						else if (lastMove == "left" || movingLeft) {
							heroIndex = 12;
						}
						jumpSpeed -= gravity;
					}
					else {
						// Mantener el sprite de estar en el aire
						if (lastMove == "right" || movingRight) {
							heroIndex = 11;
						}
						else if (lastMove == "left" || movingLeft) {
							heroIndex = 13;
						}
						hero->setY(hero->getY() - jumpSpeed);
						jumpSpeed -= gravity;
					}
					// Colisión con la parte superior
					if (hero->getY() < 22) {
						hero->setY(22);
						jumping = false;
						falling = true;
						jumpSpeed = 0;
					}
				}
				else {
					jumping = false;
					falling = true;
					jumpSpeed = 0;
				}
			}
			else if (falling) {
				punching = false;
				shooting = false;
				if (lastMove == "right" || movingRight) {
					heroIndex = 14;
				}
				else if (lastMove == "left" || movingLeft) {
					heroIndex = 16;
				}

				if (hero->getX() == 0) {
					heroIndex = 33;
				}
				else if (hero->getX() + hero->getWidth() == g->VisibleClipBounds.Width) {
					heroIndex = 32;
				}

				hero->setY(hero->getY() + gravity);
				gravity += aceleration;
				if (hero->getY() + hero->getHeight() > defaultFloorY + margendeErrorY * 3) {
					if (lastMove == "right" || movingRight) {
						heroIndex = 15;
					}
					else if (lastMove == "left" || movingLeft) {
						heroIndex = 17;
					}

					hero->setY(defaultFloorY);
					falling = false;
					running = true;
					gravity = 5;
				}

				for (int i = 0; i < suelosActuales->getN(); ++i) {
					Suelo^ sueloActual = suelosActuales->getSuelo(i);

					int sueloX = sueloActual->getX();
					int sueloY = sueloActual->getY();
					int sueloWidth = sueloActual->getWidth();
					int sueloHeight = sueloActual->getHeight();

					int pieSpriteY = hero->getY() + hero->getHeight() - margendeErrorY;

					if (pieSpriteY >= sueloY &&
						pieSpriteY <= sueloY + sueloHeight &&
						hero->getX() + hero->getWidth() >= sueloX + margendeErrorX &&
						hero->getX() <= sueloX + sueloWidth - margendeErrorX * 2) {

						hero->setY(sueloY - hero->getHeight() + margendeErrorY);
						falling = false;
						running = true;
						gravity = 5;
					}
				}
			}
			if (sliding) {
				lapse += 0.1;
				if (lastMove == "right" || movingRight) {
					heroIndex = 28;
				}
				else if (lastMove == "left" || movingLeft) {
					heroIndex = 29;
				}
				if (lapse > 1.5) {
					running = true;
					sliding = false;
					lapse = 0;
				}
			}

			if (punching) {
				running = false;
				if (!punchingStarted) {
					if (lastMove == "right") {
						startIndex = 18;
						endIndex = 21;
					}
					else if (lastMove == "left") {
						startIndex = 22;
						endIndex = 25;
					}
					heroIndex = startIndex;
					punchingStarted = true;
				}
				else if (punchingStarted) {
					heroIndex++;
					if (heroIndex > endIndex) {
						heroIndex = startIndex;
						for (int i = 0; i < enemigosActuales->getN(); ++i) {
							Enemigo^ enemigoActual = enemigosActuales->getEnemigo(i);
							int width_Enemy = enemigoActual->getWidth();
							int height_Enemy = enemigoActual->getHeight();
							int x_Enemy = enemigoActual->getX() + width_Enemy / 2;
							int y_Enemy = enemigoActual->getY() + height_Enemy / 2;

							// Posición del héroe y área de golpe
							int x_Hero = hero->getX();
							int y_Hero = hero->getY();
							int width_Hero = hero->getWidth();
							int height_Hero = hero->getHeight();
							int rangePunch = 80;
							if (y_Enemy > y_Hero && y_Enemy < y_Hero + width_Hero) {
								if (lastMove == "right") {
									if (x_Enemy <= (x_Hero + (width_Hero / 2) + rangePunch) && x_Enemy >= x_Hero + width_Hero / 2) {
										enemigoActual->setPunched(true);
										enemigosActuales->getEnemigo(i)->setVidas(enemigoActual->getVidas() - 60);
									}
								}
								else if (lastMove == "left") {
									if (x_Enemy >= (x_Hero + (width_Hero / 2) - rangePunch) && x_Enemy <= x_Hero + width_Hero / 2) {
										enemigoActual->setPunched(true);
										enemigosActuales->getEnemigo(i)->setVidas(enemigoActual->getVidas() - 60);
									}
								}
							}
						}
					}
				}
			}

			if (shooting) {
				running = false;
				if (lastMove == "right") {
					heroIndex = 26;
				}
				else if (lastMove == "left") {
					heroIndex = 27;
				}
			}


			if (joining) {
				heroIndex = 35;
			}

			for (int i = 0; i < enemigosActuales->getN(); ++i) {
				for (int j = 0; j < hero->getArma()->getN(); ++j) {
					Bala^ bala = hero->getArma()->getBala(j);
					int x_Bala = bala->getX();
					int y_Bala = bala->getY();
					int width_Bala = bala->getWidth();
					int height_Bala = bala->getHeight();
					Enemigo^ enemy = enemigosActuales->getEnemigo(i);
					int x_Enemy = enemy->getX();
					int y_Enemy = enemy->getY();
					int width_Enemy = enemy->getWidth();
					int height_Enemy = enemy->getHeight();

					int ajusteBalaX = width_Bala * 0.2;  // Ajustar el 20% del ancho de la bala
					int ajusteBalaY = height_Bala * 0.2; // Ajustar el 20% de la altura de la bala
					int ajusteEnemyX = width_Enemy * 0.2; // Ajustar el 20% del ancho del enemigo
					int ajusteEnemyY = height_Enemy * 0.2; // Ajustar el 20% de la altura del enemigo

					if (x_Bala + ajusteBalaX < x_Enemy + width_Enemy - ajusteEnemyX &&
						x_Bala + width_Bala - ajusteBalaX > x_Enemy + ajusteEnemyX &&
						y_Bala + ajusteBalaY < y_Enemy + height_Enemy - ajusteEnemyY &&
						y_Bala + height_Bala - ajusteBalaY > y_Enemy + ajusteEnemyY) {
						enemy->setShot(true);
						enemy->setVidas(enemy->getVidas() - 100);
						hero->getArma()->eliminarBala(j);
					}
				}
			}

			this->Invalidate();
		}

		void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
			Graphics^ g = this->CreateGraphics();
			if (punching || shooting) {
				return;
			}
			if (e->KeyCode == Keys::D) {
				running = true;
				if (!movingRight) {
					movingRight = true;
					movingLeft = false;
					heroIndex = 4;
				}
			}
			else if (e->KeyCode == Keys::A) {
				running = true;
				if (!movingLeft) {
					movingLeft = true;
					movingRight = false;
					heroIndex = 7;
				}
			}
			else if (e->KeyCode == Keys::Space && !jumping && !falling && !sliding) {
				joining = false;
				running = false;
				jumping = true;
				jumpSpeed = jumpStrength;
			}
			if (running) {
				if (e->KeyCode == Keys::R) {
					punching = false;
					shooting = false;
					running = false;
					jumping = false;
					sliding = true;
					slideSpeed = slideStrength;
				}
			}
			if (!running || !jumping || !falling || !sliding) {
				if (e->KeyCode == Keys::Q) {
					punching = true;
				}
				else if (hero->getMunicion() > 0) {
					if (e->KeyCode == Keys::E) {
						shooting = true;
					}
				}
			}
			if (readyToTravelForward) {
				if (e->KeyCode == Keys::G) {
					running = false;
					leaving = true;
					if (leaving) {
						heroIndex = 34;
						hero->dibujarSprite(g, heroIndex);
						leaving = false;
						joining = true;
						Sleep(200);
					}
					if (val_mundo_1) {
						prevX_1 = hero->getX();
						prevY_1 = hero->getY();
						hero->setX(1333);
						hero->setY(defaultFloorY);
						val_mundo_1 = false;
						val_mundo_2 = true;
					}
					else if (val_mundo_2) {
						prevX_2 = hero->getX();
						prevY_2 = hero->getY();
						hero->setX(190);
						hero->setY(defaultFloorY);
						val_mundo_2 = false;
						val_mundo_3 = true;
					}
					else if (val_mundo_3) {
						prevX_3 = hero->getX();
						prevY_3 = hero->getY();
						hero->setX(1364);
						hero->setY(defaultFloorY);
						val_mundo_3 = false;
						val_mundo_4 = true;
					}
					else if (val_mundo_4) {
						prevX_4 = hero->getX();
						prevY_4 = hero->getY();
						hero->setX(1364);
						hero->setY(defaultFloorY);
						val_mundo_4 = false;
						val_mundo_5 = true;
					}
					else if (val_mundo_5) {
						hero->setX(0);
						hero->setY(defaultFloorY);
						val_mundo_5 = false;
						val_mundo_victoria = true;
					}
					imagePortalIndex_b = 0;
					imagePortalIndex_f = 0;
					imageWorldIndex = 0;
					readyToTravelForward = false;
				}
			}
			else if (readyToTravelBackward) {
				if (e->KeyCode == Keys::T) {
					leaving = true;
					running = false;
					if (leaving) {
						heroIndex = 34;
						hero->dibujarSprite(g, heroIndex);
						leaving = false;
						joining = true;
						Sleep(200);
					}
					if (val_mundo_2) {
						
						val_mundo_2 = false;
						val_mundo_1 = true;

						imagePortalIndex_b = 0;
						imagePortalIndex_f = 0;

						hero->setX(prevX_1);
						hero->setY(prevY_1);
					}
					else if (val_mundo_3) {
						val_mundo_3 = false;
						val_mundo_2 = true;

						imagePortalIndex_b = 0;
						imagePortalIndex_f = 0;

						hero->setX(prevX_2);
						hero->setY(prevY_2);
					}
					else if (val_mundo_4) {
						val_mundo_4 = false;
						val_mundo_3 = true;

						imagePortalIndex_b = 0;
						imagePortalIndex_f = 0;

						hero->setX(prevX_3);
						hero->setY(prevY_3);
					}
					else if (val_mundo_5) {
						val_mundo_5 = false;
						val_mundo_4 = true;

						imagePortalIndex_b = 0;
						imagePortalIndex_f = 0;

						hero->setX(prevX_4);
						hero->setY(prevY_4);
					}
					imagePortalIndex_b = 0;
					imagePortalIndex_f = 0;
					imageWorldIndex = 0;
					readyToTravelBackward = false;
				}

			}
			
		}

		void MyForm_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
			if (e->KeyCode == Keys::D) {
				movingRight = false;
				lastMove = "right";
			}
			else if (e->KeyCode == Keys::A) {
				movingLeft = false;
				lastMove = "left";
			}
			else if (e->KeyCode == Keys::Q) {
				running = true;
				punching = false;
				punchingStarted = false;
			}
			else if (e->KeyCode == Keys::E) {
				running = true;
				if (shooting) {
					if (lastMove == "right") {
						heroIndex = 26;
						hero->getArma()->agregarBala(gcnew Bala(hero->getX() + hero->getWidth(), hero->getY(), 10, 20, 20, imagesBala));
					}
					else if (lastMove == "left") {
						heroIndex = 27;
						hero->getArma()->agregarBala(gcnew Bala(hero->getX() - 10, hero->getY(), -10, 20, 20, imagesBala));
					}
					hero->setMunicion(hero->getMunicion() - 1);
					shooting = false;
					Sleep(100);
				}
			}
		}
		void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {

		}
		void MyForm_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
			String^ x = e->X.ToString();
			String^ y = e->Y.ToString();
			MessageBox::Show("X: " + x + " Y: " + y);
		}
	};
}
