#include <SFML/Graphics.hpp>
#include <MainProcessor.hpp>
#include <Asteroid.hpp>
#include <Ship.hpp>
#include <Bullet.hpp>
#include <math.h>
#include <list>
#include <CommonConst.hpp>
#include <AbstractPhysicalObject.hpp>
#include <AbstractVisibleObject.hpp>


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

float DotProduct(sf::Vector2f rv, sf::Vector2f normal) {
        return (rv.x * normal.x + rv.y * normal.y) / sqrt(pow(normal.x, 2) + pow(normal.y, 2));
}

// void resolve_collision(std::__cxx11::list<AbstractPhysicalObject>::iterator&A, std::__cxx11::list<AbstractPhysicalObject>::iterator&B) {
//     // Вычисляем относительную скорость
//     sf::Vector2f rv = B->GetSpeed()- A->GetSpeed();
//     sf::Vector2f normal = B->GetPosition() - A->GetPosition();
//     float normal_k = sqrt(pow(normal.x, 2) + pow(normal.y, 2));
//     normal.x /= normal_k;
//     normal.y /= normal_k;

//     // Вычисляем относительную скорость относительно направления нормали
//     float velAlongNormal = DotProduct(rv, normal);

//     // Не выполняем вычислений, если скорости разделены
//     if(velAlongNormal > 0) {
//             return;
//     }

//     // Вычисляем упругость
//     float e = 1;

//     // Вычисляем скаляр импульса силы
//     float j = -(1 + e) * velAlongNormal;
//     // j /= 1 / A->mass + 1 / B->mass;
//     j /= 1 / 1 + 1 / 1;

//     // Прикладываем импульс силы
//     sf::Vector2f impulse = j * normal;
//     // A->velocity -= 1 / A->mass * impulse;
//     // B->velocity += 1 / B->mass * impulse;
//     A->SetSpeed(A->GetSpeed()-impulse);
//     B->SetSpeed(B->GetSpeed()+impulse);

//     // std::cout << "velAlongNormal: " << velAlongNormal << std::endl;
//     // std::cout << "impulse" << impulse.x << std::endl;
//     // std::cout << "impulse" << impulse.y << std::endl;
//     // std::cout << "Av x: " << A->velocity.x << std::endl;
//     // std::cout << "Av y: " << A->velocity.y << std::endl;
//     // std::cout << "Bv x: " << B->velocity.x << std::endl;
//     // std::cout << "Bv y: " << B->velocity.y << std::endl;
// }


void check_colision(std::list<void*> &common_list) {
    std::list<AbstractPhysicalObject*> collaps_list;
    for (void* cur_list: common_list) {
        for (auto cur_obj: (std::list<AbstractPhysicalObject>)cur_list) {
            collaps_list.push_back(&cur_obj);
        }
    }
    std::list<AbstractPhysicalObject>::iterator common_iterator_left;
    std::list<AbstractPhysicalObject>::iterator common_iterator_right;

    for (common_iterator_left=collaps_list.begin();
         common_iterator_left!=collaps_list.end();
         common_iterator_left++) {
        for (common_iterator_right=common_iterator_left;
             common_iterator_right!=common_iterator_right.end();
             common_iterator_right++) {
            // resolve_collision(common_iterator_left, common_iterator_right);
        }
    }
}

void MainProcessor::Run() {
    int                 cooldown = 10;
    int                 current_cooldown = 0;
    int                 time_to_spawn = 1 * 60;
    bool                shoot = false;
    long int            frame_counter = 0;
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

    // add lists
    std::list<AbstractPhysicalObject*> common_apo_list;
    std::list<AbstractVisibleObject*> common_avo_list;
    std::list<Asteroid*> asteroids_list;
    std::list<Bullet*> bullet_list;
    std::list<Ship*> ship_list;

    // add iterators
    std::list<Asteroid>::iterator asteroids_iterator;
    std::list<Bullet>::iterator bullet_iterator;

    while (window->isOpen())
    {
        if (current_cooldown > 0) {
            current_cooldown--;
        }
        frame_counter++;
        if (!(frame_counter % time_to_spawn)) {
            auto *tmp = new Asteroid(window, resolution, ship.GetPosition());

            // TODO make class context
            asteroids_list.push_back(tmp);
            common_apo_list.push_back(tmp);

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
            bullet_list.push_back(tmp);
            common_apo_list.push_back(tmp);
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

        // bullet_list.remove_if(b_is_not_alive);
        // asteroids_list.remove_if(a_is_not_alive);


        window->clear();
        for (auto &object: asteroids_list) {
            object->draw();
        }
        for (auto &object: bullet_list) {
            object->draw();
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
