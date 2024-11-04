#pragma once
using namespace System::Media;
using namespace System::Drawing;
using namespace System;

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

ref class Sprite {
protected:
    int x, y;
    int dx;
    int width, height;
    array<Bitmap^>^ images;
public:
    Sprite(int x, int y, int dx, int w, int h, array<Bitmap^>^imgs) : x(x), y(y), dx(dx), width(w), height(h), images(imgs) {}
    ~Sprite(){}
    virtual void dibujarSprite(Graphics^ g, int index) = 0;
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
};

ref class Vida : public Sprite {
private:
    int startIndex, endIndex;
    int index;
public:
    Vida(int x, int y, int w, int h, array<Bitmap^>^ imgs, int s_i, int e_i) : Sprite(x, y, 0, w, h, imgs), startIndex(s_i), endIndex(e_i) {
        this->index = startIndex;
    }
    ~Vida(){}
    void dibujarSprite(Graphics^ g, int index) override {}
    void dibujarVida(Graphics^ g) {
        g->DrawImage(images[index], x, y, width, height);
    }
    void setIndex(int i) { this->index = i; }
    void setStartIndex(int s_i) { this->startIndex = s_i; }
    void setEndIndex(int e_i) { this->endIndex = e_i; }
    int getIndex() { return this->index; }
    int getStartIndex() { return this->startIndex; }
    int getEndIndex() { return this->endIndex; }
};

ref class Bala : public Sprite {
private:   
    int startIndex, endIndex;
    int index;
public:
    Bala(int x, int y, int dx, int i, int w, int h, array<Bitmap^>^ imgs) : Sprite(x, y, dx, w, h, imgs){
        if (dx > 0) {
            this->startIndex = i - i;
            this->endIndex = i;
        }
        else if (dx < 0) {
            this->startIndex = i + 1;
            this->endIndex = i * 2 + 1;
        }
        this->index = startIndex;
        this->y += 20;
    }
    void dibujarSprite(Graphics^ g, int index) override {}
    void dibujarBala(Graphics^ g) {
        g->DrawImage(images[index], x, y, width, height);
    }
    void setIndex(int i) { this->index = i; }
    void setStartIndex(int s_i) { this->startIndex = s_i; }
    void setEndIndex(int e_i) { this->endIndex = e_i; }
    int getIndex() { return this->index; }
    int getStartIndex() { return this->startIndex; }
    int getEndIndex() { return this->endIndex; }
};

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
            balaActual->dibujarBala(g);
            balaActual->setX(balaActual->getX() + balaActual->getDX());
        }
    }
};

ref class Heroe : public Sprite {
private:
    int startIndex, endIndex;
    float index;
    bool attacked;
    int vidas;
    int municion;
    Balas^ arma;
    Vida^ VidaHero;
    array<SoundPlayer^>^ sounds;
public:
    Heroe(int x, int y, int dx, int w, int h, array<Bitmap^>^ imgs, Vida^ vida, array<SoundPlayer^>^ sounds) : Sprite(x, y, dx, w, h, imgs), VidaHero(vida), sounds(sounds){
        arma = gcnew Balas;
        this->municion = 10;
        this->vidas = 1000;
        this->attacked = false;
    }
    void dibujarSprite(Graphics^ g, int index) override {
        if (!attacked) {
            g->DrawImage(images[index], x, y, width, height);
        }
        else if (attacked) {
            Bitmap^ spriteBlanco = crearSpriteBlanco(images[index]);
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
    int getVidas() {
        return this->vidas;
    }
    void setAttacked(bool attacked) {
        this->attacked = attacked;
    }
    bool getAttacked() {
        return this->attacked;
    }

    Vida^ getVida() { return this->VidaHero; }
    array<SoundPlayer^>^ getSounds() { return this->sounds; }

    void setIndex(float i) { this->index = i; }
    void setStartIndex(int s_i) { this->startIndex = s_i; }
    void setEndIndex(int e_i) { this->endIndex = e_i; }
    float getIndex() { return this->index; }
    int getStartIndex() { return this->startIndex; }
    int getEndIndex() { return this->endIndex; }
};

ref class Recurso : public Sprite {
private:
    bool sembrado;
    int index;
public:
    Recurso(int x, int y, int w, int h, array<Bitmap^>^ imgs, int i) : Sprite(x, y, 0, w, h, imgs){
        this->sembrado = false;
        this->index = i;
    }
    void dibujarSprite(Graphics^ g, int index) override {}
    void dibujarRecurso(Graphics^ g) {
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

ref class Aliado : public Sprite {
private:
    int startIndex, endIndex;
    int index;
public:
    Aliado(int x, int y, int dx, int w, int h, array<Bitmap^>^ imgs) : Sprite(x, y, dx, w, h, imgs) {
        if (randnum(1, 2) == 1) {
            startIndex = 0;
            endIndex = 1;
        }
        else {
            startIndex = 2;
            endIndex = 3;
        }
    }
    void dibujarSprite(Graphics^ g, int index) override{}
    void dibujarAliado(Graphics^ g) {
        g->DrawImage(images[index], x, y, width, height);
    }
    void setIndex(int i) { this->index = i; }
    void setStartIndex(int s_i) { this->startIndex = s_i; }
    void setEndIndex(int e_i) { this->endIndex = e_i; }
    int getIndex() { return this->index; }
    int getStartIndex() { return this->startIndex; }
    int getEndIndex() { return this->endIndex; }
};

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

ref class Enemigo : public Sprite {
private:
    int vidas, daño;
    int gravity;
    int startIndex, endIndex;
    int index;
    bool movingRight = 0, movingLeft = 0;
    bool falling;
    bool punched, shot;
    array<SoundPlayer^>^ sounds;
public:
    Enemigo(int x, int y, int dx, int w, int h, array<Bitmap^>^ imgs, int daño, int vidas, cli::array<SoundPlayer^>^ sounds) : Sprite(x, y, dx, w, h, imgs), sounds(sounds) {
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
    void dibujarSprite(Graphics^ g, int index) override {}
    void dibujarEnemigo(Graphics^ g) {
        if (!punched && !shot) {
            g->DrawImage(images[index], x, y, width, height);
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
    void setIndex(int i) { this->index = i; }
    void setStartIndex(int s_i) { this->startIndex = s_i; }
    void setEndIndex(int e_i) { this->endIndex = e_i; }
    void setDX(int dx) { 
        this->dx = dx;
        if (dx > 0) movingRight = true, movingLeft = false;
        else if (dx < 0) movingLeft = true, movingRight = false;
        if (movingRight) startIndex = 2, endIndex = 4;
        if (movingLeft) startIndex = 5, endIndex = 7;
    }
    void setFall(bool fall) { this->falling = fall; }
    void setGravity(int gravity) { this->gravity = gravity; }
    int getIndex() { return this->index; }
    int getStartIndex() { return this->startIndex; }
    int getEndIndex() { return this->endIndex; }
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

ref class Portal : public Sprite {
private:
    array<Image^>^ portal;
public:
    Portal(int x, int y, int w, int h, array<Image^>^ prtl) : Sprite(x, y, 0, w, h, nullptr), portal(prtl) {}
    ~Portal() {}
    void dibujarSprite(Graphics^ g, int index) override {
        System::Drawing::Rectangle portalRect = System::Drawing::Rectangle(x, y, width, height);
        g->DrawImage(portal[index], portalRect);
    }
};

ref class Mundo {
private:
    int x, y;
    int width, height;
    array<Image^>^ imagenes;
public:
    Mundo(int x, int y, int w, int h, array<Image^>^ imagenes) {
        this->x = x;
        this->y = y;
        this->width = w;
        this->height = h;
        this->imagenes = imagenes;
    }
    ~Mundo() {}
    void dibujarMundo(Graphics^ g, int index, int clientWidth, int clientHeight) {
        System::Drawing::Imaging::ColorMatrix^ colorMatrix = gcnew System::Drawing::Imaging::ColorMatrix();
        colorMatrix->Matrix33 = 1.0f;

        System::Drawing::Imaging::ImageAttributes^ imageAttributes = gcnew System::Drawing::Imaging::ImageAttributes();
        imageAttributes->SetColorMatrix(colorMatrix, System::Drawing::Imaging::ColorMatrixFlag::Default, System::Drawing::Imaging::ColorAdjustType::Bitmap);

        System::Drawing::Rectangle destRect = System::Drawing::Rectangle(0, 0, clientWidth, clientHeight);
        g->DrawImage(imagenes[index], destRect, x, y, width, height, GraphicsUnit::Pixel, imageAttributes);
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

ref class Temporizador : public Sprite {
    int startIndex, endIndex;
    float index;
    bool activo;
public:
    Temporizador(int x, int y, int w, int h, array<Bitmap^>^ imgs) : Sprite(x, y, 0, w, h, imgs){
        this->startIndex = 60;
        this->endIndex = 0;
        this->index = startIndex;
        this->activo = true;
    }
    ~Temporizador(){}
    void dibujarSprite(Graphics^ g, int index) override {}
    void dibujarTemporizador(Graphics^ g, int num) {
        if (activo) {
            if (num == 0) {
                Bitmap^ temporizadorBlanco = crearSpriteBlanco(images[int(index)]);
                g->DrawImage(temporizadorBlanco, x, y, width, height);
            }
            else {
                g->DrawImage(images[int(index)], x, y, width, height);
            }
        }
        else if (!activo) {
            this->index = 61;
            if (num == 0) {
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
    void setStartIndex(int s_i) { this->startIndex = s_i; }
    void setEndIndex(int e_i) { this->endIndex = e_i; }
    float getIndex() { return this->index; }
    int getStartIndex() { return this->startIndex; }
    int getEndIndex() { return this->endIndex; }
    void setActivo(bool activo) { this->activo = activo; };
    bool getActivo() { return this->activo; }
};

ref class Boss : public Sprite {
private:
    int startIndex, endIndex;
    int index;
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
    Boss(int x, int y, int w, int h, array<Bitmap^>^ imgs, int s_i, int e_i, int vidas, int daño, Vida^ vida) : Sprite(x, y, 0, w, h, imgs), startIndex(s_i), endIndex(e_i), vidas(vidas), daño(daño), vida(vida) {
        
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
    void dibujarSprite(Graphics^ g, int index) override {}
    void dibujarBoss(Graphics^ g) {
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
            g->DrawImage(images[index], x, y, width, height);
        }
        else if (attacked) {
            Bitmap^ spriteBlanco;
            spriteBlanco = crearSpriteBlanco(images[index]);
            g->DrawImage(spriteBlanco, x, y, width, height);
            attacked = false;
        }
    }
    void movimientoEspiral(Graphics^ g) {
        // Definimos las velocidades y otras variables
        static double angle = 0;          // ángulo inicial para el movimiento circular
        double angularSpeed = 0.05;       // velocidad angular para el movimiento circular
        double radialSpeed = 10.0;         // velocidad de expansión/contracción del radio

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
    void setIndex(int i) { this->index = i; }
    void setStartIndex(int s_i) { this->startIndex = s_i; }
    void setEndIndex(int e_i) { this->endIndex = e_i; }
    void setVidas(int vidas) { 
        if (vidas < 0) vidas = 0;
        this->vidas = vidas;
    }
    bool getSeingRight() { return this->seingRight; }
    bool getSeingLeft() { return this->seingLeft; }
    bool getAttacked() { return this->attacked; }
    int getIndex() { return this->index; }
    int getStartIndex() { return this->startIndex; }
    int getEndIndex() { return this->endIndex; }
    int getVidas() { return this->vidas; }
    int getDaño() { return this->daño; }
    Vida^ getVida() { return this->vida; }
    Balas^ getArma() { return this->bolas; }

    void setLapse(float lapse) { this->lapse = lapse; }
    float getLapse() { return this->lapse; }

    void setAlive(bool alive) { this->alive = alive; }
    bool getAlive() { return this->alive; }
};
