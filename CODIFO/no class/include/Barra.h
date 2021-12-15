#pragma once
#include <SFML/Graphics.hpp>
#ifndef BARRA_H
#define BARRA_H

using namespace sf;

class Barra
{
public:
    Barra();
	float speed = 10.f;
	RectangleShape barraShape;
    Texture barraTexture;
	RectangleShape& getShapeBarra() { return barraShape; }
    void setSize(float ancho, float alto);
    void setPosition(float x, float y);
    void Move();
    void modo();
};

#endif // BARRA_H
