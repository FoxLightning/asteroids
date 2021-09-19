#include <SFML/Graphics.hpp>
#include <MainProcessor.hpp>
#include <Asteroid.hpp>
#include <Ship.hpp>
#include <List.hpp>
#include <math.h>
#include <iostream>

#define PI 3.14159265

void MainProcessor::Run() {
    long int    frame_counter = 0;
    int         data_type;
    long double direction;
    sf::Vector2f direction_vector;
    Asteroid    *current_asteroid;
//  Bullet      *currentBullet
    sf::RenderWindow win(sf::VideoMode(resolution.x, resolution.y), "Blastar");
    List object_list;
    object_list.PrintInfo();
    win.setVerticalSyncEnabled(true);
    window = &win;

    Ship ship(sf::Vector2f(resolution/2),
              sf::Vector2f(0, 0), window,
              resolution);

    object_list.PrintInfo();


    sf::Vector2i cursor_position = sf::Mouse::getPosition(*window);
    while (window->isOpen())
    {
        frame_counter++;
        if (!(frame_counter % (5 * 60))) {
            current_asteroid = new Asteroid(window, resolution,
                                            ship.GetPosition());
            object_list.AppendAsteroid(current_asteroid);
        }
        // INPUT
        sf::Event event;
        while (window->pollEvent(event))
        {
            cursor_position = sf::Mouse::getPosition(*window);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                ship.engine_on();
            } else {
                ship.engine_off();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                ship.fire();
            }
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) {
                window->close();
            }
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
        window->clear();
        object_list.GoToStart();
        if (!object_list.GetCapacity()) {
            goto skip_object_render;
        }
        do {

            if (object_list.GetCurrentDataTypeId() == ASTEROID) {
                void *tmp = object_list.GetCurrentData();
                current_asteroid = static_cast<Asteroid*>(tmp);
                current_asteroid->draw();
            }
        } while (!object_list.NextElement());

        skip_object_render:

        ship.draw();
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