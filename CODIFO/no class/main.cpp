#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Barra.h"
#include "Pelota.h"
#include "Global.h"
#include "Bloque.h"
#include"Menu.h"
#include <iostream>

using namespace std;

using namespace sf;

int main()
{

    int vida = 5;

    int puntos = 0;

    Barra obj1;
    obj1.setSize(100, 20);
    obj1.setPosition(ANCHO / 2, ALTO - obj1.barraShape.getSize().y);



    RenderWindow ventana(VideoMode(ANCHO, ALTO), " Proyecto Final ");

    ventana.setVerticalSyncEnabled(true);

    Font fuente;

    fuente.loadFromFile("Gameplay.ttf");

    Text txt_vida;

    Text txt_puntos;

    txt_puntos.setFont(fuente);

    txt_puntos.setPosition(970, 560);

    txt_puntos.setCharacterSize(50);

    txt_vida.setFont(fuente);

    txt_vida.setPosition(970, 635);

    txt_vida.setCharacterSize(50);


    //VARIABLES DEL MENU
    Menu menu(ventana.getSize().x, ventana.getSize().y);
    RectangleShape background;
    background.setSize(Vector2f(ANCHO, ALTO));
    Texture Maintexture;
    Maintexture.loadFromFile("Background.png");
    background.setTexture(&Maintexture);

    // INSTANCIAR UN OBJETO DE TIPO PELOTA
    Pelota pelota(10.f);
    pelota.getShapePelota().setPosition(0, 300);

    //SEPARACION, POSCION Y CANTIDAD DE BLOQUES
    unsigned const int bloqueCantidad = 13;

    Bloque bloques1[bloqueCantidad];
    Bloque bloques2[bloqueCantidad];
    Bloque bloques3[bloqueCantidad];
    Bloque bloques4[bloqueCantidad];

    for (size_t i = 0; i < bloqueCantidad; i++)
    {
        bloques1[i].setPosition(i * 84.f, 0.f);
        bloques1[i].setTexturaRed();
    }
    for (size_t i = 0; i < bloqueCantidad; i++)
    {
        bloques2[i].setPosition(i * 84.f, 58.f);
        bloques2[i].setTexturaBlue();
    }
    for (size_t i = 0; i < bloqueCantidad; i++)
    {
        bloques3[i].setPosition(i * 84.f, 116.f);
        bloques3[i].setTexturaGreen();
    }
    for (size_t i = 0; i < bloqueCantidad; i++)
    {
        bloques4[i].setPosition(i * 84.f, 175.f);
        bloques4[i].setTexturaPurple();
    }

    SoundBuffer buffer;
    Sound sonido;
    buffer.loadFromFile("AUN YO TE RECUERDO.wav");
    sonido.setBuffer(buffer);
    SoundBuffer otaso;
    Sound elMosca;
    otaso.loadFromFile("el mosca.wav");
    elMosca.setBuffer(otaso);
    SoundBuffer pin;
    Sound pin_sound;
    pin_sound.setBuffer(pin);
    pin.loadFromFile("pin.wav");
    SoundBuffer pop;
    Sound sound_pop;
    pop.loadFromFile("break.wav");
    sound_pop.setBuffer(pop);





    //RECORRE EL VECTOR Y OBTIENE LOS BOUNDS

    while (ventana.isOpen())
    {

        //verificamos todos los eventos de la ventana
        Event event;
        while (ventana.pollEvent(event))
        {
            // "cierre solicitado" evento: cerramos la ventana
            if (event.type == sf::Event::Closed)
                ventana.close();

			switch (event.type)
			{
			case Event::KeyReleased:
				switch (event.key.code)
				{
				case Keyboard::Up:
					menu.MoveUp();
					break;

				case Keyboard::Down:
					menu.MoveDown();
					break;

				case Keyboard::Return:
					switch (menu.GetPressedItem())
					{
					case 0:
                        sonido.play();

                        while(ventana.isOpen())
                            {
                            while (ventana.pollEvent(event))
                            {
                                // "cierre solicitado" evento: cerramos la ventana
                                if (event.type == sf::Event::Closed)
                                    ventana.close();

                            }
                                obj1.Move();
                                pelota.mover();


                                //MOVIMIENTO DE LA PELOTA
                                if(pelota.getShapePelota().getPosition().y + pelota.getShapePelota().getRadius() > 720)
                                {
                                    pelota.getShapePelota().setPosition(20,320);
                                    vida -= 1;
                                }

                                if(pelota.getShapePelota().getPosition().y < 0)
                                {
                                    pelota.getdireccionY(1);
                                }


                                if(pelota.getShapePelota().getPosition().x + pelota.getShapePelota().getRadius() > 1080)
                                {
                                    pelota.getdireccionX(-1);
                                }

                                if(pelota.getShapePelota().getPosition().x < 0)
                                {
                                    pelota.getdireccionX(1);
                                }

                                FloatRect barraBox = obj1.getShapeBarra().getGlobalBounds();
                                FloatRect pelotaBox = pelota.getShapePelota().getGlobalBounds();


                                if(pelotaBox.intersects(barraBox))
                                {
                                    pelota.getdireccionY(-1);
                                    pin_sound.play();
                                }
                                //DESTRUCCION DE BLOQUES
                                //OBTIENE LOS LIMITES(BOUNDS) DE CADA FILA DE BLOQUES
                                for(size_t i= 0; i < bloqueCantidad; i++)
                                {
                                    bloques1[i].bordes();
                                    bloques2[i].bordes();
                                    bloques3[i].bordes();
                                    bloques4[i].bordes();
                                    if(pelotaBox.intersects(bloques1[i].bordes()))
                                    {
                                        bloques1[i].getBloqueShape().setPosition(3000, 3000);
                                        pelota.getdireccionY(1);
                                        puntos += 20;
                                        sound_pop.play();
                                    }
                                    if(pelotaBox.intersects(bloques2[i].bordes()))
                                    {
                                        bloques2[i].getBloqueShape().setPosition(3000, 3000);
                                        pelota.getdireccionY(1);
                                        puntos += 15;
                                        sound_pop.play();
                                    }
                                    if(pelotaBox.intersects(bloques3[i].bordes()))
                                    {
                                        bloques3[i].getBloqueShape().setPosition(3000, 3000);
                                        pelota.getdireccionY(1);
                                        puntos += 10;
                                        sound_pop.play();
                                    }
                                    if(pelotaBox.intersects(bloques4[i].bordes()))
                                    {
                                        bloques4[i].getBloqueShape().setPosition(3000, 3000);
                                        pelota.getdireccionY(1);
                                        puntos += 5;
                                        sound_pop.play();

                                    }

                                }

                                ventana.draw(obj1.barraShape);
                                ventana.draw(pelota.getShapePelota());
                                txt_vida.setString(std::to_string(vida));
                                txt_puntos.setString(to_string(puntos));
                                ventana.draw(txt_puntos);
                                ventana.draw(txt_vida);

                                for(size_t i = 0; i < bloqueCantidad; i++)
                                {
                                    bloques1[i].draw(ventana);
                                    bloques2[i].draw(ventana);
                                    bloques3[i].draw(ventana);
                                    bloques4[i].draw(ventana);

                                }
                                if(vida < 1)
                                {
                                    ventana.clear(Color::Black);

                                    Font fuente2;

                                    fuente2.loadFromFile("Gameplay.ttf");

                                    Text txt_GameOver;

                                    txt_GameOver.setFont(fuente2);

                                    txt_GameOver.setPosition(330, 200);

                                    txt_GameOver.setCharacterSize(70);

                                    txt_GameOver.setFillColor(Color::Red);

                                    txt_GameOver.setString("GAME OVER");

                                    ventana.draw(txt_GameOver);

                                    txt_vida.setString("TUS PUNTOS FUERON");

                                    txt_vida.setPosition(263, 350);

                                    ventana.draw(txt_vida);

                                    txt_puntos.setPosition(540, 450);

                                    ventana.draw(txt_puntos);

                                    pelota.getShapePelota().setPosition(3000, 3000);


                                }

                                if(puntos >= 650)
                                {
                                    ventana.clear(Color::Black);
                                    txt_vida.setPosition(425, 250);
                                    txt_vida.setString("VICTORIA!");
                                    txt_vida.setFillColor(Color::Green);
                                    txt_puntos.setString("TUS PUNTOS FUERON 650");
                                    txt_puntos.setPosition(215, 350);
                                    Text txt_puntitos;
                                    txt_puntitos.setPosition(540, 450);
                                    //txt_puntitos.setString()

                                    ventana.draw(txt_puntitos);
                                    ventana.draw(txt_vida);
                                    ventana.draw(txt_puntos);
                                }

                                ventana.display();
                                ventana.clear();

                            }

						break;
					case 1:
                            elMosca.play();
                            pelota.modo();
                            obj1.modo();
                            vida -= 2;
                            while(ventana.isOpen())
                            {
                                while (ventana.pollEvent(event))
                                {
                                    // "cierre solicitado" evento: cerramos la ventana
                                    if (event.type == sf::Event::Closed)
                                        ventana.close();

                                }
                                obj1.Move();
                                pelota.mover();

                                //MOVIMIENTO DE LA PELOTA
                                if(pelota.getShapePelota().getPosition().y + pelota.getShapePelota().getRadius() > 720)
                                {
                                    pelota.getShapePelota().setPosition(20,320);
                                    vida -= 1;
                                }

                                if(pelota.getShapePelota().getPosition().y < 0)
                                {
                                    pelota.getdireccionY(1);
                                }


                                if(pelota.getShapePelota().getPosition().x + pelota.getShapePelota().getRadius() > 1080)
                                {
                                    pelota.getdireccionX(-1);
                                }

                                if(pelota.getShapePelota().getPosition().x < 0)
                                {
                                    pelota.getdireccionX(1);
                                }

                                FloatRect barraBox = obj1.getShapeBarra().getGlobalBounds();
                                FloatRect pelotaBox = pelota.getShapePelota().getGlobalBounds();


                                if(pelotaBox.intersects(barraBox))
                                {
                                    pelota.getdireccionY(-1);
                                    pin_sound.play();
                                }
                                //DESTRUCCION DE BLOQUES
                                //OBTIENE LOS LIMITES(BOUNDS) DE CADA FILA DE BLOQUES
                                for(size_t i= 0; i < bloqueCantidad; i++)
                                {
                                    bloques1[i].bordes();
                                    bloques2[i].bordes();
                                    bloques3[i].bordes();
                                    bloques4[i].bordes();
                                    if(pelotaBox.intersects(bloques1[i].bordes()))
                                    {
                                        bloques1[i].getBloqueShape().setPosition(3000, 3000);
                                        pelota.getdireccionY(1);
                                        puntos += 20;
                                        sound_pop.play();
                                    }
                                    if(pelotaBox.intersects(bloques2[i].bordes()))
                                    {
                                        bloques2[i].getBloqueShape().setPosition(3000, 3000);
                                        pelota.getdireccionY(1);
                                        puntos += 15;
                                        sound_pop.play();
                                    }
                                    if(pelotaBox.intersects(bloques3[i].bordes()))
                                    {
                                        bloques3[i].getBloqueShape().setPosition(3000, 3000);
                                        pelota.getdireccionY(1);
                                        puntos += 10;
                                        sound_pop.play();
                                    }
                                    if(pelotaBox.intersects(bloques4[i].bordes()))
                                    {
                                        bloques4[i].getBloqueShape().setPosition(3000, 3000);
                                        pelota.getdireccionY(1);
                                        puntos += 5;
                                        sound_pop.play();

                                    }

                                }

                                ventana.draw(obj1.barraShape);
                                ventana.draw(pelota.getShapePelota());
                                txt_vida.setString(std::to_string(vida));
                                txt_puntos.setString(to_string(puntos));
                                ventana.draw(txt_puntos);
                                ventana.draw(txt_vida);

                                for(size_t i = 0; i < bloqueCantidad; i++)
                                {
                                    bloques1[i].draw(ventana);
                                    bloques2[i].draw(ventana);
                                    bloques3[i].draw(ventana);
                                    bloques4[i].draw(ventana);

                                }
                                if(vida < 1)
                                {
                                    ventana.clear(Color::Black);

                                    Font fuente2;

                                    fuente2.loadFromFile("Gameplay.ttf");

                                    Text txt_GameOver;

                                    txt_GameOver.setFont(fuente2);

                                    txt_GameOver.setPosition(330, 200);

                                    txt_GameOver.setCharacterSize(70);

                                    txt_GameOver.setFillColor(Color::Red);

                                    txt_GameOver.setString("GAME OVER");

                                    ventana.draw(txt_GameOver);

                                    txt_vida.setString("TUS PUNTOS FUERON");

                                    txt_vida.setPosition(263, 350);

                                    ventana.draw(txt_vida);

                                    txt_puntos.setPosition(540, 450);

                                    ventana.draw(txt_puntos);

                                    pelota.getShapePelota().setPosition(3000, 3000);


                                }

                                if(puntos >= 650)
                                {
                                    ventana.clear(Color::Black);
                                    txt_vida.setPosition(425, 250);
                                    txt_vida.setString("VICTORIA!");
                                    txt_vida.setFillColor(Color::Green);
                                    txt_puntos.setString("TUS PUNTOS FUERON 650");
                                    txt_puntos.setPosition(215, 350);
                                    Text txt_puntitos;
                                    txt_puntitos.setPosition(540, 450);
                                    //DIBUJA LA PANTALLA DE VICTORIA
                                    ventana.draw(txt_puntitos);
                                    ventana.draw(txt_vida);
                                    ventana.draw(txt_puntos);
                                    pelota.getShapePelota().setPosition(3000, 3000);
                                }

                                ventana.display();
                                ventana.clear();

                            }

						break;

					case 2:
						ventana.close();
						break;
					}

					break;
				}

				break;
			case Event::Closed:
				ventana.close();

				break;

			}

        }


        // mostramos ventana en la pantalla

        ventana.draw(background);
        menu.draw(ventana);
        ventana.display();
        ventana.clear();


     }// al cerrar la ventana salto esta llave

    return 0;//devuelvo el control al SO
}
