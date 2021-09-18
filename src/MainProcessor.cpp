#include <SFML/Graphics.hpp>
#include <MainProcessor.hpp>
#include <Asteroid.hpp>
#include <Ship.hpp>
#include <List.hpp>

void MainProcessor::Run() {
    int         data_type;
    Asteroid    *current_asteroid;
//  Bullet      *currentBullet
    sf::RenderWindow win(sf::VideoMode(resolution.x, resolution.y), "Blastar");
    List object_list;
    object_list.PrintInfo();
    win.setVerticalSyncEnabled(true);
    window = &win;

    Asteroid *a1 = new Asteroid(sf::Vector2f(resolution),
                             sf::Vector2f(1, 1), window,
                             resolution);
    Asteroid *a2 = new Asteroid(sf::Vector2f(resolution),
                        sf::Vector2f(0, 1), window,
                        resolution);
    Ship ship(sf::Vector2f(resolution/2),
              sf::Vector2f(0, 0), window,
              resolution);
    
    object_list.AppendAsteroid(a1);
    object_list.AppendAsteroid(a2);


    object_list.PrintInfo();
    while (window->isOpen())
    {
        // INPUT
        sf::Event event;
        while (window->pollEvent(event))
        {
            // rotation
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                ship.turn_left();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                ship.turn_right();
            }
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