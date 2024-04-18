#include "Turtle.h"

void Turtle::Action(World &W) {
    if (rand() % 4 == 0)
        Animal::Action(W);
}

