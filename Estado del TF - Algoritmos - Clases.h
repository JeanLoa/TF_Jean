#pragma once
#include "iostream"
#include "Windows.h"
#include "FormEnd.h"
using namespace System::Media;
using namespace System::Drawing;
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
using namespace System::IO;
// Funciones Auxiliares
Bitmap^ crearSpriteBlanco(Bitmap^ original) {
    // Crear un nuevo bitmap con las mismas dimensiones que el original
    Bitmap^ spriteBlanco = gcnew Bitmap(original->Width, original->Height);

    for (int i = 0; i < original->Width; i++) {
        for (int j = 0; j < original->Height; j++) {
            // Obtener el color del píxel
            Color colorPixel = original->GetPixel(i, j);

            // Si el píxel no es transparente, lo cambiamos a blanco
            if (colorPixel.A > 0) {
                spriteBlanco->SetPixel(i, j, Color::FromArgb(colorPixel.A, 255, 255, 255)); // Color blanco manteniendo transparencia
            }
        }
    }

    return spriteBlanco;
}
Bitmap^ crearSpriteNegro(Bitmap^ original) {
    // Crear un nuevo bitmap con las mismas dimensiones que el original
    Bitmap^ spriteNegro = gcnew Bitmap(original->Width, original->Height);

    for (int i = 0; i < original->Width; i++) {
        for (int j = 0; j < original->Height; j++) {
            // Obtener el color del píxel
            Color colorPixel = original->GetPixel(i, j);

            // Si el píxel no es transparente, lo cambiamos a negro
            if (colorPixel.A > 0) {
                spriteNegro->SetPixel(i, j, Color::FromArgb(colorPixel.A, 0, 0, 0)); // Color negro manteniendo transparencia
            }
        }
    }

    return spriteNegro;
}
int randnum(int min, int max) {
    return min + rand() % (max - min + 1);
}
int randRecurso() {
    int num = randnum(1, 3);
    switch (num) {
    case 1:
        return 0;
    case 2:
        return 2;
    case 3:
        return 4;
    }
}
int randDX() {
    int num = randnum(1, 3);
    switch (num) {
    case 1:
        return 5;
    case 2:
        return 0;
    case 3:
        return -5;
    }
}

int readGuardianIndex() {
    int guardianIndex = 1;  // Valor predeterminado si no existe el archivo

    try {
        if (File::Exists("guardian_index.txt")) {
            // Leer el índice almacenado
            guardianIndex = Convert::ToInt32(File::ReadAllText("guardian_index.txt"));
        }
    }
    catch (Exception^ ex) {
        MessageBox::Show("Error al leer el índice del guardián: " + ex->Message);
    }

    return guardianIndex;
}
void saveGuardianIndex(int guardianIndex) {
    try {
        // Guardar el nuevo índice
        File::WriteAllText("guardian_index.txt", guardianIndex.ToString());
    }
    catch (Exception^ ex) {
        MessageBox::Show("Error al guardar el índice del guardián: " + ex->Message);
    }
}
void updateGuardianIndex() {
    // Leer el índice actual
    int guardianIndex = readGuardianIndex();

    // Incrementar el índice para el siguiente guardián
    guardianIndex++;

    // Guardar el nuevo índice
    saveGuardianIndex(guardianIndex);
}
/*
Clases
*/
// Clase Padre de la mayoría de las clases en el juego
ref class Sprite {
protected:
    int x, y;
    int dx;
    int width, height;
    array<Bitmap^>^ images;
    float index;
    int startIndex, endIndex;
public:
    Sprite(int x, int y, int dx, int w, int h, array<Bitmap^>^imgs, int s_i, int e_i) : x(x), y(y), dx(dx), width(w), height(h), images(imgs) {}
    ~Sprite(){}
    virtual void dibujarSprite(Graphics^ g) = 0;
    int getX() { return this->x; }
    int getY() { return this->y; }
    int getDX() { return this->dx; }
    int getWidth() { return this->width; }
    int getHeight() { return this->height; }
    array<Bitmap^>^ getImages() { return this->images; }
    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
    void setDX(int dx) { this->dx = dx; }
    void setWidth(int w) { this->width = w; }
    void setHeight(int h) { this->height = h; }

    void setIndex(float i) { this->index = i; }
    void setStartIndex(int s_i) { this->startIndex = s_i; }
    void setEndIndex(int e_i) { this->endIndex = e_i; }
    float getIndex() { return this->index; }
    int getStartIndex() { return this->startIndex; }
    int getEndIndex() { return this->endIndex; }
};
// Clase de la vida, hija de Sprite
ref class Vida : public Sprite {
public:
    Vida(int x, int y, int w, int h, array<Bitmap^>^ imgs, int s_i, int e_i) : Sprite(x, y, 0, w, h, imgs, s_i, e_i) {
        this->index = startIndex;
    }
    ~Vida(){}
    void dibujarSprite(Graphics^ g) override {
        g->DrawImage(images[int(index)], x, y, width, height);
    }
};
// Clase de la bala, hija de Sprite
ref class Bala : public Sprite {
public:
    Bala(int x, int y, int dx, int i, int w, int h, array<Bitmap^>^ imgs) : Sprite(x, y, dx, w, h, imgs, 0, 0) {
        if (dx > 0) {
            startIndex = i - i;
            endIndex = i;
        }
        else if (dx < 0) {
            startIndex = i + 1;
            endIndex = i * 2 + 1;
        }
        this->index = startIndex;
        this->y += 20;
    }
    void dibujarSprite(Graphics^ g) override {
        g->DrawImage(images[int(index)], x, y, width, height);
    }
};
// Composición
ref class Balas {
private:
    int n_Balas;
    array<Bala^>^ balas;
public:
    Balas() : n_Balas(0), balas(nullptr){}
    ~Balas(){}
    void agregarBala(Bala^ nuevo) {
        array<Bala^>^ copia = gcnew array<Bala^> (n_Balas + 1);
        for (int i = 0; i < n_Balas; ++i) {
            copia[i] = balas[i];
        }
        copia[n_Balas] = nuevo;
        delete balas;
        balas = copia;
        ++n_Balas;
    }
    void eliminarBala(int indice) {
        delete balas[indice];
        array<Bala^>^ copia = gcnew array<Bala^>(n_Balas + 1);
        for (int i = indice; i < n_Balas - 1; ++i) {
            balas[i] = balas[i + 1];
        }
        for (int i = 0; i < n_Balas - 1; ++i) {
            copia[i] = balas[i];
        }
        delete[] balas;
        balas = copia;
        --n_Balas;
    }
    int getN() {
        return this->n_Balas;
    }
    Bala^ getBala(int indice) {
        return balas[indice];
    }

    void disparar(Graphics^ g) {
        for (int i = n_Balas - 1; i >= 0; --i) {
            Bala^ balaActual = balas[i];
            balaActual->dibujarSprite(g);
            balaActual->setX(balaActual->getX() + balaActual->getDX());
        }
    }
};
// Clase del Heroe, hija de Sprite
ref class Heroe : public Sprite {
private:
    bool attacked;
    int vidas;
    int municion;
    Balas^ arma;
    Vida^ VidaHero;
    array<SoundPlayer^>^ sounds;
    // Movimientos
    float lapse;
    bool sliding;
    float slideStrength = 20.0f;
    float slideSpeed;
    bool running;
    bool movingLeft, movingRight;
    // Salto y caida
    bool jumping;
    bool falling;
    float jumpStrength = 40.0f;
    float gravity = 5.0f;
    float aceleration = 2.0f;
    float jumpSpeed;

    bool punching;
    bool punchingStarted;
    bool shooting;

    bool planted;
    bool readyToPlant;

    int defaultFloor;

    bool dead;
public:
    Heroe(int x, int y, int dx, int w, int h, array<Bitmap^>^ imgs, Vida^ vida, array<SoundPlayer^>^ sounds, int s_i, int e_i) : Sprite(x, y, dx, w, h, imgs, s_i, e_i), VidaHero(vida), sounds(sounds) {
        arma = gcnew Balas;
        this->municion = 10;
        this->vidas = 1000;
        this->attacked = false;
        this->sliding = false;
        this->running = true;
        this->movingRight = false;
        this->movingLeft = false;
        this->jumping = false;
        this->falling = false;
        this->punching = false;
        this->punchingStarted = false;
        this->shooting = false;
        this->planted = false;
        this->defaultFloor = 570;
        this->dead = false;
        this->readyToPlant = false;
    }
    void dibujarSprite(Graphics^ g) override {
        if (!attacked) {
            g->DrawImage(images[int(index)], x, y, width, height);
        }
        else if (attacked) {
            Bitmap^ spriteBlanco = crearSpriteBlanco(images[int(index)]);
            g->DrawImage(spriteBlanco, x, y, width, height);
            attacked = false;
        }
    }
    Balas^ getArma() {
        return this->arma;
    }
    int getMunicion() {
        return this->municion;
    }
    void setMunicion(int municion) {
        if (municion > 20) municion = 20;
        this->municion = municion;
    }
    void setVidas(int vidas) {
        if (vidas > 1000) vidas = 1000;
        this->vidas = vidas;
    }
    int getVidas() { return this->vidas; }
    bool getAttacked() { return this->attacked; }
    void setAttacked(bool attacked) { this->attacked = attacked; }
    float getLapse() { return this->lapse; }
    void setLapse(float lapse) { this->lapse = lapse; }
    bool getSliding() { return this->sliding; }
    void setSliding(bool sliding) { this->sliding = sliding; }
    float getSlideStrength() { return this->slideStrength; }
    float getSlideSpeed() { return this->slideSpeed; }
    void setSlideSpeed(float slideSpeed) { this->slideSpeed = slideSpeed; }
    
    bool getRunning() { return this->running; }
    void setRunning(bool running) { this->running = running; }
    bool getMovingRight() { return this->movingRight; }
    void setMovingRight(bool movingRight) { this->movingRight = movingRight; }
    bool getMovingLeft() { return this->movingLeft; }
    void setMovingLeft(bool movingLeft) { this->movingLeft = movingLeft; }

    bool getFalling() { return this->falling; }
    void setFalling(bool falling) { this->falling = falling; }
    bool getJumping() { return this->jumping; }
    void setJumping(bool jumping) { this->jumping = jumping; }

    float getJumpStrength() { return this->jumpStrength; }
    float getGravity() { return this->gravity; }
    void setGravity(float gravity) { this->gravity = gravity; }
    float getAceleration() { return this->aceleration; }
    float getJumpSpeed() { return this->jumpSpeed; }
    void setJumpSpeed(float jumpSpeed) { this->jumpSpeed = jumpSpeed; }

    bool getPunching() { return this->punching; }
    void setPunching(bool punching) { this->punching = punching; }
    bool getPunchingStarted() { return this->punchingStarted; }
    void setPunchingStarted(bool punchingStarted) { this->punchingStarted = punchingStarted; }
    bool getShooting() { return this->shooting; }
    void setShooting(bool shooting) { this->shooting = shooting; }
    bool getPlanted() { return this->planted; }
    void setPlanted(bool planted) { this->planted = planted; }
    int getDefaultFloor() { return this->defaultFloor; }
    void setDefaultFloor(int defaultFloor) { this->defaultFloor = defaultFloor; }
    bool getReadyToPlant() { return this->readyToPlant; }
    void setReadyToPlant(bool readyToPLant) { this->readyToPlant = readyToPLant; }

    bool getDead() { return this->dead; }
    void setDead(bool dead) { this->dead = dead; }

    Vida^ getVida() { return this->VidaHero; }
    array<SoundPlayer^>^ getSounds() { return this->sounds; }
};
// Clase del Recurso, hija de Sprite
ref class Recurso : public Sprite {
private:
    bool sembrado;
    int index;
public:
    Recurso(int x, int y, int w, int h, array<Bitmap^>^ imgs, int i) : Sprite(x, y, 0, w, h, imgs, 0, 0){
        this->sembrado = false;
        this->index = i;
    }
    void dibujarSprite(Graphics^ g) override {
        if (!sembrado) {
            g->DrawImage(images[index], x, y, width, height);
        }
        else if (sembrado) {
            g->DrawImage(images[index + 1], x, y - height * 1.5, width * 2, height * 4);
        }
    }
    void setSembrado(bool sembrado) {
        this->sembrado = sembrado;
    }
    bool getSembrado() {
        return this->sembrado;
    }
};
// Composición
ref class Recursos {
    array<Recurso^>^ recursos;
    int n_Recursos;
public:
    Recursos() : recursos(nullptr), n_Recursos(0) {}
    ~Recursos() {
        for (int i = 0; i < n_Recursos; ++i) {
            delete recursos[i];
        }
        delete[] recursos;
    }
    void agregarRecurso(Recurso^ nuevo) {
        array<Recurso^>^ copia = gcnew array<Recurso^>(n_Recursos + 1);
        for (int i = 0; i < n_Recursos; ++i) {
            copia[i] = recursos[i];
        }
        copia[n_Recursos] = nuevo;
        delete[] recursos;
        recursos = copia;
        ++n_Recursos;
    }
    Recurso^ getRecurso(int indice) {
        return recursos[indice];
    }
    int getN() {
        return this->n_Recursos;
    }
};
// Clase del aliado, hija de Sprite
ref class Aliado : public Sprite {
public:
    Aliado(int x, int y, int dx, int w, int h, array<Bitmap^>^ imgs) : Sprite(x, y, dx, w, h, imgs, 0, 0) {
        if (randnum(1, 2) == 1) {
            startIndex = 0;
            endIndex = 1;
        }
        else {
            startIndex = 2;
            endIndex = 3;
        }
    }
    void dibujarSprite(Graphics^ g) override {
        g->DrawImage(images[int(index)], x, y, width, height);
    }
    void setIndex(int i) { this->index = i; }
    void setStartIndex(int s_i) { this->startIndex = s_i; }
    void setEndIndex(int e_i) { this->endIndex = e_i; }
    int getIndex() { return this->index; }
    int getStartIndex() { return this->startIndex; }
    int getEndIndex() { return this->endIndex; }
};
// Composición
ref class Aliados {
    array<Aliado^>^ aliados;
    int n_Aliados;
public:
    Aliados() : aliados(nullptr), n_Aliados(0) {}
    ~Aliados() {
        for (int i = 0; i < n_Aliados; ++i) {
            delete aliados[i];
        }
        delete[] aliados;
    }
    void agregarAliado(Aliado^ nuevo) {
        array<Aliado^>^ copia = gcnew array<Aliado^>(n_Aliados + 1);
        for (int i = 0; i < n_Aliados; ++i) {
            copia[i] = aliados[i];
        }
        copia[n_Aliados] = nuevo;
        delete[] aliados;
        aliados = copia;
        ++n_Aliados;
    }
    void eliminarAliado(int indice) {
        delete aliados[indice];
        array<Aliado^>^ copia = gcnew array<Aliado^>(n_Aliados - 1);
        for (int i = indice; i < n_Aliados - 1; ++i) {
            aliados[i] = aliados[i + 1];
        }
        for (int i = 0; i < n_Aliados - 1; ++i) {
            copia[i] = aliados[i];
        }
        delete[] aliados;
        aliados = copia;
        --n_Aliados;
    }
    Aliado^ getAliado(int indice) {
        return aliados[indice];
    }
    int getN() {
        return this->n_Aliados;
    }
};
// Clase del enemigo, hija de Sprite
ref class Enemigo : public Sprite {
private:
    int vidas, daño;
    int gravity;
    bool movingRight = 0, movingLeft = 0;
    bool falling;
    bool punched, shot;
    array<SoundPlayer^>^ sounds;
public:
    Enemigo(int x, int y, int dx, int w, int h, array<Bitmap^>^ imgs, int daño, int vidas, array<SoundPlayer^>^ sounds) : Sprite(x, y, dx, w, h, imgs, 0, 0), sounds(sounds) {
        if (dx > 0) startIndex = 2, endIndex = 4, movingRight = true;
        else if (dx < 0) startIndex = 5, endIndex = 7, movingLeft = true;
        else if (dx == 0) {
            if (randnum(1, 2) == 1) {
                startIndex = 0, endIndex = 0;
            }
            else {
                startIndex = 1, endIndex = 1;
            }
        }
        this->index = randnum(startIndex, endIndex);
        this->falling = false;
        this->punched = false;
        this->shot = false;
        this->gravity = 5;
        this->vidas = vidas;
        this->daño = daño;
    }
    ~Enemigo(){}
    void dibujarSprite(Graphics^ g) override {
        if (!punched && !shot) {
            g->DrawImage(images[int(index)], x, y, width, height);
        }
        else if (punched) {
            Bitmap^ spriteBlanco;
            if (movingRight || index == 0) {
                spriteBlanco = crearSpriteBlanco(images[0]);
            }
            else if (movingLeft || index == 1) {
                spriteBlanco = crearSpriteBlanco(images[1]);
            }
            g->DrawImage(spriteBlanco, x, y, width, height);
            punched = false;
        }
        else if (shot) {
            Bitmap^ spriteNegro;
            if (movingRight || index == 0) {
                spriteNegro = crearSpriteNegro(images[0]);
            }
            else if (movingLeft || index == 1) {
                spriteNegro = crearSpriteNegro(images[1]);
            }
            g->DrawImage(spriteNegro, x, y, width, height);
            shot = false;
        }
    }
    void setDX(int dx) { 
        this->dx = dx;
        if (dx > 0) movingRight = true, movingLeft = false;
        else if (dx < 0) movingLeft = true, movingRight = false;
        if (movingRight) startIndex = 2, endIndex = 4;
        if (movingLeft) startIndex = 5, endIndex = 7;
    }
    void setFall(bool fall) { this->falling = fall; }
    void setGravity(int gravity) { this->gravity = gravity; }
    bool getFall() { return this->falling; }
    int getGravity() { return this->gravity; }

    void setVidas(int vidas) { this->vidas = vidas; }
    int getVidas() { return this->vidas; }
    void setPunched(bool punched) { this->punched = punched; }
    bool getPunched() { return this->punched; }
    void setShot(bool shot) { this->shot = shot; }
    bool getShot() { return this->shot; }
    int getDaño() { return this->daño; }

    array<SoundPlayer^>^ getSounds() { return this->sounds; }
};
// Composición
ref class Enemigos {
private:
    array<Enemigo^>^ enemigos;
    int n_Enemigos;
public:
    Enemigos() : enemigos(nullptr), n_Enemigos(0) {}
    ~Enemigos() {
        for (int i = 0; i < n_Enemigos; ++i) {
            delete enemigos[i];
        }
        delete[] enemigos;
    }
    void agregarEnemigo(Enemigo^ nuevo) {
        array<Enemigo^>^ copia = gcnew array<Enemigo^>(n_Enemigos + 1);
        for (int i = 0; i < n_Enemigos; ++i) {
            copia[i] = enemigos[i];
        }
        copia[n_Enemigos] = nuevo;
        delete[] enemigos;
        enemigos = copia;
        ++n_Enemigos;
    }
    void eliminarEnemigo(int indice) {
        delete enemigos[indice];
        array<Enemigo^>^ copia = gcnew array<Enemigo^>(n_Enemigos - 1);
        for (int i = indice; i < n_Enemigos - 1; ++i) {
            enemigos[i] = enemigos[i + 1];
        }
        for (int i = 0; i < n_Enemigos - 1; ++i) {
            copia[i] = enemigos[i];
        }
        delete[] enemigos;
        enemigos = copia;
        --n_Enemigos;
    }
    Enemigo^ getEnemigo(int indice) {
        return enemigos[indice];
    }
    int getN() {
        return this->n_Enemigos;
    }
};
// Clase del suelo
ref class Suelo {
private:
    int x, y;
    int width, height;
public:
    Suelo(int x, int y, int w, int h) {
        this->x = x;
        this->y = y;
        this->width = w;
        this->height = h;
    }
    ~Suelo() {}
    int getX() {
        return this->x;
    }
    int getY() {
        return this->y;
    }
    int getWidth() {
        return this->width;
    }
    int getHeight() {
        return this->height;
    }
};
// Composición
ref class Suelos {
private:
    array<Suelo^>^ suelos;
    int n_Suelos;
public:
    Suelos() : suelos(nullptr), n_Suelos(0) {}
    ~Suelos() {
        for (int i = 0; i < n_Suelos; ++i) {
            delete suelos[i];
        }
        delete[] suelos;
    }
    void agregarSuelo(Suelo^ nuevo) {
        array<Suelo^>^ copia = gcnew array<Suelo^>(n_Suelos + 1);
        for (int i = 0; i < n_Suelos; ++i) {
            copia[i] = suelos[i];
        }
        copia[n_Suelos] = nuevo;
        delete[] suelos;
        suelos = copia;
        ++n_Suelos;
    }
    Suelo^ getSuelo(int indice) {
        return suelos[indice];
    }
    int getN() {
        return this->n_Suelos;
    }
};
// Clase del portal, hija de Sprite
ref class Portal : public Sprite {
private:
    array<Image^>^ portal;
public:
    Portal(int x, int y, int w, int h, array<Image^>^ prtl, int s_i, int e_i) : Sprite(x, y, 0, w, h, nullptr, s_i, e_i), portal(prtl) {}
    ~Portal() {}
    void dibujarSprite(Graphics^ g) override {
        System::Drawing::Rectangle portalRect = System::Drawing::Rectangle(x, y, width, height);
        g->DrawImage(portal[int(index)], portalRect);
    }
};
// Clase del mundo
ref class Mundo : public Sprite {
private:
    array<Image^>^ imagenes;
public:
    Mundo(int x, int y, int w, int h, array<Image^>^ imagenes, int s_i, int e_i) : Sprite(x, y, 0, w, h, nullptr, s_i, e_i) {
        this->imagenes = imagenes;
        this->index = s_i;
    }
    ~Mundo() {}
    void dibujarSprite(Graphics^ g) override {}
    void dibujarMundo(Graphics^ g, int index) {
        float brightness = 1.0f; // Valor predeterminado de brillo
        System::Drawing::Imaging::ColorMatrix^ colorMatrix = gcnew System::Drawing::Imaging::ColorMatrix();
        System::Drawing::Imaging::ImageAttributes^ imageAttributes = gcnew System::Drawing::Imaging::ImageAttributes();

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

        System::Drawing::Rectangle destRect = System::Drawing::Rectangle(0, 0, width * 1.59, height * 1.435);
        g->DrawImage(imagenes[int(this->index)], destRect, x, y, width, height, System::Drawing::GraphicsUnit::Pixel, imageAttributes);
    }
    int getX() {
        return this->x;
    }
    int getY() {
        return this->y;
    }
    int getWidth() {
        return this->width;
    }
    int getHeight() {
        return this->height;
    }
    array<Image^>^ getImagenes() {
        return this->imagenes;
    }
};
// Clase del temporizador, hija de Sprite
ref class Temporizador : public Sprite {
    bool activo;
    int color;
public:
    Temporizador(int x, int y, int w, int h, array<Bitmap^>^ imgs, int color) : Sprite(x, y, 0, w, h, imgs, 60, 0){
        this->index = 60;
        this->activo = true;
        this->color = color;
    }
    ~Temporizador(){}
    void dibujarSprite(Graphics^ g) override {
        if (activo) {
            if (color == 0) {
                Bitmap^ temporizadorBlanco = crearSpriteBlanco(images[int(index)]);
                g->DrawImage(temporizadorBlanco, x, y, width, height);
            }
            else {
                g->DrawImage(images[int(index)], x, y, width, height);
            }
        }
        else if (!activo) {
            this->index = 61;
            if (color == 0) {
                Bitmap^ temporizadorBlanco = crearSpriteBlanco(images[int(index)]);
                g->DrawImage(temporizadorBlanco, x, y, width, height);
            }
            else {
                g->DrawImage(images[int(index)], x, y, width, height);
            }
        }
    }
    void setIndex(float i) {
        if (i > 60) i = 60;
        this->index = i;
    }
    void setActivo(bool activo) { this->activo = activo; };
    bool getActivo() { return this->activo; }
};
// Clase del Jefe, hija de Sprite
ref class Boss : public Sprite {
private:
    int vidas;
    int daño;
    bool attacked;
    Vida^ vida;
    Balas^ bolas;
    bool alive;

    float lapse;
    bool seingLeft;
    bool seingRight;

    int centerX, centerY;   // Centro de la espiral
    double angle;           // Ángulo para el movimiento circular
    double radius;          // Radio de la espiral
    double maxRadius;       // Máximo radio de expansión
    bool expanding;         // Bandera para saber si estamos expandiendo o contrayendo
public:
    Boss(int x, int y, int w, int h, array<Bitmap^>^ imgs, int s_i, int e_i, int vidas, int daño, Vida^ vida) : Sprite(x, y, 0, w, h, imgs, s_i, e_i), vidas(vidas), daño(daño), vida(vida) {
        
        bolas = gcnew Balas;
        this->lapse = 0;
        this->seingLeft = false;
        this->seingRight = false;
        this->attacked = false;
        this->alive = true;
        // Centro de la espiral basado en el tamaño de la ventana
        this->centerX = x;
        this->centerY = y;

        this->angle = 0;             // Ángulo inicial
        this->radius = 50;           // Radio inicial
        this->maxRadius = 500;       // Máximo radio de expansión (ajustable)
        this->expanding = true;      // Inicia en expansión
    }
    ~Boss() {}
    void dibujarSprite(Graphics^ g) override {
        if (x + width / 2 < g->VisibleClipBounds.Width / 2) {
            seingRight = true;
            seingLeft = false;
            startIndex = 0;
            endIndex = 3;
        }
        else if (x + width / 2 > g->VisibleClipBounds.Width / 2) {
            seingLeft = true;
            seingRight = false;
            startIndex = 4; 
            endIndex = 7;
        }

        if (!attacked) {
            g->DrawImage(images[int(index)], x, y, width, height);
        }
        else if (attacked) {
            Bitmap^ spriteBlanco;
            spriteBlanco = crearSpriteBlanco(images[int(index)]);
            g->DrawImage(spriteBlanco, x, y, width, height);
            attacked = false;
        }
    }
    void movimientoEspiral(Graphics^ g) {
        // Definimos las velocidades y otras variables
        static double angle = 0;          // ángulo inicial para el movimiento circular
        double angularSpeed = 0.05;       // velocidad angular para el movimiento circular
        double radialSpeed = 10.0;        // velocidad de expansión/contracción del radio

        // Aumenta el ángulo para el movimiento circular
        angle += angularSpeed;

        // Ajusta el radio según el estado de expansión o contracción
        if (expanding) {
            radius += radialSpeed;
            if (radius >= maxRadius) expanding = false; // Cambia a contracción al alcanzar el máximo
        }
        else {
            radius -= radialSpeed;
            if (radius <= 20) expanding = true;  // Cambia a expansión al alcanzar el mínimo
        }

        // Calcula el desplazamiento a partir del ángulo y el radio
        int offsetX = (int)(Math::Cos(angle) * radius);
        int offsetY = (int)(Math::Sin(angle) * radius);

        // Aplica el desplazamiento calculado a las coordenadas actuales de x e y
        // Centro de la espiral basado en centerX y centerY
        x = centerX + offsetX;
        y = centerY + offsetY;

        // Asegúrate de que x e y estén dentro de los límites de la ventana
        int maxWidth = g->VisibleClipBounds.Width;
        int maxHeight = g->VisibleClipBounds.Height;

        // Restringe las posiciones dentro de los límites de la ventana
        x = Math::Max(0, Math::Min(maxWidth - width, x));
        y = Math::Max(0, Math::Min(maxHeight - height, y));
    }

    void setAttacked(bool attacked) { this->attacked = attacked; }
    void setVidas(int vidas) { 
        if (vidas < 0) vidas = 0;
        this->vidas = vidas;
    }
    bool getSeingRight() { return this->seingRight; }
    bool getSeingLeft() { return this->seingLeft; }
    bool getAttacked() { return this->attacked; }
    int getVidas() { return this->vidas; }
    int getDaño() { return this->daño; }
    Vida^ getVida() { return this->vida; }
    Balas^ getArma() { return this->bolas; }

    void setLapse(float lapse) { this->lapse = lapse; }
    float getLapse() { return this->lapse; }

    void setAlive(bool alive) { this->alive = alive; }
    bool getAlive() { return this->alive; }
};
// Clase GMA - Controladora
ref class GMA {
private:
    Heroe^ hero;
    bool sound;
    SoundPlayer^ Final_music;
    SoundPlayer^ musicaActual;

    int margendeErrorY = 20;
    int margendeErrorX = 35;

    String^ lastMove = "";

    Portal^ portal_1_f;
    Portal^ portal_2_f;
    Portal^ portal_3_f;
    Portal^ portal_4_f;
    Portal^ portal_5_f;

    Portal^ portal_2_b;
    Portal^ portal_3_b;
    Portal^ portal_4_b;

    Portal^ portalActual_f;
    Portal^ portalActual_b;

    Aliados^ aliados_1;
    Aliados^ aliados_2;
    Aliados^ aliados_3;
    Aliados^ aliados_4;
    Aliados^ aliadosActuales;

    Recursos^ recursos_1;
    Recursos^ recursos_2;
    Recursos^ recursos_3;
    Recursos^ recursos_4;
    Recursos^ recursosActuales;
    array<Bitmap^>^ imagesRecurso;

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

    String^ end = "";

    float lapseFile;
public:
    // Constructor
    GMA(Graphics^ g) {
        lapseFile = 11;
        LoadHero();
        LoadBoss(g);
        LoadMusics();
        LoadRecursos();
        LoadTempos(g);
        LoadBullets();
        LoadFloors();
        LoadAllies(g);
        LoadWorlds();
        LoadPortals();
        LoadMessage();
        LoadEnemies(g);
    }
    // Destructor
    ~GMA() {}
    // Funciones para la lectura y escritura del código
    void saveBin() {
        int guardianIndex = readGuardianIndex();

        if (!Directory::Exists("datos")) {
            Directory::CreateDirectory("datos");
        }
        String^ filePath = "datos\\puntaje.bin";

        FileStream^ fileBin = gcnew FileStream(filePath, FileMode::Append, FileAccess::Write);
        BinaryWriter^ bin = gcnew BinaryWriter(fileBin);

        DateTime^ fecha = DateTime::Now;
        int puntaje = 0;
        if (recursosSembrados_Actuales != nullptr) {
            puntaje = *recursosSembrados_Actuales;
        }
        else if (val_mundo_5) {
            puntaje = 5000 + (boss->getVidas() * -1);
        }
        else {
            puntaje = 10;
        }
        String^ nombre = "Guardian " + guardianIndex.ToString();

        try {
            // Escribir los datos del nuevo guardián
            bin->Write(nombre);
            bin->Write(puntaje);            // Escribir el puntaje
            bin->Write(fecha->ToBinary());  // Convertir la fecha a formato binario
        }
        catch (Exception^ ex) {
            MessageBox::Show("Error al escribir el archivo binario: " + ex->Message);
        }
        finally {
            bin->Close();
            fileBin->Close();
        }
    }
    void saveTXT() {
        if (!Directory::Exists("datos")) {
            Directory::CreateDirectory("datos");
        }
        String^ filePath = "datos\\configuracion.txt";
        String^ data = Convert::ToString(enemigosActuales->getN()) + "," + Convert::ToString(aliadosActuales->getN()) + "," + Convert::ToString(temporizadorActual->getIndex());
        StreamWriter^ fileTXT = gcnew StreamWriter(filePath, true);
        try {
            fileTXT->WriteLine(data);
        }
        catch (Exception^ ex) {
            MessageBox::Show("Error al escribir el archivo de texto" + ex->Message);
        }
        finally {
            fileTXT->Close();
        }
    }
    float getLapseFiles() { return this->lapseFile; }
    void setLapseFiles(float lapseFile) { this->lapseFile = lapseFile; }

    // Funciones para el constructor
    void getRandHelp(Timer^ Timer) {
        Timer->Stop();
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
        Timer->Start();
    }
    void LoadBoss(Graphics^ g) {
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

        boss = gcnew Boss(g->VisibleClipBounds.Width / 2 - 160, g->VisibleClipBounds.Height / 2 - 140, 400, 400, images, 0, 3, 5000, 50, vidaBoss);
    }
    void LoadMusics() {
        Final_music = gcnew SoundPlayer("Musicas\\Musica_GMA_Mundo5.wav");
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
    }
    void LoadTempos(Graphics^ g) {
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
        int x = (g->VisibleClipBounds.Width - width) / 2 - 1;
        int y = -5;
        temporizador_1 = gcnew Temporizador(x, y, width, height, images, 1);
        temporizador_2 = gcnew Temporizador(x, y, width, height, images, 1);
        temporizador_3 = gcnew Temporizador(x, y, width, height, images, 1);
        temporizador_4 = gcnew Temporizador(x, y, width, height, images, 1);
        temporizador_5 = gcnew Temporizador(x, y, width, height, images, 0);
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
    void LoadAllies(Graphics^ g) {
        array<Bitmap^>^ images = gcnew array<Bitmap^>(4) {
            gcnew Bitmap("Imagenes\\Aliado\\AllieRight1.png"),
                gcnew Bitmap("Imagenes\\Aliado\\AllieRight2.png"),
                gcnew Bitmap("Imagenes\\Aliado\\AllieLeft1.png"),
                gcnew Bitmap("Imagenes\\Aliado\\AllieLeft2.png")
        };
        aliados_1 = gcnew Aliados;
        generarAliados(aliados_1, images, g);
        aliados_2 = gcnew Aliados;
        generarAliados(aliados_2, images, g);
        aliados_3 = gcnew Aliados;
        generarAliados(aliados_3, images, g);
        aliados_4 = gcnew Aliados;
        generarAliados(aliados_4, images, g);
    }
    void generarAliados(Aliados^ allies, array<Bitmap^>^ imgs, Graphics^ g) {
        for (int i = 0; i < 3; ++i) {
            allies->agregarAliado(gcnew Aliado((g->VisibleClipBounds.Width / 3) * (i + 0.5), hero->getDefaultFloor(), 0, 80, 80, imgs));
        }
    }
    void LoadEnemies(Graphics^ g) {
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
        generarEnemigos(enemigos_1, images, suelos_1, 300, 30, 11, sound, g);
        recursosPorSembrar_1 = int(11 * 0.7);

        enemigos_2 = gcnew Enemigos;
        generarEnemigos(enemigos_2, images, suelos_2, 400, 40, 12, sound, g);
        recursosPorSembrar_2 = int(12 * 0.7);

        enemigos_3 = gcnew Enemigos;
        generarEnemigos(enemigos_3, images, suelos_3, 500, 50, 13, sound, g);
        recursosPorSembrar_3 = int(13 * 0.7);

        enemigos_4 = gcnew Enemigos;
        generarEnemigos(enemigos_4, images, suelos_4, 600, 60, 14, sound, g);
        recursosPorSembrar_4 = int(14 * 0.7);
    }
    void generarEnemigos(Enemigos^ enemies, array<Bitmap^>^ imgs, Suelos^ suelos, int vidas, int daño, int n, array<SoundPlayer^>^ sounds, Graphics^ g) {
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
            enemies->agregarEnemigo(gcnew Enemigo(x, y, randDX(), 80, 80, imgs, daño, vidas, sounds));
        }
        for (int i = 9; i < n; ++i) {
            enemies->agregarEnemigo(gcnew Enemigo(g->VisibleClipBounds.Width / (n - 9) * (i - 9 + 0.5), hero->getDefaultFloor(), randDX(), 80, 80, imgs, daño, vidas, sounds));
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
        }, 0, 0);
        portal_2_f = gcnew Portal(357, 70, 140, 180, gcnew array<Image^>(4) {
            Image::FromFile("Imagenes\\Portales\\Portal2_0.jpg"),
                Image::FromFile("Imagenes\\Portales\\Portal2_1.jpg"),
                Image::FromFile("Imagenes\\Portales\\Portal2_2.jpg"),
                Image::FromFile("Imagenes\\Portales\\Portal2_3.jpg")
        }, 0, 3);
        portal_3_f = gcnew Portal(1182, 140, 140, 180, gcnew array<Image^>(4) {
            Image::FromFile("Imagenes\\Portales\\Portal3_0.jpg"),
                Image::FromFile("Imagenes\\Portales\\Portal3_1.jpg"),
                Image::FromFile("Imagenes\\Portales\\Portal3_2.jpg"),
                Image::FromFile("Imagenes\\Portales\\Portal3_3.jpg")
        }, 0, 3);
        portal_4_f = gcnew Portal(172, 179, 196, 166, gcnew array<Image^>(4) {
            Image::FromFile("Imagenes\\Portales\\Portal4_0.png"),
                Image::FromFile("Imagenes\\Portales\\Portal4_1.png"),
                Image::FromFile("Imagenes\\Portales\\Portal4_2.png"),
                Image::FromFile("Imagenes\\Portales\\Portal4_3.png")
        }, 0, 3);
        portal_5_f = gcnew Portal(666, 366, 196, 166, gcnew array<Image^>(8) {
            Image::FromFile("Imagenes\\Portales\\Portal5_0.png"),
                Image::FromFile("Imagenes\\Portales\\Portal5_1.png"),
                Image::FromFile("Imagenes\\Portales\\Portal5_2.png"),
                Image::FromFile("Imagenes\\Portales\\Portal5_3.png"),
                Image::FromFile("Imagenes\\Portales\\Portal5_4_0.png"),
                Image::FromFile("Imagenes\\Portales\\Portal5_4_1.png"),
                Image::FromFile("Imagenes\\Portales\\Portal5_4_2.png"),
                Image::FromFile("Imagenes\\Portales\\Portal5_4_3.png")
        }, 0, 0);

        portal_2_b = gcnew Portal(1330, 515, 80, 120, gcnew array<Image^>(1) {
            Image::FromFile("Imagenes\\Portales\\Portal1.jpg")
        }, 0, 0);
        portal_3_b = gcnew Portal(160, 455, 140, 180, gcnew array<Image^>(4) {
            Image::FromFile("Imagenes\\Portales\\Portal2_0.jpg"),
                Image::FromFile("Imagenes\\Portales\\Portal2_1.jpg"),
                Image::FromFile("Imagenes\\Portales\\Portal2_2.jpg"),
                Image::FromFile("Imagenes\\Portales\\Portal2_3.jpg")
        }, 0, 3);
        portal_4_b = gcnew Portal(1330, 455, 140, 180, gcnew array<Image^>(4) {
            Image::FromFile("Imagenes\\Portales\\Portal3_0.jpg"),
                Image::FromFile("Imagenes\\Portales\\Portal3_1.jpg"),
                Image::FromFile("Imagenes\\Portales\\Portal3_2.jpg"),
                Image::FromFile("Imagenes\\Portales\\Portal3_3.jpg")
        }, 0, 3);
    }
    void LoadWorlds() {
        mundo_1 = gcnew Mundo(0, 0, 2457, 1335, gcnew array<Image^>(1) {
            Image::FromFile("Imagenes\\Mundos\\Mundo1.jpg")
        }, 0, 0);
        mundo_2 = gcnew Mundo(0, 0, 2457, 1335, gcnew array<Image^>(1) {
            Image::FromFile("Imagenes\\Mundos\\Mundo2.jpg")
        }, 0, 0);
        mundo_3 = gcnew Mundo(0, 0, 2457, 1335, gcnew array<Image^>(2) {
            Image::FromFile("Imagenes\\Mundos\\Mundo3_0.jpg"),
                Image::FromFile("Imagenes\\Mundos\\Mundo3_1.jpg")
        }, 0, 1);
        mundo_4 = gcnew Mundo(0, 0, 2457, 1335, gcnew array<Image^>(3) {
            Image::FromFile("Imagenes\\Mundos\\Mundo4_0.jpg"),
                Image::FromFile("Imagenes\\Mundos\\Mundo4_1.jpg"),
                Image::FromFile("Imagenes\\Mundos\\Mundo4_2.jpg")
        }, 0, 2);
        mundo_5 = gcnew Mundo(0, 0, 2457, 1335, gcnew array<Image^>(5) {
            Image::FromFile("Imagenes\\Mundos\\Mundo5_0.jpg"),
                Image::FromFile("Imagenes\\Mundos\\Mundo5_1.jpg"),
                Image::FromFile("Imagenes\\Mundos\\Mundo5_2.jpg"),
                Image::FromFile("Imagenes\\Mundos\\Mundo5_3.jpg"),
                Image::FromFile("Imagenes\\Mundos\\Mundo5_4.jpg"),
        }, 0, 4);
        mundo_victoria = gcnew Mundo(0, 0, 2457, 1335, gcnew array<Image^>(1) {
            Image::FromFile("Imagenes\\Mundos\\MundoVictoria.jpg"),
        }, 0, 0);
    }
    void LoadHero() {
        array<Bitmap^>^ sprites = gcnew array<Bitmap^>(44);

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
        hero = gcnew Heroe(100, 570, 10, 80, 80, sprites, vida, sounds, 0, 1);
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
    // Funciones para el Paint
    void Dibujar(Graphics^ g) {
        if (mundoActual != nullptr) {
            int index = 60;
            if (temporizadorActual != nullptr) {
                index = temporizadorActual->getIndex();
            }
            mundoActual->dibujarMundo(g, index);
            if (portalActual_f != nullptr) {
                portalActual_f->dibujarSprite(g);
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
                }
            }
            if (portalActual_b != nullptr) {
                portalActual_b->dibujarSprite(g);
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
                    g->DrawImage(messages_b[messageIndex], System::Drawing::Rectangle(mensajeX, mensajeY, mensajeAncho, mensajeAlto), 0, 0, mensajeAncho, mensajeAlto, GraphicsUnit::Pixel);
                }
            }
        }
        if (enemigosActuales != nullptr) {
            for (int i = 0; i < enemigosActuales->getN(); ++i) {
                Enemigo^ enemigoActual = enemigosActuales->getEnemigo(i);
                enemigoActual->dibujarSprite(g);
            }
        }
        if (aliadosActuales != nullptr) {
            for (int i = 0; i < aliadosActuales->getN(); ++i) {
                Aliado^ aliadoActual = aliadosActuales->getAliado(i);
                aliadoActual->dibujarSprite(g);
            }
        }
        if (temporizadorActual != nullptr) {
            temporizadorActual->dibujarSprite(g);
        }
        if (hero->getArma() != nullptr) {
            hero->getArma()->disparar(g);
        }
        if (hero != nullptr) {
            hero->dibujarSprite(g);
            if (!val_mundo_victoria) {
                hero->getVida()->dibujarSprite(g);
            }
        }
        if (recursosActuales != nullptr) {
            for (int i = 0; i < recursosActuales->getN(); ++i) {
                Recurso^ recursoActual = recursosActuales->getRecurso(i);
                recursoActual->dibujarSprite(g);
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
                        hero->setReadyToPlant(true);
                        int mensajeAncho = messageRecurso[messageIndex]->Width;
                        int mensajeAlto = messageRecurso[messageIndex]->Height;

                        // Calcular la posición de la imagen centrada horizontalmente sobre el portal
                        int mensajeX = recursoActual->getX() + (recursoActual->getWidth() / 2) - (mensajeAncho / 2);
                        int mensajeY = recursoActual->getY() - mensajeAlto;

                        g->DrawImage(messageRecurso[messageIndex], mensajeX, mensajeY, mensajeAncho, mensajeAlto);
                    }
                }
            }
        }
        if (val_mundo_5) {
            if (boss->getAlive()) {
                boss->getArma()->disparar(g);
                boss->dibujarSprite(g);
            }
            boss->getVida()->dibujarSprite(g);
        }
    }
    void ValidacionMundo() {
        if (val_mundo_1) {
            hero->setDefaultFloor(570);
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

            mundoActual->setStartIndex(0);
            mundoActual->setEndIndex(0);

            portalActual_f->setStartIndex(0);
            portalActual_f->setEndIndex(0);
        }
        else if (val_mundo_2) {
            hero->setDefaultFloor(570);
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

            mundoActual->setStartIndex(0);
            mundoActual->setEndIndex(0);

            portalActual_f->setStartIndex(0);
            portalActual_f->setEndIndex(3);

            portalActual_b->setStartIndex(0);
            portalActual_b->setEndIndex(0);
        }
        else if (val_mundo_3) {
            hero->setDefaultFloor(570);
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

            mundoActual->setStartIndex(0);
            mundoActual->setEndIndex(1);

            portalActual_f->setStartIndex(0);
            portalActual_f->setEndIndex(3);

            portalActual_b->setStartIndex(0);
            portalActual_b->setEndIndex(3);
        }
        else if (val_mundo_4) {
            hero->setDefaultFloor(570);
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

            mundoActual->setStartIndex(0);
            mundoActual->setEndIndex(2);

            portalActual_f->setStartIndex(0);
            portalActual_f->setEndIndex(3);

            portalActual_b->setStartIndex(0);
            portalActual_b->setEndIndex(3);
        }
        else if (val_mundo_5) {
            hero->setDefaultFloor(3000);
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
                portalActual_f->setStartIndex(0);
                portalActual_f->setEndIndex(0);

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
                portalActual_f->setStartIndex(1);
                portalActual_f->setEndIndex(1);
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
                portalActual_f->setStartIndex(2);
                portalActual_f->setEndIndex(2);
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
                portalActual_f->setStartIndex(3);
                portalActual_f->setEndIndex(3);
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
                portalActual_f->setStartIndex(3);
                portalActual_f->setEndIndex(3);
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
                portalActual_f->setStartIndex(4);
                portalActual_f->setEndIndex(7);
                boss->getVida()->setStartIndex(25);
                boss->getVida()->setEndIndex(25);
                boss->setAlive(false);
            }
            mundoActual->setStartIndex(0);
            mundoActual->setEndIndex(4);
        }
        else if (val_mundo_victoria) {
            hero->setWidth(160);
            hero->setHeight(160);
            hero->setDefaultFloor(500);
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

            mundoActual->setStartIndex(0);
            mundoActual->setEndIndex(0);
        }
    }
    void ReproduccionDelMundo(Graphics^ g, Timer^% Timer) {
        if (!sound && musicaActual != nullptr) {
            musicaActual->PlayLooping();
            sound = true;
        }
        if (mundoActual != nullptr) {
            mundoActual->setIndex(mundoActual->getIndex() + 1);
            if (mundoActual->getIndex() > mundoActual->getEndIndex()) {
                mundoActual->setIndex(mundoActual->getStartIndex());
            }
            if (portalActual_f != nullptr) {

                portalActual_f->setIndex(portalActual_f->getIndex() + 1);
                if (portalActual_f->getIndex() > portalActual_f->getEndIndex()) {
                    portalActual_f->setIndex(portalActual_f->getStartIndex());
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

                portalActual_b->setIndex(portalActual_b->getIndex() + 1);
                if (portalActual_b->getIndex() > portalActual_b->getEndIndex()) {
                    portalActual_b->setIndex(portalActual_b->getStartIndex());
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
            if (!hero->getDead()) {
                if (temporizadorActual->getIndex() <= 0 || hero->getVidas() <= 0) {
                    hero->setDead(true);
                    if (hero->getMovingRight() || lastMove == "right") {
                        hero->setStartIndex(36);
                        hero->setEndIndex(38);
                    }
                    else if (hero->getMovingLeft() || lastMove == "left") {
                        hero->setStartIndex(39);
                        hero->setEndIndex(41);
                    }
                    hero->setIndex(hero->getStartIndex());
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
            if (hero->getDead() && !deadStarted) {
                hero->setAttacked(false);
                deadStarted = true;
                hero->getSounds()[5]->Play();
                Timer->Interval = 500;
            }
            if (hero->getAttacked()) {
                Sleep(300);
            }
            if (hero->getVida() != nullptr) {
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
                        hero->setReadyToPlant(true);

                        messageIndex++;
                        if (messageIndex > 1) {
                            messageIndex = 0;
                        }
                        if (hero->getPlanted()) {
                            ++(*recursosSembrados_Actuales);
                            recursoActual->setSembrado(true);
                            hero->setPlanted(false);
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
    // Funciones para el Tick
    void ValidacionDeEstados(Timer^% Timer) {
        if (hero->getDead()) {
            hero->setIndex(hero->getIndex() + 1);
            if (hero->getIndex() > hero->getEndIndex()) {
                end = "lose";
                Timer->Stop();
                return;
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
    void CondicionesParaAliados(Timer^ Timer) {
        if (!hero->getDead()) {
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
                        getRandHelp(Timer);
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
    void CondicionesParaEnemigos(Graphics^ g) {
        if (!hero->getDead()) {
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
                            else if (pieSpriteY > hero->getDefaultFloor() + margendeErrorY * 2) {
                                enemigoActual->setFall(false);
                                break;
                            }
                            else {
                                enemigoActual->setFall(true);
                            }
                        }
                        if (enemigoActual->getFall() == true) {

                            enemigoActual->setY(enemigoActual->getY() + enemigoActual->getGravity());
                            enemigoActual->setGravity(enemigoActual->getGravity() + hero->getAceleration());
                            if (enemigoActual->getY() + enemigoActual->getHeight() > hero->getDefaultFloor() + margendeErrorY * 3) {

                                enemigoActual->setY(hero->getDefaultFloor());
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
                            enemigoActual->getX() <= sueloX + sueloWidth - margendeErrorX * 3.5 || enemigoActual->getY() == hero->getDefaultFloor()) {
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
    void AccionesDelJugador(Graphics^ g) {
        if (!hero->getDead()) {
            if (!hero->getFalling()) {
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
                            hero->setFalling(false);
                            break;
                        }
                        if (pieSpriteY > hero->getDefaultFloor() + margendeErrorY * 2) {
                            hero->setFalling(false);
                        }
                        else {
                            hero->setFalling(true);
                        }
                    }
                }
            }

            // Actualiza la posición del sprite al moverse
            if (hero->getSliding()) {
                if (lastMove == "right" || hero->getMovingRight()) {
                    hero->setX(hero->getX() + hero->getSlideSpeed());
                    lastMove = "right";  // Guarda la última dirección
                }
                else if (lastMove == "left" || hero->getMovingLeft()) {
                    hero->setX(hero->getX() - hero->getSlideSpeed());
                    lastMove = "left";  // Guarda la última dirección
                }
                hero->setSlideSpeed(hero->getSlideSpeed() * 0.95);
                if (hero->getX() < 0) {
                    hero->setX(0);
                }
                else if (hero->getX() + hero->getWidth() > g->VisibleClipBounds.Width) {
                    hero->setX(g->VisibleClipBounds.Width - hero->getWidth());
                }
            }
            if (hero->getRunning() || hero->getJumping() || hero->getFalling()) {
                joining = false;
                if (hero->getMovingRight()) {
                    hero->setX(hero->getX() + hero->getDX());
                    lastMove = "right";  // Guarda la última dirección
                }
                else if (hero->getMovingLeft()) {
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
            if (hero->getRunning()) {
                if (hero->getMovingRight()) {
                    hero->setStartIndex(4); // Primer sprite de movimiento a la derecha
                    hero->setEndIndex(6);   // Último sprite de movimiento a la derecha
                }
                else if (hero->getMovingLeft()) {
                    hero->setStartIndex(7); // Primer sprite de movimiento a la izquierda
                    hero->setEndIndex(9);   // Último sprite de movimiento a la izquierda
                }
                else { // Si no se está moviendo
                    if (lastMove == "right") {
                        hero->setStartIndex(0); // Último sprite estático mirando a la derecha
                        hero->setEndIndex(1);   // Mantener el mismo sprite
                    }
                    else if (lastMove == "left") {
                        hero->setStartIndex(2); // Último sprite estático mirando a la izquierda
                        hero->setEndIndex(3);   // Mantener el mismo sprite
                    }
                }
                hero->setIndex(hero->getIndex() + 1);
                if (hero->getIndex() > hero->getEndIndex()) {
                    hero->setIndex(hero->getStartIndex());
                }
                if (hero->getX() == 0) {
                    hero->setIndex(31);
                }
                else if (hero->getX() + hero->getWidth() == g->VisibleClipBounds.Width) {
                    hero->setIndex(30);
                }
            }
            if (hero->getJumping()) {
                hero->setPunching(false);
                hero->setShooting(false);
                hero->setRunning(false);
                if (hero->getJumpSpeed() > 0) {
                    // Mostrar el sprite inicial de salto
                    if (hero->getJumpSpeed() == hero->getJumpStrength()) {
                        if (lastMove == "right" || hero->getMovingRight()) {
                            hero->setIndex(10);
                        }
                        else if (lastMove == "left" || hero->getMovingLeft()) {
                            hero->setIndex(12);
                        }
                        hero->setJumpSpeed(hero->getJumpSpeed() - hero->getGravity());
                    }
                    else {
                        // Mantener el sprite de estar en el aire
                        if (lastMove == "right" || hero->getMovingRight()) {
                            hero->setIndex(11);
                        }
                        else if (lastMove == "left" || hero->getMovingLeft()) {
                            hero->setIndex(13);
                        }
                        hero->setY(hero->getY() - hero->getJumpSpeed());
                        hero->setJumpSpeed(hero->getJumpSpeed() - hero->getGravity());
                    }
                    // Colisión con la parte superior
                    if (hero->getY() < 22) {
                        hero->setY(22);
                        hero->setJumping(false);
                        hero->setFalling(true);
                        hero->setJumpSpeed(0);
                    }
                }
                else {
                    hero->setJumping(false);
                    hero->setFalling(true);
                    hero->setJumpSpeed(0);
                }
            }
            else if (hero->getFalling()) {
                hero->setPunching(false);
                hero->setShooting(false);
                if (lastMove == "right" || hero->getMovingRight()) {
                    hero->setIndex(14);
                }
                else if (lastMove == "left" || hero->getMovingLeft()) {
                    hero->setIndex(16);
                }

                if (hero->getX() == 0) {
                    hero->setIndex(33);
                }
                else if (hero->getX() + hero->getWidth() == g->VisibleClipBounds.Width) {
                    hero->setIndex(32);
                }

                hero->setY(hero->getY() + hero->getGravity());
                hero->setGravity(hero->getGravity() + hero->getAceleration());
                if (hero->getY() + hero->getHeight() > hero->getDefaultFloor() + margendeErrorY * 3) {
                    if (lastMove == "right" || hero->getMovingRight()) {
                        hero->setIndex(15);
                    }
                    else if (lastMove == "left" || hero->getMovingLeft()) {
                        hero->setIndex(17);
                    }

                    hero->setY(hero->getDefaultFloor());
                    hero->setFalling(false);
                    hero->setRunning(true);
                    hero->setGravity(5);
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
                            hero->setFalling(false);
                            hero->setRunning(true);
                            hero->setGravity(5);
                        }
                    }
                }
                if (hero->getY() + hero->getHeight() > 750) {
                    hero->setVidas(hero->getVidas() - 60);
                    hero->setAttacked(true);
                    hero->setJumpSpeed(hero->getJumpStrength());
                    hero->setJumping(true);
                    hero->setFalling(false);
                    hero->setRunning(false);
                    hero->setSliding(false);
                    hero->setGravity(5);
                }
            }
            if (hero->getSliding()) {
                hero->setLapse(hero->getLapse() + 0.1);
                if (lastMove == "right" || hero->getMovingRight()) {
                    hero->setIndex(28);
                }
                else if (lastMove == "left" || hero->getMovingLeft()) {
                    hero->setIndex(29);
                }
                if (hero->getLapse() > 1.5) {
                    hero->setRunning(true);
                    hero->setSliding(false);
                    hero->setLapse(0);
                }
            }

            if (hero->getPunching()) {
                hero->setRunning(false);
                if (!hero->getPunchingStarted()) {
                    if (lastMove == "right") {
                        hero->setStartIndex(18);
                        hero->setEndIndex(21);
                    }
                    else if (lastMove == "left") {
                        hero->setStartIndex(22);
                        hero->setEndIndex(25);
                    }
                    hero->setIndex(hero->getStartIndex());
                    hero->setPunchingStarted(true);
                }
                else if (hero->getPunchingStarted()) {
                    hero->setIndex(hero->getIndex() + 1);
                    if (hero->getIndex() > hero->getEndIndex()) {
                        hero->setIndex(hero->getStartIndex());
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

            if (hero->getShooting()) {
                hero->setRunning(false);
                if (lastMove == "right") {
                    hero->setIndex(26);
                }
                else if (lastMove == "left") {
                    hero->setIndex(27);
                }
            }

            if (joining) {
                hero->setIndex(35);
            }

            if (val_mundo_victoria) {
                hero->setFalling(true);
                if (hero->getY() == 500) {
                    hero->setRunning(false);
                    hero->setFalling(false);
                    hero->setJumping(false);
                    hero->setStartIndex(42);
                    hero->setEndIndex(43);
                    static bool win = false;
                    if (!win) {
                        hero->getSounds()[randnum(7, 11)]->Play();
                        hero->setIndex(hero->getStartIndex());
                        win = true;
                        end = "win";
                    }
                    hero->setIndex(hero->getIndex() + 0.5);
                    if (hero->getIndex() > hero->getEndIndex()) {
                        hero->setIndex(hero->getStartIndex());
                    }
                }
            }
        }
    }
    // Funciones para las teclas
    void TeclasPulsadas(KeyEventArgs^ e, Graphics^ g) {
        if (!hero->getDead()) {
            if (hero->getPunching() || hero->getShooting()) {
                return;
            }
            if (hero->getFalling() || !val_mundo_victoria) {
                if (e->KeyCode == Keys::D) {
                    hero->setRunning(true);
                    if (!hero->getMovingRight()) {
                        hero->setMovingRight(true);
                        hero->setMovingLeft(false);
                        hero->setIndex(4);
                    }
                }
                else if (e->KeyCode == Keys::A) {
                    hero->setRunning(true);
                    if (!hero->getMovingLeft()) {
                        hero->setMovingLeft(true);
                        hero->setMovingRight(false);
                        hero->setIndex(7);
                    }
                }
                else if (e->KeyCode == Keys::Space && !hero->getJumping() && !hero->getFalling() && !hero->getSliding()) {
                    joining = false;
                    hero->setRunning(false);
                    hero->setJumping(true);
                    hero->setJumpSpeed(hero->getJumpStrength());
                }
            }
            if (hero->getRunning()) {
                if (e->KeyCode == Keys::R) {
                    hero->setPunching(false);
                    hero->setShooting(false);
                    hero->setRunning(false);
                    hero->setJumping(false);
                    hero->setSliding(true);
                    hero->setSlideSpeed(hero->getSlideStrength());
                }
            }
            if (!hero->getRunning() || !hero->getJumping() || !hero->getFalling() || !hero->getSliding()) {
                if (e->KeyCode == Keys::Q) {
                    hero->setPunching(true);
                }
                else if (hero->getMunicion() > 0) {
                    if (e->KeyCode == Keys::E) {
                        hero->setShooting(true);
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
                if (ready) {
                    if (e->KeyCode == Keys::G) {
                        hero->getSounds()[6]->Play();
                        sound = false;
                        hero->setRunning(false);
                        leaving = true;
                        if (leaving) {
                            hero->setIndex(34);
                            hero->dibujarSprite(g);
                            leaving = false;
                            joining = true;
                            Sleep(200);
                        }
                        if (val_mundo_1) {
                            prevX_1 = hero->getX();
                            prevY_1 = hero->getY();
                            hero->setX(1333);
                            hero->setY(hero->getDefaultFloor());
                            val_mundo_1 = false;
                            val_mundo_2 = true;
                        }
                        else if (val_mundo_2) {
                            prevX_2 = hero->getX();
                            prevY_2 = hero->getY();
                            hero->setX(190);
                            hero->setY(hero->getDefaultFloor());
                            val_mundo_2 = false;
                            val_mundo_3 = true;
                        }
                        else if (val_mundo_3) {
                            prevX_3 = hero->getX();
                            prevY_3 = hero->getY();
                            hero->setX(1364);
                            hero->setY(hero->getDefaultFloor());
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
                        if (portalActual_b != nullptr) {
                            portalActual_b->setIndex(0);
                        }
                        if (portalActual_f != nullptr) {
                            portalActual_f->setIndex(0);
                        }
                        readyToTravelForward = false;
                    }
                }
            }
            else if (readyToTravelBackward) {
                if (e->KeyCode == Keys::T) {
                    hero->getSounds()[6]->Play();
                    sound = false;
                    leaving = true;
                    hero->setRunning(false);
                    if (leaving) {
                        hero->setIndex(34);
                        hero->dibujarSprite(g);
                        leaving = false;
                        joining = true;
                        Sleep(200);
                    }
                    if (val_mundo_2) {

                        val_mundo_2 = false;
                        val_mundo_1 = true;

                        hero->setX(prevX_1);
                        hero->setY(prevY_1);
                    }
                    else if (val_mundo_3) {
                        val_mundo_3 = false;
                        val_mundo_2 = true;

                        hero->setX(prevX_2);
                        hero->setY(prevY_2);
                    }
                    else if (val_mundo_4) {
                        val_mundo_4 = false;
                        val_mundo_3 = true;

                        hero->setX(prevX_3);
                        hero->setY(prevY_3);
                    }
                    else if (val_mundo_5) {
                        val_mundo_5 = false;
                        val_mundo_4 = true;

                        hero->setX(prevX_4);
                        hero->setY(prevY_4);
                    }
                    if (portalActual_b != nullptr) {
                        portalActual_b->setIndex(0);
                    }
                    if (portalActual_f != nullptr) {
                        portalActual_f->setIndex(0);
                    }
                    readyToTravelBackward = false;
                }
            }
            else if (e->KeyCode == Keys::P) {
                if (hero->getReadyToPlant()) {
                    hero->setPlanted(true);
                }
            }
        }
    }
    void TeclasLevantadas(KeyEventArgs^ e) {
        if (!val_mundo_victoria) {
            if (e->KeyCode == Keys::D) {
                hero->setMovingRight(false);
                lastMove = "right";
            }
            else if (e->KeyCode == Keys::A) {
                hero->setMovingLeft(false);
                lastMove = "left";
            }
            else if (e->KeyCode == Keys::Q) {
                hero->setRunning(true);
                hero->setPunching(false);
                hero->setPunchingStarted(false);
            }
            else if (e->KeyCode == Keys::E) {
                hero->setRunning(true);
                if (hero->getShooting()) {
                    int dx = 10;
                    if (val_mundo_5) {
                        dx = 20;
                    }
                    if (lastMove == "right") {
                        hero->setIndex(26);
                        hero->getArma()->agregarBala(gcnew Bala(hero->getX() + hero->getWidth(), hero->getY(), dx, 2, 20, 20, images_heroBala));
                    }
                    else if (lastMove == "left") {
                        hero->setIndex(27);
                        hero->getArma()->agregarBala(gcnew Bala(hero->getX() - 10, hero->getY(), -dx, 2, 20, 20, images_heroBala));
                    }
                    if (!val_mundo_5) {
                        hero->getSounds()[1]->Play();
                        Sleep(50);
                    }
                    hero->setMunicion(hero->getMunicion() - 1);
                    hero->setShooting(false);
                    Sleep(100);
                }
            }
            else if (e->KeyCode == Keys::P) {
                hero->setPlanted(false);
            }
        }
    }
    // Funciones para el formulario final
    String^ getEnd() { return this->end; }
    
};
