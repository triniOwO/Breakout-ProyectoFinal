#pragma once
#include <SFML/Graphics.hpp>
#ifndef PELOTA_H
#define PELOTA_H

using namespace sf;

class Pelota
{
    private:

        Texture ball;
        int direccionY;
        int direccionX;
        float speed = 5.f;
        CircleShape pelotaShape;


    public:
        Pelota(float radio);
        virtual ~Pelota();

        CircleShape& getShapePelota(){ return pelotaShape; }

        Texture& getTexturePelota(){ return ball; }



        void mover();
        void getdireccionY(int);
        void getdireccionX(int);
        void modo()
        {
            speed = 6.f;
        }


};

#endif // PELOTA_H
