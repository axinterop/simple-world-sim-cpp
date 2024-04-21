#ifndef PR1_ANIMAL_H
#define PR1_ANIMAL_H

#include "Organism.h"

class Animal : public Organism {
public:
    using Organism::Organism;
    void Action(World &W) override;
    COLLISION_STATUS Collision(Organism &other) override;
    std::string className() override = 0;

    bool isAttackBlocked(Organism &other);
    bool escapedFight(Organism &other);
    bool avoidedDeath(Organism &other);
};


#endif //PR1_ANIMAL_H
