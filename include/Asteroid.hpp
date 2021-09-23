#pragma once
#include <SFML/Graphics.hpp>
#include <AbstractPhysicalObject.hpp>
#include <AbstractVisibleObject.hpp>

class Asteroid: public AbstractPhysicalObject,
                public AbstractVisibleObject
{
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
    bool IsAlive();
    void asteroid_die();
};
