#ifndef PR1_ANIMAL_H
#define PR1_ANIMAL_H

#include "Organism.h"

class Animal : public Organism {
public:
    void Action() override;
    void Collision() override;
};


#endif //PR1_ANIMAL_H
