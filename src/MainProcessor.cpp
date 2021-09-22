#include <SFML/Graphics.hpp>
#include <MainProcessor.hpp>
#include <Asteroid.hpp>
#include <Ship.hpp>
#include <Bullet.hpp>
#include <List.hpp>
#include <math.h>
#include <iostream>
#include <list>

#define PI 3.14159265

bool b_is_not_alive(Bullet& bullet) { 
    return (!bullet.IsAlive()); 
}

bool a_is_not_alive(Asteroid& asteroid) { 
    return (!asteroid.IsAlive()); 
}

bool hit_bullet(sf::Vector2f asteroid_pos, sf::Vector2f bullet_pos, long double asteroid_radious) {
    if (
        std::pow((bullet_pos.x - asteroid_pos.x), 2) + std::pow((bullet_pos.y - asteroid_pos.y), 2) < std::pow(asteroid_radious, 2)) {
        return true;
    }
    return false;
}

void MainProcessor::Run() {
    int time_to_spawn = 1 * 60;
    bool shoot = false;
    long int    frame_counter = 0;
    int         data_type;
    long double direction;
    sf::Vector2f direction_vector;
    Asteroid    *current_asteroid;
    Bullet      *current_bullet;
    sf::RenderWindow win(sf::VideoMode(resolution.x, resolution.y), "Blastar");
    win.setVerticalSyncEnabled(true);
    window = &win;

    Ship ship(sf::Vector2f(resolution/2),
              sf::Vector2f(0, 0), window,
              resolution);
    // add quiues
    std::list<Asteroid> asteroids_list;
    std::list<Asteroid>::iterator asteroids_iterator;
    std::list<Bullet> bullet_list;
    std::list<Bullet>::iterator bullet_iterator;

    sf::Vector2i cursor_position = sf::Mouse::getPosition(*window);
    while (window->isOpen())
    {
        frame_counter++;
        if (!(frame_counter % time_to_spawn)) {
            asteroids_list.push_back(Asteroid(window, resolution, ship.GetPosition()));
            std::cout << bullet_list.size() << std::endl;
            frame_counter %= time_to_spawn;
            time_to_spawn -= 10;
            if (time_to_spawn < 1) {
                time_to_spawn = 5;
            }
        }
        // INPUT
        sf::Event event;
        while (window->pollEvent(event))
        {
            cursor_position = sf::Mouse::getPosition(*window);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                shoot = true;
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
        if (shoot) {
            bullet_list.push_back(Bullet(&ship));
            shoot = false;
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

        bullet_list.remove_if(b_is_not_alive);
        asteroids_list.remove_if(a_is_not_alive);
        window->clear();
        for (asteroids_iterator=asteroids_list.begin();
             asteroids_iterator!=asteroids_list.end();
             asteroids_iterator++) {
            asteroids_iterator->draw();
        }
        for (bullet_iterator=bullet_list.begin();
             bullet_iterator!=bullet_list.end();
             bullet_iterator++) {
            sf::Vector2f bp = bullet_iterator->GetPosition();
            for (asteroids_iterator=asteroids_list.begin();
                asteroids_iterator!=asteroids_list.end();
                asteroids_iterator++) {
                sf::Vector2f ap = asteroids_iterator->GetPosition();
                long double ar = asteroids_iterator->GetRadious();
                if (hit_bullet(ap, bp, ar)) {
                    asteroids_iterator->asteroid_die();
                }
            }
            bullet_iterator->draw();
        }
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