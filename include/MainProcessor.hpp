#pragma once
#include <Ship.hpp>
#include <Asteroid.hpp>


class MainProcessor {
    sf::RenderWindow    *window;
    sf::Vector2i        resolution;
    Asteroid            *asteroids;
    Ship                *ship;
public:
    MainProcessor();
    ~MainProcessor();
    void Run();
};
