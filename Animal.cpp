#include "Animal.h"
#include <iostream> // TODO: Remove (temp)

void Animal::Action() {
    std::cout << "Animal(" << id << ") acted." << std::endl;
}

void Animal::Collision() {
    std::cout << "Animal(" << id << ") collided." << std::endl;
}
