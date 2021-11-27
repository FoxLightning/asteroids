#include <SFML/Graphics.hpp>
#include <MainProcessor.hpp>
#include <Asteroid.hpp>
#include <Ship.hpp>
#include <Bullet.hpp>
#include <math.h>
#include <list>
#include <commonConst.hpp>
#include <AbstractPhysicalObject.hpp>
#include <AbstractVisibleObject.hpp>
#include <algorithms.hpp>
#include <iostream>


bool b_is_not_alive(Bullet& bullet) { 
    return (!bullet.IsAlive()); 
}

bool a_is_not_alive(Asteroid& asteroid) { 
    return (!asteroid.IsAlive()); 
}

std::list<AbstractPhysicalObject*> MainProcessor::GetColisionCoupleList(std::list<AbstractPhysicalObject*> &object_list) {
    std::list<AbstractPhysicalObject*> colision_object_list;
    int skip = 0;
    int count = 0;

    for (AbstractPhysicalObject* lvalue: object_list) {
        for(AbstractPhysicalObject* rvalue: object_list) {
            if (count > skip && CheckColision(lvalue, rvalue)) {
                colision_object_list.push_back(lvalue);
                colision_object_list.push_back(rvalue);
            }
            count++;
        }
        skip++;
        count = 0;
    }
    return colision_object_list;
}


std::list<AbstractPhysicalObject*> MainProcessor::GetAbstractPhisicalObjectList() {
    std::list<AbstractPhysicalObject*> object_list;
    for (auto object: global_context.asteroids_list) {
        object_list.push_back(static_cast<AbstractPhysicalObject*>(object));
    }
    for (auto object: global_context.bullet_list) {
        object_list.push_back(static_cast<AbstractPhysicalObject*>(object));
    }
    for (auto object: global_context.ship_list) {
        object_list.push_back(static_cast<AbstractPhysicalObject*>(object));
    }
    return object_list;
}

std::list<AbstractVisibleObject*> MainProcessor::GetAbstractVisibleObjectList() {
    std::list<AbstractVisibleObject*> object_list;
    for (auto object: global_context.asteroids_list) {
        object_list.push_back(static_cast<AbstractVisibleObject*>(object));
    }
    for (auto object: global_context.bullet_list) {
        object_list.push_back(static_cast<AbstractVisibleObject*>(object));
    }
    for (auto object: global_context.ship_list) {
        object_list.push_back(static_cast<AbstractVisibleObject*>(object));
    }
    return object_list;
}

void MainProcessor::Run() {
    int                 cooldown = 10;
    int                 current_cooldown = 0;
    int                 time_to_spawn = 1 * 60*60;
    bool                shoot = false;
    long int            frame_counter = 60*59;
    long double         direction;
    sf::Vector2f        direction_vector;
    sf::RenderWindow    win(sf::VideoMode(resolution.x, resolution.y), "Blastar");
    window = &win;
    sf::Vector2i        cursor_position = sf::Mouse::getPosition(*window);

    win.setVerticalSyncEnabled(true);

    // create main ship
    Ship ship(sf::Vector2f(resolution/2),
              sf::Vector2f(0, 0), window,
              resolution);
    global_context.ship_list.push_back(&ship);

    while (window->isOpen())
    {
        if (current_cooldown > 0) {
            current_cooldown--;
        }
        frame_counter++;
        if (!(frame_counter % time_to_spawn)) {
            Asteroid *tmp = new Asteroid(window, resolution, ship.GetPosition());

            // TODO make class context
            global_context.asteroids_list.push_back(tmp);

            frame_counter %= time_to_spawn;
        }
        // INPUT
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed) {
                shoot = true;
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                shoot = false;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                ship.engine_on();
            } else {
                ship.engine_off();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            }
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) {
                window->close();
            }
            cursor_position = sf::Mouse::getPosition(*window);
        }
        if (shoot and !current_cooldown) {
            current_cooldown = cooldown;
            auto *tmp = new Bullet(&ship);
            global_context.bullet_list.push_back(tmp);
        }
        { // set ship direction
            direction_vector = sf::Vector2f(cursor_position.x-ship.GetPosition().x,
                                          cursor_position.y-ship.GetPosition().y);
            direction = atan(direction_vector.y/direction_vector.x) * 180/PI;
            if (direction_vector.x < 0) {
                direction += 180;
            }
            ship.SetRotation(direction+90);
        }

        // collision check
        auto v = GetAbstractPhisicalObjectList();
        auto col_c = GetColisionCoupleList(v);
        AbstractPhysicalObject* prev = NULL;
        for (AbstractPhysicalObject* cur: GetColisionCoupleList(col_c)) {
            if (prev == NULL) {
                prev = cur;
            } else {
                ResolveColision(prev, cur);
                prev = NULL;
            }
        }

        window->clear();
        ship.draw();
        for(auto obj: GetAbstractVisibleObjectList()) {
            obj->draw();
        }
        window->display();
    }
}

MainProcessor::MainProcessor() {
    // settings
    resolution.x = 1600;
    resolution.y = 900;
}

MainProcessor::~MainProcessor() {
}
