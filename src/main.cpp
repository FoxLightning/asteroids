#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <Asteroid.hpp>
#include <Ship.hpp>

#define PI 3.14159265
#define SCREEN_X  1280
#define SCREEN_Y  720

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(SCREEN_X, SCREEN_Y), "Blastar");
    window.setVerticalSyncEnabled(true);

    // create objects
    Asteroid asteroid(sf::Vector2f(SCREEN_X*3/4, SCREEN_Y*3/4),
                      sf::Vector2f(-1, 1),
                      &window);
    Ship ship(sf::Vector2f(SCREEN_X/2, SCREEN_Y/2),
              sf::Vector2f(0, 0),
              &window);


    // run the program as long as the window is open
    while (window.isOpen())
    {
        // INPUT
        sf::Event event;
        while (window.pollEvent(event))
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
            }
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        asteroid.draw();
        ship.draw();
        // end the current frame
        window.display();
    }

    return 0;
}