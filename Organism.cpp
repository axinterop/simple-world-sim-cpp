#include "Organism.h"

int Organism::free_id = 0;

void Organism::RevertPos() {
    Point temp = pos;
    pos = prevPos;
    prevPos = temp;
};
