#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <math.h>
#include <Asteroid.hpp>

#define PI 3.14159265
#define SCREEN_X  1280
#define SCREEN_Y  720

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(SCREEN_X, SCREEN_Y), "Blastar");
    window.setVerticalSyncEnabled(true);
    Asteroid AAA(sf::Vector2f(SCREEN_X*3/4, SCREEN_Y*3/4),
                 sf::Vector2f(-1, 1),
                 &window);
    // define asteroid phisics
    bool a_alive = true;
    float a_positon_x, a_positon_y;
    a_positon_x = SCREEN_X / 4;
    a_positon_y = SCREEN_Y / 4;
    float a_speed_x, a_speed_y;
    a_speed_x = 1;
    a_speed_y = 1;
    float a_acceleration_x, a_acceleration_y;
    a_acceleration_x = 0;
    a_acceleration_y = 0;
    float a_rotation;
    a_rotation = 0;
    float damage_radius;
    damage_radius = 100.f;
    // define ship render
    // shape
    sf::ConvexShape asteroid;
    asteroid.setPointCount(5);
    asteroid.setPoint(0, sf::Vector2f(0.f, -100.f));
    asteroid.setPoint(1, sf::Vector2f(100.f, -50.f));
    asteroid.setPoint(2, sf::Vector2f(70.f, 40.f));
    asteroid.setPoint(3, sf::Vector2f(-60.f, 50.f));
    asteroid.setPoint(4, sf::Vector2f(-40.f, -20.f));
    asteroid.setFillColor(sf::Color::Transparent);
    asteroid.setOutlineThickness(4.f);
    asteroid.setOutlineColor(sf::Color::Blue);
    // position
    asteroid.setPosition(a_positon_x, a_positon_y);
    asteroid.setRotation(a_rotation);


    // define ship phisics
    float positon_x, positon_y;
    positon_x = SCREEN_X / 2;
    positon_y = SCREEN_Y /2;
    float speed_x, speed_y;
    speed_x = 0;
    speed_y = 0;
    float acceleration_x, acceleration_y;
    acceleration_x = 0;
    acceleration_y = 0;
    float rotation;
    rotation = 0;
    // define ship render
    // shape
    sf::ConvexShape ship;
    ship.setPointCount(3);
    ship.setPoint(0, sf::Vector2f(0.f, -10.f));
    ship.setPoint(1, sf::Vector2f(-5.f, 10.f));
    ship.setPoint(2, sf::Vector2f(5.f, 10.f));
    ship.setFillColor(sf::Color::Transparent);
    ship.setOutlineThickness(4.f);
    ship.setOutlineColor(sf::Color::Blue);
    // position
    ship.setPosition(positon_x, positon_y);
    ship.setRotation(rotation);

    // bullet
    bool alive;
    alive = false;
    int life_time;
    life_time = 4 * 60;
    
    float b_positon_x, b_positon_y;
    float b_speed_x, b_speed_y;
    float b_rotation;
    sf::RectangleShape line(sf::Vector2f(50.f, 4.f));
    line.rotate(rotation);
    line.setFillColor(sf::Color::Blue);



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
                rotation -= 15;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                rotation += 15;
            }
            if (360 < rotation) {
                rotation -= 360;
            } else if (rotation < -360) {
                rotation += 360;
            }
            // acceleration
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                acceleration_x = 0.1 * cos((rotation-90) * PI / 180.f);
                acceleration_y = 0.1 * sin((rotation-90) * PI / 180.f);
            } else {
            // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                acceleration_x = 0;
                acceleration_y = 0;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                speed_x = 0;
                speed_y = 0;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                alive = true;
            }
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // LOGIC
        speed_y += acceleration_y;
        speed_x += acceleration_x;
        positon_y += speed_y;
        positon_x += speed_x;
        positon_y = (int)positon_y % SCREEN_Y;
        positon_x = (int)positon_x % SCREEN_X;

        a_positon_y += a_speed_y;
        a_positon_x += a_speed_x;
        a_positon_y = (int)a_positon_y % SCREEN_Y;
        a_positon_x = (int)a_positon_x % SCREEN_X;
        // loop ship
        if (positon_y < 0) {
            positon_y = SCREEN_Y;
        }
        if (positon_x < 0) {
            positon_x = SCREEN_X;
        }
        // loop asteroid
        a_positon_y = (int)a_positon_y % SCREEN_Y;
        a_positon_x = (int)a_positon_x % SCREEN_X;
        if (a_positon_y < 0) {
            a_positon_y = SCREEN_Y;
        }
        if (a_positon_x < 0) {
            a_positon_x = SCREEN_X;
        }
        // game over
        if (pow(a_positon_x - positon_x, 2) + pow(a_positon_y - positon_y, 2) <
            pow(damage_radius, 2) && a_alive) {
                printf("The end");
                window.close();
        }
        if (pow(a_positon_x - b_positon_x, 2) + pow(a_positon_y - b_positon_y, 2) <
            pow(damage_radius, 2)) {
                a_alive = false;
        }

        // RENDER
        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        ship.setPosition(positon_x, positon_y);
        ship.setRotation(rotation);
        window.draw(ship);

        asteroid.setPosition(a_positon_x, a_positon_y);
        if (a_alive) {
            window.draw(asteroid);
        }


        if (alive) {
            if (life_time == 4 * 60) {
                b_positon_x = positon_x - 2;
                b_positon_y = positon_y;
                b_rotation = rotation;
                b_speed_x = speed_x + 10 * cos((rotation-90) * PI / 180.f);
                b_speed_y = speed_y + 10 * sin((rotation-90) * PI / 180.f);
            }
            life_time--;
            line.setPosition(b_positon_x, b_positon_y);
            line.setRotation(b_rotation - 90);
            window.draw(line);
            if (life_time < 1) {
                alive = false;
            }
            b_positon_x += b_speed_x;
            b_positon_y += b_speed_y;

        } else {
            life_time = 4 * 60;
        }

        AAA.draw();
        // end the current frame
        window.display();
    }

    return 0;
}