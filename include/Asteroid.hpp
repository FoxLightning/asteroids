#pragma once
#include <SFML/Graphics.hpp>
#include <AbstractPhysicalObject.hpp>

class Asteroid :private AbstractPhysicalObject,
                public  AbstractPhysicalObjectInterface{
private:
    long double         rotation_speed;
    int setRandomPosition();
    int setRandomSpeed(sf::Vector2f target);
public:
    Asteroid(sf::Vector2f pos, sf::Vector2f sp,
             sf::RenderWindow *win, sf::Vector2i resolution);
    Asteroid(sf::RenderWindow *win, sf::Vector2i resolution,
             sf::Vector2f target);
    ~Asteroid();

    virtual void calculate();
    virtual void draw();
    virtual long double GetRadious();
    virtual sf::Vector2f GetPosition();
};
