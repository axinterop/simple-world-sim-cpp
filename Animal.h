#ifndef PR1_ANIMAL_H
#define PR1_ANIMAL_H

#include "Organism.h"

class Animal : public Organism {
private:
    void MoveInRandomDirection(World &W);
public:
    using Organism::Organism;
    void Action(World &W) override;
    void Collision(World &W) override;
};


#endif //PR1_ANIMAL_H
