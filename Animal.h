#ifndef PR1_ANIMAL_H
#define PR1_ANIMAL_H

#include "Organism.h"

class Animal : Organism {
    void action() override;
    void collision() override;
    void draw() override;

};


#endif //PR1_ANIMAL_H
