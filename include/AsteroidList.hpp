#pragma once
#include <Ship.hpp>
#include <Asteroid.hpp>

struct Element {
    Asteroid *asteroid_data;
    Element *next_element;
    Element *prev_element;
};

class AsteroidList {
    unsigned int count;
    Element *current_element;
    Element *first_element;
    Element *last_element;

public:
    void Append(sf::RenderWindow window, sf::Vector2i resolution,
                  sf::Vector2f position);

    void *GetCurrentData();
    int DeleteCurrentElement();

    int NextElement();
    int GoToStart();
    int GetCapacity();
    void PrintInfo();

    AsteroidList();
    ~AsteroidList();
};