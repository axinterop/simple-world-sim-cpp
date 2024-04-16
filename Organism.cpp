#include "Organism.h"

int Organism::free_id = 0;

void Organism::RevertPos() {
    Point temp = pos;
    pos = prevPos;
    prevPos = temp;
};

void Organism::Action(World &W) {}
void Organism::Collision(World &W) {}