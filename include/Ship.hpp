#pragma once
#include <SFML/Graphics.hpp>
#include <AbstractPhysicalObject.hpp>

class Ship :public AbstractPhysicalObject,
            public AbstractPhysicalObjectInterface{
private:
    sf::Vector2f        acceleration;
public:
    Ship(sf::Vector2f pos, sf::Vector2f sp,
         sf::RenderWindow *win, sf::Vector2i resolution);
    Ship(sf::RenderWindow *win, sf::Vector2i resolution);
    ~Ship();

    void SetRotation(long double input_rotation);
    void engine_on();
    void engine_off();
    void fire();

    void calculate();
    sf::Vector2f GetPosition();
    long double GetRadious();
    void draw();
};