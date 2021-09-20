#include "AsteroidList.hpp"
#include <Ship.hpp>
#include <Asteroid.hpp>

AsteroidList::AsteroidList() {
    // create empty AsteroidList
    count           = 0;
    current_element = NULL;
    first_element   = NULL;
    last_element    = NULL;
}

AsteroidList::~AsteroidList() {
    current_element = first_element;
    while (!DeleteCurrentElement()) {}
}

void AsteroidList::Append(sf::RenderWindow window, sf::Vector2i resolution,
                  sf::Vector2f position) {
    Element *new_element      = new Element;
    new_element->data         = new Asteroid(window, resolution, position);
    new_element->next_element = NULL;
    new_element->prev_element = NULL;
    if (count) {
        last_element->next_element = new_element;
        new_element->prev_element  = last_element;
        last_element               = new_element;
        count++;
    } else {
        count           = 1;
        first_element   = new_element;
        last_element    = new_element;
    }
}


void *AsteroidList::GetCurrentData() {
    return current_element->data;
}

int AsteroidList::DeleteCurrentElement() {
    Element *to_delete = current_element;

    if (!count) {
        std::cout << "ERROR empty AsteroidList" << std::endl;
        return 1; 
    } else if (count == 1) {
        // delete element from AsteroidList wich conteines only one element
        current_element = NULL;
        first_element = NULL;
        last_element = NULL;

    } else if (current_element->next_element == NULL) {
        // try to delete last element
        current_element->prev_element->next_element = NULL;
        current_element = current_element->prev_element;
        last_element = current_element;
    } else if (current_element->prev_element == NULL) {
        // try to delete first element
        current_element->next_element->prev_element = NULL;
        current_element = current_element->next_element;
        first_element = current_element;
    } else {
        current_element->next_element->prev_element = current_element->prev_element;
        current_element->prev_element->next_element = current_element->next_element;
    }

    count--;
    delete to_delete->data;
    delete to_delete;
    std::cout << "delete object" << std::endl;
    return 0;
}

int AsteroidList::NextElement() {
    // return true if next element exitst and switch current to next element
    if (current_element->next_element == NULL) {
        return 1;
    } else {
        current_element = current_element->next_element;
        return 0;
    }

}

int AsteroidList::GoToStart() {
    if (count == 0) {
        std::cout << "trying to set ptr on start of empty AsteroidList" << std::endl;
        return 1;
    }
    current_element = first_element;
    return 0;

}

int AsteroidList::GetCapacity() {
    return count;
}

void AsteroidList::PrintInfo() {
    std::cout << "Capacity: " << count << std::endl;
    std::cout << "First: " << first_element << std::endl;
    std::cout << "Last: " << last_element << std::endl;
    std::cout << "Current: " << current_element << std::endl;
}
