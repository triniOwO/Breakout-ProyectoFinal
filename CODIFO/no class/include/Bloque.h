#pragma once
#include <SFML/Graphics.hpp>
#ifndef BLOQUE_H
#define BLOQUE_H

using namespace sf;

class Bloque
{
    private:
        RectangleShape bloqueShape;
        Texture textureRed;
        Texture textureBlue;
        Texture textureGreen;
        Texture texturePurple;
        FloatRect bloquesBox;

    public:
        Bloque();
        virtual ~Bloque();
        void setPosition(float posY, float posX);

        void draw(RenderWindow& ventana);

        FloatRect bordes();

        RectangleShape& getBloqueShape() { return bloqueShape; }
        void setTexturaRed()
        {
            textureRed.loadFromFile("BLOQUE ROJO.png");
            bloqueShape.setTexture(&textureRed);
        }
        void setTexturaBlue()
        {
            textureBlue.loadFromFile("BLOQUE AZUL.png");
            bloqueShape.setTexture(&textureBlue);
        }
        void setTexturaGreen()
        {
            textureGreen.loadFromFile("BLOQUE VERDE.png");
            bloqueShape.setTexture(&textureGreen);
        }
        void setTexturaPurple()
        {
            texturePurple.loadFromFile("BLOQUE VIOLETA.png");
            bloqueShape.setTexture(&texturePurple);
        }

};

#endif // BLOQUE_H
