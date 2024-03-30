#ifndef PR1_ORGANISM_H
#define PR1_ORGANISM_H

#include "util.h"

class Organism {
    int strength;
    int initiative;
    int age;
    Point pos;

    virtual void action() = 0;
    virtual void collision() = 0;
    virtual void draw() = 0;
};


#endif //PR1_ORGANISM_H
