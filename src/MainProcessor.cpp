#include <SFML/Graphics.hpp>
#include <MainProcessor.hpp>
#include <Asteroid.hpp>
#include <Ship.hpp>


void MainProcessor::Run() {
    sf::RenderWindow win(sf::VideoMode(resolution.x, resolution.y), "Blastar");
    win.setVerticalSyncEnabled(true);
    window = &win;

    Asteroid asteroid(sf::Vector2f(resolution),
                      sf::Vector2f(1, 1), window,
                      resolution);
    Ship ship(sf::Vector2f(resolution/2),
              sf::Vector2f(0, 0), window,
              resolution);
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
                // ship.fire();
            }
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) {
                window->close();
            }
        }
        { // render stage
            window->clear();
            asteroid.draw();
            ship.draw();
            window->display();
        }
    }
}

MainProcessor::MainProcessor() {
    // settings
    resolution.x = 1600;
    resolution.y = 900;
}

MainProcessor::~MainProcessor() {
}