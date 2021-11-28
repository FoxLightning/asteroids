#pragma once
#include <Ship.hpp>
#include <Asteroid.hpp>
#include <Bullet.hpp>
#include <list>

struct GlobalContext
{
    std::list<Asteroid*>    asteroids_list;
    std::list<Bullet*>      bullet_list;
    std::list<Ship*>        ship_list;
};

class MainProcessor {
    sf::RenderWindow    *window;
    sf::Vector2i        resolution;
    GlobalContext       global_context;
public:
    MainProcessor();
    ~MainProcessor();
    void Run();
    void DrawContextObjects();
    std::list<AbstractPhysicalObject*> GetAbstractPhisicalObjectList();
    std::list<AbstractPhysicalObject*> GetColisionCoupleList(std::list<AbstractPhysicalObject*> &object_list);
    std::list<AbstractVisibleObject*> GetAbstractVisibleObjectList();

    void CalculateColisisons();
    void DrawAllObjects();
};
