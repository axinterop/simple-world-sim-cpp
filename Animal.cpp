#include "Animal.h"

#include "World.h"

void Animal::Action(World &W) {
    setPos(W.getRandomPosNearby(pos));
}

COLLISION_STATUS Animal::Collision(Organism &other) {
    if (this->getType() == other.getType()) {
        // Breeding is handled in World::ReactOnCollision() because it needs World's fields.
        // Not the best solution.
        if (this->canBreed() && other.canBreed()) {
            RevertPos();
            return COLLISION_STATUS::BREED;
        }
    } else if (this->getStrength() >= other.getStrength()) {
        if (other.getType() == GRASS || other.getType() == SONCHUS)
            return COLLISION_STATUS::STAY;
        if (other.getType() == GUARANA) {
            strength += 3;
            other.Die();
            return COLLISION_STATUS::BOOST_EATING;
        } else if (isAttackBlocked(other)) {
            RevertPos();
            return COLLISION_STATUS::BLOCK_ATTACK;
        } else if (escapedFight(other)) {
            return COLLISION_STATUS::ESCAPE;
        } else {
            other.Die();
            return COLLISION_STATUS::KILL;
        }
    } else if (this->getStrength() < other.getStrength()) {
        if (avoidedDeath(other)) {
            RevertPos();
            return COLLISION_STATUS::AVOID_DEATH;
        } else {
            if (other.getType() == BELLADONNA || other.getType() == H_SOSNOWSKYI) {
                this->Die();
                other.Die();
                return COLLISION_STATUS::DIE_EATING;
            } else {
                this->Die();
                return COLLISION_STATUS::DIE;
            }
        }
    }

    RevertPos();
    return COLLISION_STATUS::STAY;
}


bool Animal::isAttackBlocked(Organism &other) {
    // `this` is an attacker
    if (this->getStrength() >= other.getStrength()) {
        if (other.getType() == TURTLE && this->getStrength() < 5)
            return true;
    }
    return false;
}

bool Animal::escapedFight(Organism &other) {
    // `this` is an attacker
    if (other.getType() == HUMAN) {
        auto h = dynamic_cast<Human *>(&other);
        if (h->isPowerful())
            return true;
    }
    if (other.getType() == ANTILOPE)
        return (bool) rand() % 2;
    return false;
}

bool Animal::avoidedDeath(Organism &other) {
    if (this->getType() == HUMAN) {
        auto h = dynamic_cast<Human *>(this);
        if (h->isPowerful())
            return true;
    }
    return false;
}
