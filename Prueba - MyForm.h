#pragma once
#include "Windows.h"
#include "Clases.h"
#include "FormEnd.h"

namespace TF {
	using namespace System::Media;
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
	public ref class MyForm : public Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			LoadBoss();
			LoadMusics();
			LoadRecursos();
			LoadTempos();
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
		void LoadBoss() {
			Graphics^ g = this->CreateGraphics();
			array<Bitmap^>^ images = gcnew array<Bitmap^>(8) {
				gcnew Bitmap("Imagenes\\Boss\\BossRight1.png"),
					gcnew Bitmap("Imagenes\\Boss\\BossRight2.png"),
					gcnew Bitmap("Imagenes\\Boss\\BossRight3.png"),
					gcnew Bitmap("Imagenes\\Boss\\BossRight4.png"),
					gcnew Bitmap("Imagenes\\Boss\\BossLeft1.png"),
					gcnew Bitmap("Imagenes\\Boss\\BossLeft2.png"),
					gcnew Bitmap("Imagenes\\Boss\\BossLeft3.png"),
					gcnew Bitmap("Imagenes\\Boss\\BossLeft4.png")
			};
			array<Bitmap^>^ spriteVida = gcnew array<Bitmap^>(26);
			spriteVida[0] = gcnew Bitmap("Imagenes\\Boss\\Vida\\BarraVida1.png");
			spriteVida[1] = gcnew Bitmap("Imagenes\\Boss\\Vida\\BarraVida2.png");
			spriteVida[2] = gcnew Bitmap("Imagenes\\Boss\\Vida\\BarraVida3.png");
			spriteVida[3] = gcnew Bitmap("Imagenes\\Boss\\Vida\\BarraVida4.png");
			spriteVida[4] = gcnew Bitmap("Imagenes\\Boss\\Vida\\BarraVida5.png");
			spriteVida[5] = gcnew Bitmap("Imagenes\\Boss\\Vida\\BarraVida6.png");
			spriteVida[6] = gcnew Bitmap("Imagenes\\Boss\\Vida\\BarraVida7.png");
			spriteVida[7] = gcnew Bitmap("Imagenes\\Boss\\Vida\\BarraVida8.png");
			spriteVida[8] = gcnew Bitmap("Imagenes\\Boss\\Vida\\BarraVida9.png");
			spriteVida[9] = gcnew Bitmap("Imagenes\\Boss\\Vida\\BarraVida10.png");
			spriteVida[10] = gcnew Bitmap("Imagenes\\Boss\\Vida\\BarraVida11.png");
			spriteVida[11] = gcnew Bitmap("Imagenes\\Boss\\Vida\\BarraVida12.png");
			spriteVida[12] = gcnew Bitmap("Imagenes\\Boss\\Vida\\BarraVida13.png");
			spriteVida[13] = gcnew Bitmap("Imagenes\\Boss\\Vida\\BarraVida14.png");
			spriteVida[14] = gcnew Bitmap("Imagenes\\Boss\\Vida\\BarraVida15.png");
			spriteVida[15] = gcnew Bitmap("Imagenes\\Boss\\Vida\\BarraVida16.png");
			spriteVida[16] = gcnew Bitmap("Imagenes\\Boss\\Vida\\BarraVida17.png");
			spriteVida[17] = gcnew Bitmap("Imagenes\\Boss\\Vida\\BarraVida18.png");
			spriteVida[18] = gcnew Bitmap("Imagenes\\Boss\\Vida\\BarraVida19.png");
			spriteVida[19] = gcnew Bitmap("Imagenes\\Boss\\Vida\\BarraVida20.png");
			spriteVida[20] = gcnew Bitmap("Imagenes\\Boss\\Vida\\BarraVida21.png");
			spriteVida[21] = gcnew Bitmap("Imagenes\\Boss\\Vida\\BarraVida22.png");
			spriteVida[22] = gcnew Bitmap("Imagenes\\Boss\\Vida\\BarraVida23.png");
			spriteVida[23] = gcnew Bitmap("Imagenes\\Boss\\Vida\\BarraVida24.png");
			spriteVida[24] = gcnew Bitmap("Imagenes\\Boss\\Vida\\BarraVida25.png");
			spriteVida[25] = gcnew Bitmap("Imagenes\\Boss\\Vida\\BarraVida26.png");

			Vida^ vidaBoss = gcnew Vida(g->VisibleClipBounds.Width - 100, 250, 87, 435, spriteVida, 0, 0);

			boss = gcnew Boss(this->ClientRectangle.Width / 2 - 160, this->ClientRectangle.Height / 2 - 140, 400, 400, images, 0, 3, 5000, 50, vidaBoss);
		}
		void LoadMusics() {
			Final_music = "Musicas\\Musica_GMA_Mundo5.wav";
		}
		void LoadRecursos() {
			imagesRecurso = gcnew array<Bitmap^>(6) {
				gcnew Bitmap("Imagenes\\Recursos\\SemillaDeCaña.png"),
					gcnew Bitmap("Imagenes\\Recursos\\Caña.png"),
					gcnew Bitmap("Imagenes\\Recursos\\Madera.png"),
					gcnew Bitmap("Imagenes\\Recursos\\Arbol.png"),
					gcnew Bitmap("Imagenes\\Recursos\\Agua.png"),
					gcnew Bitmap("Imagenes\\Recursos\\Flor.png")
			};
			recursos_1 = gcnew Recursos;
			recursos_2 = gcnew Recursos;
			recursos_3 = gcnew Recursos;
			recursos_4 = gcnew Recursos;
			recursos_5 = gcnew Recursos;
		}
		void LoadTempos() {
			array<Bitmap^>^ images = gcnew array<Bitmap^>(62) {
				gcnew Bitmap("Imagenes\\Tiempo\\0.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\1.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\2.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\3.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\4.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\5.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\6.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\7.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\8.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\9.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\10.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\11.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\12.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\13.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\14.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\15.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\16.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\17.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\18.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\19.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\20.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\21.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\22.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\23.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\24.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\25.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\26.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\27.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\28.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\29.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\30.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\31.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\32.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\33.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\34.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\35.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\36.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\37.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\38.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\39.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\40.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\41.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\42.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\43.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\44.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\45.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\46.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\47.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\48.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\49.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\50.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\51.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\52.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\53.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\54.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\55.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\56.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\57.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\58.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\59.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\60.png"),
					gcnew Bitmap("Imagenes\\Tiempo\\GO!.png")
			};
			int width = 80;
			int height = 80;
			int x = (this->ClientSize.Width - width) / 2 - 1;
			int y = -5;
			temporizador_1 = gcnew Temporizador(x, y, width, height, images);
			temporizador_2 = gcnew Temporizador(x, y, width, height, images);
			temporizador_3 = gcnew Temporizador(x, y, width, height, images);
			temporizador_4 = gcnew Temporizador(x, y, width, height, images);
			temporizador_5 = gcnew Temporizador(x, y, width, height, images);
		}
		void LoadBullets() {
			images_heroBala = gcnew array<Bitmap^>(6) {
				gcnew Bitmap("Imagenes\\Bala\\Hero\\BalaRight1.png"),
					gcnew Bitmap("Imagenes\\Bala\\Hero\\BalaRight2.png"),
					gcnew Bitmap("Imagenes\\Bala\\Hero\\BalaRight3.png"),
					gcnew Bitmap("Imagenes\\Bala\\Hero\\BalaLeft1.png"),
					gcnew Bitmap("Imagenes\\Bala\\Hero\\BalaLeft2.png"),
					gcnew Bitmap("Imagenes\\Bala\\Hero\\BalaLeft3.png")
			};
			images_bossBala = gcnew array<Bitmap^>(8) {
				gcnew Bitmap("Imagenes\\Bala\\Boss\\BalaRight1.png"),
					gcnew Bitmap("Imagenes\\Bala\\Boss\\BalaRight2.png"),
					gcnew Bitmap("Imagenes\\Bala\\Boss\\BalaRight3.png"),
					gcnew Bitmap("Imagenes\\Bala\\Boss\\BalaRight4.png"),
					gcnew Bitmap("Imagenes\\Bala\\Boss\\BalaLeft1.png"),
					gcnew Bitmap("Imagenes\\Bala\\Boss\\BalaLeft2.png"),
					gcnew Bitmap("Imagenes\\Bala\\Boss\\BalaLeft3.png"),
					gcnew Bitmap("Imagenes\\Bala\\Boss\\BalaLeft4.png")
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
			generarAliados(aliados_3, images);
			aliados_4 = gcnew Aliados;
			generarAliados(aliados_4, images);
		}
		void generarAliados(Aliados^ allies, cli::array<Bitmap^>^ imgs) {
			Graphics^ g = this->CreateGraphics();
			for (int i = 0; i < 3; ++i) {
				allies->agregarAliado(gcnew Aliado((g->VisibleClipBounds.Width / 3) * (i + 0.5), defaultFloorY, 0, 80, 80, imgs));
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
			array<SoundPlayer^>^ sound = gcnew array<SoundPlayer^>(2) {
				gcnew SoundPlayer("EfectosDeSonido\\Enemy\\EnemyAttacked.wav"),
					gcnew SoundPlayer("EfectosDeSonido\\Enemy\\EnemyDeath.wav")
			};

			enemigos_1 = gcnew Enemigos;
			generarEnemigos(enemigos_1, images, suelos_1, 300, 30, 11, sound);
			recursosPorSembrar_1 = int(11 * 0.7);

			enemigos_2 = gcnew Enemigos;
			generarEnemigos(enemigos_2, images, suelos_2, 400, 40, 12, sound);
			recursosPorSembrar_2 = int(12 * 0.7);

			enemigos_3 = gcnew Enemigos;
			generarEnemigos(enemigos_3, images, suelos_3, 500, 50, 13, sound);
			recursosPorSembrar_3 = int(13 * 0.7);

			enemigos_4 = gcnew Enemigos;
			generarEnemigos(enemigos_4, images, suelos_4, 600, 60, 14, sound);
			recursosPorSembrar_4 = int(14 * 0.7);
		}
		void generarEnemigos(Enemigos^ enemies, cli::array<Bitmap^>^ images, Suelos^ suelos, int vidas, int daño, int n, array<SoundPlayer^>^ sounds) {
			Graphics^ g = this->CreateGraphics();
			List<int>^ indexWarning = gcnew List<int>();
			for (int i = 0; i < 9; ++i) {
				int index;
				do {
					index = randnum(0, suelos->getN() - 1);
				} while (indexWarning->Contains(index));
				indexWarning->Add(index);
				int width = suelos->getSuelo(index)->getWidth();
				int x = suelos->getSuelo(index)->getX() + width / 2 - margendeErrorX * 2;
				int y = suelos->getSuelo(index)->getY() - margendeErrorY * 5;
				enemies->agregarEnemigo(gcnew Enemigo(x, y, randDX(), 80, 80, images, daño, vidas, sounds));
			}
			for (int i = 9; i < n; ++i) {
				enemies->agregarEnemigo(gcnew Enemigo(g->VisibleClipBounds.Width / (n - 9) * (i - 9 + 0.5), defaultFloorY, randDX(), 80, 80, images, daño, vidas, sounds));
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
			suelos_5->agregarSuelo(gcnew Suelo(202, 485, 238, 32));
			suelos_5->agregarSuelo(gcnew Suelo(395, 297, 132, 32));
			suelos_5->agregarSuelo(gcnew Suelo(669, 188, 238, 32));
			suelos_5->agregarSuelo(gcnew Suelo(1033, 298, 132, 32));
			suelos_5->agregarSuelo(gcnew Suelo(1145, 481, 238, 32));
			suelos_5->agregarSuelo(gcnew Suelo(1036, 631, 132, 32));
			suelos_5->agregarSuelo(gcnew Suelo(668, 700, 238, 32));
			suelos_5->agregarSuelo(gcnew Suelo(396, 638, 132, 32));

			suelos_5->agregarSuelo(gcnew Suelo(351, 385, 76, 33));
			suelos_5->agregarSuelo(gcnew Suelo(561, 239, 76, 32));
			suelos_5->agregarSuelo(gcnew Suelo(935, 240, 76, 32));
			suelos_5->agregarSuelo(gcnew Suelo(1149, 382, 76, 32));
			suelos_5->agregarSuelo(gcnew Suelo(1149, 561, 76, 32));
			suelos_5->agregarSuelo(gcnew Suelo(941, 671, 76, 32));
			suelos_5->agregarSuelo(gcnew Suelo(563, 672, 76, 32));
			suelos_5->agregarSuelo(gcnew Suelo(352, 562, 76, 32));

			suelos_victoria = gcnew Suelos;
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
			portal_5_f = gcnew Portal(666, 366, 196, 166, gcnew array<Image^>(8) {
				Image::FromFile("Imagenes\\Portales\\Portal5_0.png"),
					Image::FromFile("Imagenes\\Portales\\Portal5_1.png"),
					Image::FromFile("Imagenes\\Portales\\Portal5_2.png"),
					Image::FromFile("Imagenes\\Portales\\Portal5_3.png"),
					Image::FromFile("Imagenes\\Portales\\Portal5_4_0.png"),
					Image::FromFile("Imagenes\\Portales\\Portal5_4_1.png"),
					Image::FromFile("Imagenes\\Portales\\Portal5_4_2.png"),
					Image::FromFile("Imagenes\\Portales\\Portal5_4_3.png")
			});

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
				Image::FromFile("Imagenes\\Mundos\\Mundo5_0.jpg"),
					Image::FromFile("Imagenes\\Mundos\\Mundo5_1.jpg"),
					Image::FromFile("Imagenes\\Mundos\\Mundo5_2.jpg"),
					Image::FromFile("Imagenes\\Mundos\\Mundo5_3.jpg"),
					Image::FromFile("Imagenes\\Mundos\\Mundo5_4.jpg"),
			});
			mundo_victoria = gcnew Mundo(0, 0, g->VisibleClipBounds.Width, g->VisibleClipBounds.Height, gcnew array<Image^>(1) {
				Image::FromFile("Imagenes\\Mundos\\MundoVictoria.jpg"),
			});
		}
		void LoadHero() {
			array<Bitmap^>^ sprites = gcnew array<Bitmap^>(44);

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
			sprites[38] = gcnew Bitmap("Imagenes\\Sprites\\Events\\SpriteDeadRight3.png");

			sprites[39] = gcnew Bitmap("Imagenes\\Sprites\\Events\\SpriteDeadLeft1.png");
			sprites[40] = gcnew Bitmap("Imagenes\\Sprites\\Events\\SpriteDeadLeft2.png");
			sprites[41] = gcnew Bitmap("Imagenes\\Sprites\\Events\\SpriteDeadLeft3.png");

			sprites[42] = gcnew Bitmap("Imagenes\\Sprites\\Events\\SpriteWin1.png");
			sprites[43] = gcnew Bitmap("Imagenes\\Sprites\\Events\\SpriteWin2.png");

			array<Bitmap^>^ spritesVida = gcnew array<Bitmap^>(11);

			// Carga cada sprite desde su ubicación
			spritesVida[0] = gcnew Bitmap("Imagenes\\Sprites\\Vida\\BarraVida1.png");
			spritesVida[1] = gcnew Bitmap("Imagenes\\Sprites\\Vida\\BarraVida2.png");
			spritesVida[2] = gcnew Bitmap("Imagenes\\Sprites\\Vida\\BarraVida3.png");
			spritesVida[3] = gcnew Bitmap("Imagenes\\Sprites\\Vida\\BarraVida4.png");
			spritesVida[4] = gcnew Bitmap("Imagenes\\Sprites\\Vida\\BarraVida5.png");
			spritesVida[5] = gcnew Bitmap("Imagenes\\Sprites\\Vida\\BarraVida6.png");
			spritesVida[6] = gcnew Bitmap("Imagenes\\Sprites\\Vida\\BarraVida7.png");
			spritesVida[7] = gcnew Bitmap("Imagenes\\Sprites\\Vida\\BarraVida8.png");
			spritesVida[8] = gcnew Bitmap("Imagenes\\Sprites\\Vida\\BarraVida9.png");
			spritesVida[9] = gcnew Bitmap("Imagenes\\Sprites\\Vida\\BarraVida10.png");
			spritesVida[10] = gcnew Bitmap("Imagenes\\Sprites\\Vida\\BarraVida11.png");

			Vida^ vida = gcnew Vida(0, 20, 350, 87, spritesVida, 0, 0);

			array<SoundPlayer^>^ sounds = gcnew array<SoundPlayer^> {
				gcnew SoundPlayer("EfectosDeSonido\\Hero\\HeroPunching.wav"),
					gcnew SoundPlayer("EfectosDeSonido\\Hero\\HeroShooting.wav"),
					gcnew SoundPlayer("EfectosDeSonido\\Hero\\HeroPlanting.wav"),
					gcnew SoundPlayer("EfectosDeSonido\\Hero\\HeroImproved.wav"),
					gcnew SoundPlayer("EfectosDeSonido\\Hero\\HeroAttacked.wav"),
					gcnew SoundPlayer("EfectosDeSonido\\Hero\\HeroDeath.wav"),
					gcnew SoundPlayer("EfectosDeSonido\\Hero\\HeroJoining.wav"),
					gcnew SoundPlayer("EfectosDeSonido\\Hero\\HeroWin1.wav"),
					gcnew SoundPlayer("EfectosDeSonido\\Hero\\HeroWin2.wav"),
					gcnew SoundPlayer("EfectosDeSonido\\Hero\\HeroWin3.wav"),
					gcnew SoundPlayer("EfectosDeSonido\\Hero\\HeroWin4.wav"),
					gcnew SoundPlayer("EfectosDeSonido\\Hero\\HeroWin5.wav"),
			};
			hero = gcnew Heroe(100, 200, 10, 80, 80, sprites, vida, sounds);
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
			messageRecurso = gcnew array<Image^>(2) {
				Image::FromFile("Imagenes\\Mensajes\\MensajeRecurso_0.png"),
					Image::FromFile("Imagenes\\Mensajes\\MensajeRecurso_1.png")
			};
		}
		void getRandHelp() {
			this->Timer->Stop();
			int num = randnum(1, 5);
			switch (num) {
			case 1:
				MessageBox::Show("Los aliados vida y más tiempo, ¡recurre a ellos!", "Información", MessageBoxButtons::OK, MessageBoxIcon::Information);
				break;
			case 2:
				MessageBox::Show("Los enemigos te quitan vida mientras te acercas mucho a ellos, ¡evítalos!", "Peligro", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				break;
			case 3:
				MessageBox::Show("Disparar hace mucho mas daño que los golpes, aunque son limitados, apunta bien", "Información", MessageBoxButtons::OK, MessageBoxIcon::Stop);
				break;
			case 4:
				MessageBox::Show("Mientras mas avances de nivel los enemigos se vuelven mas fuertes", "Peligro", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
				break;
			case 5:
				MessageBox::Show("Plantar ayuda a progresar la reforestación, además crea munición", "Tip", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
				break;
			}
			this->Timer->Start();
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
		}
	private: System::ComponentModel::IContainer^ components;
	protected:

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>
	private:

		String^ Final_music;
		String^ musicaActual;
		// Auxiliar
		float lapse = 0.0f;
		// Sprite
		Heroe^ hero;
		float heroIndex = 0;
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
		// Reforestación
		bool planted = false;
		// MUsica
		bool sound = false;
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

		Portal^ portalActual_f;
		Portal^ portalActual_b;

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
		Recursos^ recursos_5;
		Recursos^ recursosActuales;
		array<Bitmap^>^ imagesRecurso;
		bool readyToPlant = false;

		Suelos^ suelos_1;
		Suelos^ suelos_2;
		Suelos^ suelos_3;
		Suelos^ suelos_4;
		Suelos^ suelos_5;
		Suelos^ suelos_victoria;
		Suelos^ suelosActuales;

		Enemigos^ enemigos_1;
		Enemigos^ enemigos_2;
		Enemigos^ enemigos_3;
		Enemigos^ enemigos_4;
		Enemigos^ enemigosActuales;

		int^ recursosSembrados_1 = gcnew int(0);
		int recursosPorSembrar_1;
		int^ recursosSembrados_2 = gcnew int(0);
		int recursosPorSembrar_2;
		int^ recursosSembrados_3 = gcnew int(0);
		int recursosPorSembrar_3;
		int^ recursosSembrados_4 = gcnew int(0);
		int recursosPorSembrar_4;

		int^ recursosSembrados_Actuales;
		int^ recursosPorSembrar_Actuales;
		Boss^ boss;

		Mundo^ mundo_1;
		Mundo^ mundo_2;
		Mundo^ mundo_3;
		Mundo^ mundo_4;
		Mundo^ mundo_5;
		Mundo^ mundo_victoria;

		Mundo^ mundoActual;

		bool val_mundo_1 = true;
		bool val_mundo_2 = false;
		bool val_mundo_3 = false;
		bool val_mundo_4 = false;
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

		Temporizador^ temporizador_1;
		Temporizador^ temporizador_2;
		Temporizador^ temporizador_3;
		Temporizador^ temporizador_4;
		Temporizador^ temporizador_5;
		Temporizador^ temporizadorActual;

		array<Image^>^ messages_b;
		array<Image^>^ messages_f;
		array<Image^>^ messageRecurso;
		int messageIndex = 0;
		
		array<Bitmap^>^ images_heroBala;
		array<Bitmap^>^ images_bossBala;
private: System::Windows::Forms::Timer^ Timer;

		bool dead;

		BufferedGraphicsContext^ bufferContext;
		BufferedGraphics^ bufferGraphics;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
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
			this->Text = L"Juego";
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyUp);
			this->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MyForm_MouseClick);
			this->ResumeLayout(false);

		}
#pragma endregion
		// Funcion de Buffer
		void DibujarEnBuffer(Graphics^ g) {
			bufferContext = BufferedGraphicsManager::Current;
			bufferGraphics = bufferContext->Allocate(this->CreateGraphics(), this->ClientRectangle);
			if (mundoActual != nullptr) {
				// Dibuja otros objetos que necesites
				System::Drawing::Imaging::ColorMatrix^ colorMatrix = gcnew System::Drawing::Imaging::ColorMatrix();
				System::Drawing::Imaging::ImageAttributes^ imageAttributes = gcnew System::Drawing::Imaging::ImageAttributes();
				int index = 60;
				if (temporizadorActual != nullptr) {
					index = temporizadorActual->getIndex();
				}
				float brightness = 1.0f; // Valor predeterminado de brillo

				if (index <= 50 && index > 40) {
					brightness = 0.8f; // 80% de brillo
				}
				else if (index <= 40 && index > 30) {
					brightness = 0.6f; // 60% de brillo
				}
				else if (index <= 30 && index > 20) {
					brightness = 0.4f; // 40% de brillo
				}
				else if (index <= 20 && index > 10) {
					brightness = 0.2f; // 20% de brillo
				}
				else if (index <= 10 && index > 0) {
					brightness = 0.1f; // 10% de brillo
				}
				else if (index == 0) {
					brightness = 0.0f;
				}

				colorMatrix->Matrix00 = brightness; // Rojo
				colorMatrix->Matrix11 = brightness; // Verde
				colorMatrix->Matrix22 = brightness; // Azul
				colorMatrix->Matrix33 = 1.0f; // Alpha (opacidad)
				colorMatrix->Matrix44 = 1.0f; // W

				imageAttributes->SetColorMatrix(colorMatrix, System::Drawing::Imaging::ColorMatrixFlag::Default, System::Drawing::Imaging::ColorAdjustType::Bitmap);

				System::Drawing::Rectangle destRect = System::Drawing::Rectangle(0, 0, this->ClientSize.Width, this->ClientSize.Height);
				bufferGraphics->Graphics->DrawImage(mundoActual->getImagenes()[imageWorldIndex], destRect, mundoActual->getX(), mundoActual->getY(), mundoActual->getImagenes()[imageWorldIndex]->Width, mundoActual->getImagenes()[imageWorldIndex]->Height, System::Drawing::GraphicsUnit::Pixel, imageAttributes);
				if (portalActual_f != nullptr) {
					portalActual_f->dibujarSprite(bufferGraphics->Graphics, imagePortalIndex_f);
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
						bufferGraphics->Graphics->DrawImage(messages_f[messageIndex], System::Drawing::Rectangle(mensajeX, mensajeY, mensajeAncho, mensajeAlto), 0, 0, mensajeAncho, mensajeAlto, GraphicsUnit::Pixel);
					}
				}
				if (portalActual_b != nullptr) {
					portalActual_b->dibujarSprite(bufferGraphics->Graphics, imagePortalIndex_b);
					if (hero->getY() + hero->getHeight() >= portalActual_b->getY() &&
						hero->getY() <= portalActual_b->getY() + portalActual_b->getHeight() &&
						hero->getX() + hero->getWidth() >= portalActual_b->getX() + margendeErrorX &&
						hero->getX() <= portalActual_b->getX() + portalActual_b->getWidth() - margendeErrorX) {
						readyToTravelBackward = true;

						int mensajeAncho = messages_b[messageIndex]->Width;
						int mensajeAlto = messages_b[messageIndex]->Height;

						// Calcular la posición de la imagen centrada horizontalmente sobre el portal
						int mensajeX = portalActual_b->getX() + (portalActual_b->getWidth() / 2) - (mensajeAncho / 2);
						int mensajeY = portalActual_b->getY() - mensajeAlto;
						bufferGraphics->Graphics->DrawImage(messages_b[messageIndex], System::Drawing::Rectangle(mensajeX, mensajeY, mensajeAncho, mensajeAlto), 0, 0, mensajeAncho, mensajeAlto, GraphicsUnit::Pixel);
					}
				}
			}
			if (enemigosActuales != nullptr) {
				for (int i = 0; i < enemigosActuales->getN(); ++i) {
					Enemigo^ enemigoActual = enemigosActuales->getEnemigo(i);
					enemigoActual->dibujarEnemigo(bufferGraphics->Graphics);
				}
			}
			if (aliadosActuales != nullptr) {
				for (int i = 0; i < aliadosActuales->getN(); ++i) {
					Aliado^ aliadoActual = aliadosActuales->getAliado(i);
					aliadoActual->dibujarAliado(bufferGraphics->Graphics);
				}
			}
			if (temporizadorActual != nullptr) {
				if (val_mundo_5) {
					temporizadorActual->dibujarTemporizador(bufferGraphics->Graphics, 0);
				}
				else {
					temporizadorActual->dibujarTemporizador(bufferGraphics->Graphics, 1);
				}
			}
			if (hero->getArma() != nullptr) {
				hero->getArma()->disparar(bufferGraphics->Graphics);
			}
			if (hero != nullptr) {
				hero->dibujarSprite(bufferGraphics->Graphics, heroIndex);
				if (!val_mundo_victoria) {
					hero->getVida()->dibujarVida(bufferGraphics->Graphics);
				}
			}
			if (recursosActuales != nullptr) {
				for (int i = 0; i < recursosActuales->getN(); ++i) {
					Recurso^ recursoActual = recursosActuales->getRecurso(i);
					recursoActual->dibujarRecurso(bufferGraphics->Graphics);
					if (!recursoActual->getSembrado()) {
						int x_Hero = hero->getX();
						int y_Hero = hero->getY();
						int width_Hero = hero->getWidth();
						int height_Hero = hero->getHeight();
						int x_Recurso = recursoActual->getX();
						int y_Recurso = recursoActual->getY();
						int width_Recurso = recursoActual->getWidth();
						int height_Recurso = recursoActual->getHeight();
						if (x_Hero < x_Recurso + width_Recurso && x_Hero + width_Hero > x_Recurso &&
							y_Hero < y_Recurso + height_Recurso && y_Hero + height_Hero > y_Recurso) {
							readyToPlant = true;
							int mensajeAncho = messageRecurso[messageIndex]->Width;
							int mensajeAlto = messageRecurso[messageIndex]->Height;

							// Calcular la posición de la imagen centrada horizontalmente sobre el portal
							int mensajeX = recursoActual->getX() + (recursoActual->getWidth() / 2) - (mensajeAncho / 2);
							int mensajeY = recursoActual->getY() - mensajeAlto;

							bufferGraphics->Graphics->DrawImage(messageRecurso[messageIndex], mensajeX, mensajeY, mensajeAncho, mensajeAlto);
						}
					}
				}
			}
			if (val_mundo_5) {
				if (boss->getAlive()) {
					boss->getArma()->disparar(bufferGraphics->Graphics);
					boss->dibujarBoss(bufferGraphics->Graphics);
				}
				boss->getVida()->dibujarVida(bufferGraphics->Graphics);
			}

			bufferGraphics->Render(g);
			delete bufferContext;
			delete bufferGraphics;
		}
		// Funciones para el Paint
		void ValidacionMundo() {
			if (val_mundo_1) {
				defaultFloorY = 570;
				musicaActual = nullptr;
				mundoActual = mundo_1;
				portalActual_f = portal_1_f;
				portalActual_b = nullptr;

				temporizadorActual = temporizador_1;
				enemigosActuales = enemigos_1;
				aliadosActuales = aliados_1;
				suelosActuales = suelos_1;
				recursosActuales = recursos_1;

				recursosSembrados_Actuales = recursosSembrados_1;
				recursosPorSembrar_Actuales = recursosPorSembrar_1;

				imageWorldStartIndex = 0;
				imageWorldEndIndex = 0;

				imagePortalStartIndex_f = 0;
				imagePortalEndIndex_f = 0;
			}
			else if (val_mundo_2) {
				defaultFloorY = 570;
				musicaActual = nullptr;
				mundoActual = mundo_2;
				portalActual_f = portal_2_f;
				portalActual_b = portal_2_b;

				temporizadorActual = temporizador_2;
				enemigosActuales = enemigos_2;
				aliadosActuales = aliados_2;
				suelosActuales = suelos_2;
				recursosActuales = recursos_2;

				recursosSembrados_Actuales = recursosSembrados_2;
				recursosPorSembrar_Actuales = recursosPorSembrar_2;

				imageWorldStartIndex = 0;
				imageWorldEndIndex = 0;

				imagePortalStartIndex_f = 0;
				imagePortalEndIndex_f = 3;

				imagePortalStartIndex_b = 0;
				imagePortalEndIndex_b = 0;
			}
			else if (val_mundo_3) {
				defaultFloorY = 570;
				musicaActual = nullptr;
				mundoActual = mundo_3;
				portalActual_f = portal_3_f;
				portalActual_b = portal_3_b;

				temporizadorActual = temporizador_3;
				enemigosActuales = enemigos_3;
				aliadosActuales = aliados_3;
				suelosActuales = suelos_3;
				recursosActuales = recursos_3;

				recursosSembrados_Actuales = recursosSembrados_3;
				recursosPorSembrar_Actuales = recursosPorSembrar_3;

				imageWorldStartIndex = 0;
				imageWorldEndIndex = 1;

				imagePortalStartIndex_f = 0;
				imagePortalEndIndex_f = 3;

				imagePortalStartIndex_b = 0;
				imagePortalEndIndex_b = 3;
			}
			else if (val_mundo_4) {
				defaultFloorY = 570;
				musicaActual = nullptr;
				mundoActual = mundo_4;
				portalActual_f = portal_4_f;
				portalActual_b = portal_4_b;

				temporizadorActual = temporizador_4;
				enemigosActuales = enemigos_4;
				aliadosActuales = aliados_4;
				suelosActuales = suelos_4;
				recursosActuales = recursos_4;

				recursosSembrados_Actuales = recursosSembrados_4;
				recursosPorSembrar_Actuales = recursosPorSembrar_4;

				imageWorldStartIndex = 0;
				imageWorldEndIndex = 2;

				imagePortalStartIndex_f = 0;
				imagePortalEndIndex_f = 3;

				imagePortalStartIndex_b = 0;
				imagePortalEndIndex_b = 3;
			}
			else if (val_mundo_5) {
				defaultFloorY = 3000;
				musicaActual = Final_music;
				mundoActual = mundo_5;
				portalActual_f = portal_5_f;
				portalActual_b = nullptr;

				temporizadorActual = temporizador_5;
				enemigosActuales = nullptr;
				aliadosActuales = nullptr;
				suelosActuales = suelos_5;
				recursosActuales = nullptr;

				recursosSembrados_Actuales = nullptr;
				recursosPorSembrar_Actuales = nullptr;

				hero->setMunicion(20);

				if (boss->getVidas() <= 5000 && boss->getVidas() > 4000) {
					imagePortalStartIndex_f = 0;
					imagePortalEndIndex_f = 0;
					if (boss->getVidas() <= 5000 && boss->getVidas() > 4800) {
						boss->getVida()->setStartIndex(0);
						boss->getVida()->setEndIndex(0);
					}
					else if (boss->getVidas() <= 4800 && boss->getVidas() > 4600) {
						boss->getVida()->setStartIndex(1);
						boss->getVida()->setEndIndex(1);
					}
					else if (boss->getVidas() <= 4600 && boss->getVidas() > 4400) {
						boss->getVida()->setStartIndex(2);
						boss->getVida()->setEndIndex(2);
					}
					else if (boss->getVidas() <= 4400 && boss->getVidas() > 4200) {
						boss->getVida()->setStartIndex(3);
						boss->getVida()->setEndIndex(3);
					}
					else if (boss->getVidas() <= 4200 && boss->getVidas() > 4000) {
						boss->getVida()->setStartIndex(4);
						boss->getVida()->setEndIndex(4);
					}
				}
				else if (boss->getVidas() <= 4000 && boss->getVidas() > 3000) {
					imagePortalStartIndex_f = 1;
					imagePortalEndIndex_f = 1;
					if (boss->getVidas() <= 4000 && boss->getVidas() > 3800) {
						boss->getVida()->setStartIndex(5);
						boss->getVida()->setEndIndex(5);
					}
					else if (boss->getVidas() <= 3800 && boss->getVidas() > 3600) {
						boss->getVida()->setStartIndex(6);
						boss->getVida()->setEndIndex(6);
					}
					else if (boss->getVidas() <= 3600 && boss->getVidas() > 3400) {
						boss->getVida()->setStartIndex(7);
						boss->getVida()->setEndIndex(7);
					}
					else if (boss->getVidas() <= 3400 && boss->getVidas() > 3200) {
						boss->getVida()->setStartIndex(8);
						boss->getVida()->setEndIndex(8);
					}
					else if (boss->getVidas() <= 3200 && boss->getVidas() > 3000) {
						boss->getVida()->setStartIndex(9);
						boss->getVida()->setEndIndex(9);
					}
				}
				else if (boss->getVidas() <= 3000 && boss->getVidas() > 2000) {
					imagePortalStartIndex_f = 2;
					imagePortalEndIndex_f = 2;
					if (boss->getVidas() <= 3000 && boss->getVidas() > 2800) {
						boss->getVida()->setStartIndex(10);
						boss->getVida()->setEndIndex(10);
					}
					else if (boss->getVidas() <= 2800 && boss->getVidas() > 2600) {
						boss->getVida()->setStartIndex(11);
						boss->getVida()->setEndIndex(11);
					}
					else if (boss->getVidas() <= 2600 && boss->getVidas() > 2400) {
						boss->getVida()->setStartIndex(12);
						boss->getVida()->setEndIndex(12);
					}
					else if (boss->getVidas() <= 2400 && boss->getVidas() > 2200) {
						boss->getVida()->setStartIndex(13);
						boss->getVida()->setEndIndex(13);
					}
					else if (boss->getVidas() <= 2200 && boss->getVidas() > 2000) {
						boss->getVida()->setStartIndex(14);
						boss->getVida()->setEndIndex(14);
					}
				}
				else if (boss->getVidas() <= 2000 && boss->getVidas() > 1000) {
					imagePortalStartIndex_f = 3;
					imagePortalEndIndex_f = 3;
					if (boss->getVidas() <= 2000 && boss->getVidas() > 1800) {
						boss->getVida()->setStartIndex(15);
						boss->getVida()->setEndIndex(15);
					}
					else if (boss->getVidas() <= 1800 && boss->getVidas() > 1600) {
						boss->getVida()->setStartIndex(16);
						boss->getVida()->setEndIndex(16);
					}
					else if (boss->getVidas() <= 1600 && boss->getVidas() > 1400) {
						boss->getVida()->setStartIndex(17);
						boss->getVida()->setEndIndex(17);
					}
					else if (boss->getVidas() <= 1400 && boss->getVidas() > 1200) {
						boss->getVida()->setStartIndex(18);
						boss->getVida()->setEndIndex(18);
					}
					else if (boss->getVidas() <= 1200 && boss->getVidas() > 1000) {
						boss->getVida()->setStartIndex(19);
						boss->getVida()->setEndIndex(19);
					}
				}
				else if (boss->getVidas() <= 1000 && boss->getVidas() > 0) {
					imagePortalStartIndex_f = 3;
					imagePortalEndIndex_f = 3;
					if (boss->getVidas() <= 1000 && boss->getVidas() > 800) {
						boss->getVida()->setStartIndex(20);
						boss->getVida()->setEndIndex(20);
					}
					else if (boss->getVidas() <= 800 && boss->getVidas() > 600) {
						boss->getVida()->setStartIndex(21);
						boss->getVida()->setEndIndex(21);
					}
					else if (boss->getVidas() <= 600 && boss->getVidas() > 400) {
						boss->getVida()->setStartIndex(22);
						boss->getVida()->setEndIndex(22);
					}
					else if (boss->getVidas() <= 400 && boss->getVidas() > 200) {
						boss->getVida()->setStartIndex(23);
						boss->getVida()->setEndIndex(23);
					}
					else if (boss->getVidas() <= 200 && boss->getVidas() > 0) {
						boss->getVida()->setStartIndex(24);
						boss->getVida()->setEndIndex(24);
					}
				}
				else if (boss->getVidas() <= 0) {
					imagePortalStartIndex_f = 4;
					imagePortalEndIndex_f = 7;
					boss->getVida()->setStartIndex(25);
					boss->getVida()->setEndIndex(25);
					boss->setAlive(false);
				}
				imageWorldStartIndex = 0;
				imageWorldEndIndex = 4;
			}
			else if (val_mundo_victoria) {
				hero->setWidth(160);
				hero->setHeight(160);
				defaultFloorY = 500;
				mundoActual = mundo_victoria;
				portalActual_f = nullptr;
				portalActual_b = nullptr;

				temporizadorActual = nullptr;
				enemigosActuales = nullptr;
				aliadosActuales = nullptr;
				suelosActuales = suelos_victoria;
				recursosActuales = nullptr;
				recursosSembrados_Actuales = nullptr;
				recursosPorSembrar_Actuales = nullptr;

				imageWorldStartIndex = 0;
				imageWorldEndIndex = 0;

				imagePortalStartIndex_f = -1;
				imagePortalEndIndex_f = -1;

				imagePortalStartIndex_b = -1;
				imagePortalEndIndex_b = -1;
			}
		}
		void ReproduccionDelMundo(Graphics^ g) {
			if (!sound && musicaActual != nullptr) {
				SoundPlayer^ musica = gcnew SoundPlayer(musicaActual);
				musica->PlayLooping();
				sound = true;
			}
			if (mundoActual != nullptr) {
				++imageWorldIndex;
				if (imageWorldIndex > imageWorldEndIndex) {
					imageWorldIndex = imageWorldStartIndex;
				}
				if (portalActual_f != nullptr) {

					++imagePortalIndex_f;
					if (imagePortalIndex_f > imagePortalEndIndex_f) {
						imagePortalIndex_f = imagePortalStartIndex_f;
					}

					if (hero->getY() + hero->getHeight() >= portalActual_f->getY() &&
						hero->getY() <= portalActual_f->getY() + portalActual_f->getHeight() &&
						hero->getX() + hero->getWidth() >= portalActual_f->getX() + margendeErrorX &&
						hero->getX() <= portalActual_f->getX() + portalActual_f->getWidth() - margendeErrorX) {
						readyToTravelForward = true;

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

					++imagePortalIndex_b;
					if (imagePortalIndex_b > imagePortalEndIndex_b) {
						imagePortalIndex_b = imagePortalStartIndex_b;
					}

					if (hero->getY() + hero->getHeight() >= portalActual_b->getY() &&
						hero->getY() <= portalActual_b->getY() + portalActual_b->getHeight() &&
						hero->getX() + hero->getWidth() >= portalActual_b->getX() + margendeErrorX &&
						hero->getX() <= portalActual_b->getX() + portalActual_b->getWidth() - margendeErrorX) {
						readyToTravelBackward = true;

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
					enemigoActual->setIndex(enemigoActual->getIndex() + 1);
					if (enemigoActual->getIndex() > enemigoActual->getEndIndex()) {
						enemigoActual->setIndex(enemigoActual->getStartIndex());
					}
				}
			}
			if (aliadosActuales != nullptr) {
				for (int i = 0; i < aliadosActuales->getN(); ++i) {
					Aliado^ aliadoActual = aliadosActuales->getAliado(i);
					aliadoActual->setIndex(aliadoActual->getIndex() + 1);
					if (aliadoActual->getIndex() > aliadoActual->getEndIndex()) {
						aliadoActual->setIndex(aliadoActual->getStartIndex());
					}
				}
			}
			if (temporizadorActual != nullptr) {
				if (temporizadorActual->getActivo()) {
					temporizadorActual->setIndex(temporizadorActual->getIndex() - 0.070);
				}
				if (!dead) {
					if (temporizadorActual->getIndex() <= 0 || hero->getVidas() <= 0) {
						dead = true;
						if (movingRight || lastMove == "right") {
							startIndex = 36;
							endIndex = 38;
						}
						else if (movingLeft || lastMove == "left") {
							startIndex = 39;
							endIndex = 41;
						}
						heroIndex = startIndex;
					}
				}
			}
			if (hero->getArma() != nullptr) {
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
				static bool deadStarted = false;
				if (dead && !deadStarted) {
					hero->setAttacked(false);
					deadStarted = true;
					hero->getSounds()[5]->Play();
					this->Timer->Interval = 500;
				}
				if (hero->getAttacked()) {
					Sleep(1000);
				}
				if (hero->getVida()!= nullptr) {
					hero->getVida()->setIndex(hero->getVida()->getIndex() + 1);
					if (hero->getVida()->getIndex() > hero->getVida()->getEndIndex()) {
						hero->getVida()->setIndex(hero->getVida()->getStartIndex());
					}
				}
			}
			if (recursosActuales != nullptr) {
				for (int i = 0; i < recursosActuales->getN(); ++i) {
					Recurso^ recursoActual = recursosActuales->getRecurso(i);

					if (!recursoActual->getSembrado()) {
						int x_Hero = hero->getX();
						int y_Hero = hero->getY();
						int width_Hero = hero->getWidth();
						int height_Hero = hero->getHeight();
						int x_Recurso = recursoActual->getX();
						int y_Recurso = recursoActual->getY();
						int width_Recurso = recursoActual->getWidth();
						int height_Recurso = recursoActual->getHeight();
						if (x_Hero < x_Recurso + width_Recurso && x_Hero + width_Hero > x_Recurso &&
							y_Hero < y_Recurso + height_Recurso && y_Hero + height_Hero > y_Recurso) {
							readyToPlant = true;

							messageIndex++;
							if (messageIndex > 1) {
								messageIndex = 0;
							}
							if (planted) {
								++(*recursosSembrados_Actuales);
								recursoActual->setSembrado(true);
								planted = false;
								hero->setMunicion(hero->getMunicion() + 5);
								if (!val_mundo_5) {
									hero->getSounds()[2]->PlaySync();
								}
							}
						}
					}
				}
			}
			if (val_mundo_5) {
				if (boss->getAlive()) {
					boss->setLapse(boss->getLapse() + 0.2);
					if (boss->getLapse() > 2) {
						int x = boss->getX();
						int width = boss->getWidth();
						int y = boss->getY() + boss->getHeight() / 2 - 20;
						if (boss->getSeingLeft()) {
							boss->getArma()->agregarBala(gcnew Bala(x - 90, y, -20, 3, 150, 150, images_bossBala));
						}
						else if (boss->getSeingRight()) {
							boss->getArma()->agregarBala(gcnew Bala(x + width, y, 20, 3, 150, 150, images_bossBala));
						}
						boss->setLapse(0);
					}
					boss->setIndex(boss->getIndex() + 1);
					if (boss->getIndex() > boss->getEndIndex()) {
						boss->setIndex(boss->getStartIndex());
					}
					boss->movimientoEspiral(g);
					if (boss->getArma() != nullptr) {
						for (int i = boss->getArma()->getN() - 1; i >= 0; --i) {
							Bala^ balaActual = boss->getArma()->getBala(i);
							balaActual->setIndex(balaActual->getIndex() + 1);
							if (balaActual->getIndex() > balaActual->getEndIndex()) {
								balaActual->setIndex(balaActual->getStartIndex());
							}
							int x_Bala = balaActual->getX();
							int y_Bala = balaActual->getY();
							int width_Bala = balaActual->getWidth();
							int height_Bala = balaActual->getHeight();

							int x_Hero = hero->getX();
							int y_Hero = hero->getY();
							int width_Hero = hero->getWidth();
							int height_Hero = hero->getHeight();

							int ajusteHero_x = width_Hero * 0.2;
							int ajusteHero_y = height_Hero * 0.2;

							int ajusteBala_x = width_Bala * 0.1;
							int ajusteBala_y = height_Bala * 0.3;

							if (x_Bala < 0 && x_Bala + width_Bala > g->VisibleClipBounds.Width) {
								boss->getArma()->eliminarBala(i);
							}
							if (x_Hero + width_Hero - ajusteHero_x > x_Bala + ajusteBala_x && x_Hero + ajusteHero_x < x_Bala + width_Bala - ajusteBala_x &&
								y_Hero + height_Hero - ajusteHero_y > y_Bala + ajusteBala_y && y_Hero + ajusteBala_y < y_Bala + height_Bala - ajusteBala_y) {
								hero->setVidas(hero->getVidas() - boss->getDaño());
								hero->setAttacked(true);
							}
						}
					}
				}
				boss->getVida()->setIndex(boss->getVida()->getIndex() + 1);
				if (boss->getVida()->getIndex() > boss->getVida()->getEndIndex()) {
					boss->getVida()->setIndex(boss->getVida()->getStartIndex());
				}
			}
		}
		void MyForm_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
			Graphics^ g = e->Graphics;
			ValidacionMundo();
			ReproduccionDelMundo(g);
			DibujarEnBuffer(g);
		}
		// Funciones para el Tick
		void ValidacionDeEstados() {
			if (dead) {
				heroIndex++;
				if (heroIndex > endIndex) {
					static bool dead = false;
					if (!dead) {
						FormEnd^ formEnd = gcnew FormEnd("lose");
						formEnd->Show();
						dead = true;
						this->Close();
					}
				}
			}

			if (hero->getVida() != nullptr) {
				if (hero->getVidas() <= 1000 && hero->getVidas() > 900) {
					hero->getVida()->setStartIndex(0);
					hero->getVida()->setEndIndex(0);
				}
				else if (hero->getVidas() <= 900 && hero->getVidas() > 800) {
					hero->getVida()->setStartIndex(1);
					hero->getVida()->setEndIndex(1);
				}
				else if (hero->getVidas() <= 800 && hero->getVidas() > 700) {
					hero->getVida()->setStartIndex(2);
					hero->getVida()->setEndIndex(2);
				}
				else if (hero->getVidas() <= 700 && hero->getVidas() > 600) {
					hero->getVida()->setStartIndex(3);
					hero->getVida()->setEndIndex(3);
				}
				else if (hero->getVidas() <= 600 && hero->getVidas() > 500) {
					hero->getVida()->setStartIndex(4);
					hero->getVida()->setEndIndex(4);
				}
				else if (hero->getVidas() <= 500 && hero->getVidas() > 400) {
					hero->getVida()->setStartIndex(5);
					hero->getVida()->setEndIndex(5);
				}
				else if (hero->getVidas() <= 400 && hero->getVidas() > 300) {
					hero->getVida()->setStartIndex(6);
					hero->getVida()->setEndIndex(6);
				}
				else if (hero->getVidas() <= 300 && hero->getVidas() > 200) {
					hero->getVida()->setStartIndex(7);
					hero->getVida()->setEndIndex(7);
				}
				else if (hero->getVidas() <= 200 && hero->getVidas() > 100) {
					hero->getVida()->setStartIndex(8);
					hero->getVida()->setEndIndex(8);
				}
				else if (hero->getVidas() <= 100 && hero->getVidas() > 0) {
					hero->getVida()->setStartIndex(9);
					hero->getVida()->setEndIndex(10);
				}
				else if (hero->getVidas() <= 0) {
					hero->getVida()->setStartIndex(10);
					hero->getVida()->setEndIndex(10);
				}
			}
		}
		void CondicionesParaEnemigos(Graphics^ g) {
			if (!dead) {
				if (enemigosActuales != nullptr) {
					for (int i = 0; i < enemigosActuales->getN(); ++i) {
						Enemigo^ enemigoActual = enemigosActuales->getEnemigo(i);
						if (suelosActuales != nullptr) {
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
						}


						if (enemigosActuales->getEnemigo(i)->getVidas() <= 0) {
							int x = enemigosActuales->getEnemigo(i)->getX() + 20;
							int y = enemigosActuales->getEnemigo(i)->getY() + 20;
							recursosActuales->agregarRecurso(gcnew Recurso(x, y, 20, 20, imagesRecurso, randRecurso()));
							enemigosActuales->getEnemigo(i)->getSounds()[1]->PlaySync();
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

					for (int i = 0; i < enemigosActuales->getN(); ++i) {
						Enemigo^ enemy = enemigosActuales->getEnemigo(i);
						int x_Enemy = enemy->getX();
						int y_Enemy = enemy->getY();
						int width_Enemy = enemy->getWidth();
						int height_Enemy = enemy->getHeight();

						int x_Hero = hero->getX();
						int y_Hero = hero->getY();
						int width_Hero = hero->getWidth();
						int height_Hero = hero->getHeight();

						int ajusteEnemyX = width_Enemy * 0.4;
						int ajusteEnemyY = height_Enemy * 0.4;
						int ajusteHeroX = width_Hero * 0.4;
						int ajusteHeroY = height_Hero * 0.4;

						if (x_Hero + ajusteHeroX < x_Enemy + width_Enemy - ajusteEnemyX && x_Hero + width_Hero - ajusteHeroX > x_Enemy + ajusteEnemyX &&
							y_Hero + ajusteHeroY < y_Enemy + height_Enemy - ajusteEnemyY && y_Hero + height_Hero - ajusteHeroY > y_Enemy + ajusteEnemyY) {
							hero->setAttacked(true);
							hero->setVidas(hero->getVidas() - enemy->getDaño());
							hero->getSounds()[4]->Play();
						}
					}
				}
				if (val_mundo_5) {
					if (boss->getAlive()) {
						int x_boss = boss->getX();
						int y_boss = boss->getY();
						int width_boss = boss->getWidth();
						int height_boss = boss->getHeight();

						int x_hero = hero->getX();
						int y_hero = hero->getY();
						int width_hero = hero->getWidth();
						int height_hero = hero->getHeight();

						int ajusteX_hero = width_hero * 0.2;
						int ajusteY_hero = height_hero * 0.2;

						int ajusteX_boss = width_boss * 0.1;
						int ajusteY_boss = height_boss * 0.1;

						if (x_hero + ajusteX_hero < x_boss + width_boss - ajusteX_boss && x_hero + width_hero - ajusteX_hero > x_boss + ajusteX_boss &&
							y_hero + ajusteY_hero < y_boss + height_boss - ajusteY_boss * 2 && y_hero + height_hero - ajusteY_hero > y_boss + ajusteY_boss * 4) {
							hero->setAttacked(true);
							hero->setVidas(hero->getVidas() - 100);
						}
						for (int i = 0; i < hero->getArma()->getN(); ++i) {
							Bala^ bala = hero->getArma()->getBala(i);
							int x_Bala = bala->getX();
							int y_Bala = bala->getY();
							int width_Bala = bala->getWidth();
							int height_Bala = bala->getHeight();

							int ajusteBalaX = width_Bala * 0.2;  // Ajustar el 20% del ancho de la bala
							int ajusteBalaY = height_Bala * 0.2; // Ajustar el 20% de la altura de la bala

							if (x_Bala + ajusteBalaX < x_boss + width_boss &&
								x_Bala + width_Bala - ajusteBalaX > x_boss &&
								y_Bala + ajusteBalaY < y_boss + height_boss &&
								y_Bala + height_Bala - ajusteBalaY > y_boss + ajusteY_boss * 3) {
								boss->setAttacked(true);
								boss->setVidas(boss->getVidas() - 100);
								hero->getArma()->eliminarBala(i);
							}
						}
					}
				}
			}
		}
		void CondicionesParaTempo() {
			if (recursosSembrados_Actuales != nullptr && recursosPorSembrar_Actuales != nullptr) {
				if (*recursosSembrados_Actuales >= *recursosPorSembrar_Actuales) {
					temporizadorActual->setActivo(false);
				}
			}
			if (!boss->getAlive()) {
				if (temporizadorActual != nullptr) {
					temporizadorActual->setActivo(false);
				}
			}
		}
		void CondicionesParaAliados() {
			if (!dead) {
				if (aliadosActuales != nullptr) {
					for (int i = 0; i < aliadosActuales->getN(); ++i) {
						Aliado^ aliadoActual = aliadosActuales->getAliado(i);
						int x_Hero = hero->getX();
						int y_Hero = hero->getY();
						int width_Hero = hero->getWidth();
						int height_Hero = hero->getHeight();

						int x_Allie = aliadoActual->getX();
						int y_Allie = aliadoActual->getY();
						int width_Allie = aliadoActual->getWidth();
						int height_Allie = aliadoActual->getHeight();

						int ajusteAllieX = width_Allie * 0.2;
						int ajusteAllieY = height_Allie * 0.2;
						int ajusteHeroX = width_Hero * 0.2;
						int ajusteHeroY = height_Hero * 0.2;

						if (x_Hero + width_Hero - ajusteHeroX > x_Allie + ajusteAllieX && x_Hero + ajusteHeroX < x_Allie + width_Allie - ajusteAllieX &&
							y_Hero + height_Hero - ajusteAllieY > y_Allie + ajusteAllieY && y_Hero + ajusteHeroY < y_Allie + height_Allie - ajusteAllieY) {
							getRandHelp();
							hero->setVidas(hero->getVidas() + 100);
							aliadosActuales->eliminarAliado(i);
							temporizadorActual->setIndex(temporizadorActual->getIndex() + 10);
							if (!val_mundo_5) {
								hero->getSounds()[3]->PlaySync();
							}
						}
					}
				}
			}
		}
		void AccionesDelJugador(Graphics^ g) {
			if (!dead) {
				if (!falling) {
					if (suelosActuales != nullptr) {
						int pieSpriteY = hero->getY() + hero->getHeight() - margendeErrorY;
						for (int i = 0; i < suelosActuales->getN(); ++i) {
							Suelo^ sueloActual = suelosActuales->getSuelo(i);

							int sueloX = sueloActual->getX();
							int sueloY = sueloActual->getY();
							int sueloWidth = sueloActual->getWidth();
							int sueloHeight = sueloActual->getHeight();

							if (pieSpriteY >= sueloY &&
								pieSpriteY <= sueloY + sueloHeight &&
								hero->getX() + hero->getWidth() >= sueloX + margendeErrorX &&
								hero->getX() <= sueloX + sueloWidth - margendeErrorX * 2) {
								falling = false;
								break;
							}
							if (pieSpriteY > defaultFloorY + margendeErrorY * 2) {
								falling = false;
							}
							else {
								falling = true;
							}
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

					if (suelosActuales != nullptr) {
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
					if (hero->getY() + hero->getHeight() > 750) {
						jumpSpeed = jumpStrength;
						jumping = true;
						falling = false;
						running = false;
						sliding = false;
						gravity = 5;
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
							int rangePunch = 80;
							if (enemigosActuales != nullptr) {
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
									if (y_Enemy + height_Enemy > y_Hero && y_Enemy < y_Hero + height_Hero) {
										if (lastMove == "right") {
											if (x_Enemy <= (x_Hero + (width_Hero / 2) + rangePunch) && x_Enemy >= x_Hero + width_Hero / 2) {
												enemigoActual->setPunched(true);
												enemigosActuales->getEnemigo(i)->setVidas(enemigoActual->getVidas() - 60);
												if (!val_mundo_5) {
													hero->getSounds()[0]->Play();
												}
											}
										}
										else if (lastMove == "left") {
											if (x_Enemy >= (x_Hero + (width_Hero / 2) - rangePunch) && x_Enemy <= x_Hero + width_Hero / 2) {
												enemigoActual->setPunched(true);
												enemigosActuales->getEnemigo(i)->setVidas(enemigoActual->getVidas() - 60);
												if (!val_mundo_5) {
													hero->getSounds()[0]->Play();
												}
											}
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

				if (val_mundo_victoria) {
					falling = true;
					if (hero->getY() == 500) {
						running = false;
						falling = false;
						jumping = false;
						startIndex = 42;
						endIndex = 43;
						static bool win = false;
						if (!win) {
							hero->getSounds()[randnum(7, 11)]->Play();
							heroIndex = startIndex;
							win = true;
							FormEnd^ formEnd = gcnew FormEnd("win");
							formEnd->Show();
						}
						heroIndex += 0.5;
						if (heroIndex > endIndex) {
							heroIndex = startIndex;
						}
					}
				}
			}
		}
		void Timer_Tick(System::Object^ sender, System::EventArgs^ e) {
			Graphics^ g = this->CreateGraphics();
			ValidacionDeEstados();
			CondicionesParaTempo();
			CondicionesParaEnemigos(g);
			CondicionesParaAliados();
			AccionesDelJugador(g);
			this->Invalidate();
		}
		void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
			Graphics^ g = this->CreateGraphics();
			if (!dead) {
				if (punching || shooting) {
					return;
				}
				if (falling || !val_mundo_victoria) {
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
					bool ready = false;
					if (recursosSembrados_Actuales != nullptr && recursosPorSembrar_Actuales != nullptr) {
						if (*recursosSembrados_Actuales >= *recursosPorSembrar_Actuales) {
							ready = true;
						}
					}
					if (boss != nullptr) {
						if (!boss->getAlive()) {
							ready = true;
						}
					}
					if (ready){
						if (e->KeyCode == Keys::G) {
							hero->getSounds()[6]->Play();
							sound = false;
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
								hero->setX(604);
								hero->setY(50);
								val_mundo_4 = false;
								val_mundo_5 = true;
							}
							else if (val_mundo_5) {
								hero->setX(800);
								hero->setY(20);
								val_mundo_5 = false;
								val_mundo_victoria = true;
							}
							imagePortalIndex_b = 0;
							imagePortalIndex_f = 0;
							imageWorldIndex = 0;
							readyToTravelForward = false;
						}
					}
				}
				else if (readyToTravelBackward) {
					if (e->KeyCode == Keys::T) {
						hero->getSounds()[6]->Play();
						sound = false;
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
				else if (e->KeyCode == Keys::P) {
					if (readyToPlant) {
						planted = true;
					}
				}
			}
		}
		void MyForm_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
			if (!val_mundo_victoria) {
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
						int dx = 10;
						if (val_mundo_5) {
							dx = 20;
						}
						if (lastMove == "right") {
							heroIndex = 26;
							hero->getArma()->agregarBala(gcnew Bala(hero->getX() + hero->getWidth(), hero->getY(), dx, 2, 20, 20, images_heroBala));
						}
						else if (lastMove == "left") {
							heroIndex = 27;
							hero->getArma()->agregarBala(gcnew Bala(hero->getX() - 10, hero->getY(), -dx, 2, 20, 20, images_heroBala));
						}
						if (!val_mundo_5) {
							hero->getSounds()[1]->Play();
							Sleep(50);
						}
						hero->setMunicion(hero->getMunicion() - 1);
						shooting = false;
						Sleep(100);
					}
				}
				else if (e->KeyCode == Keys::P) {
					planted = false;
				}
			}
		}
		void MyForm_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
			Graphics^ g = this->CreateGraphics();
			String^ x = e->X.ToString();
			String^ y = e->Y.ToString();
			MessageBox::Show("X: " + x + " Y: " + y);
		}
	};
}
