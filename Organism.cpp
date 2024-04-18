#include "Organism.h"
#include "World.h"

int Organism::free_id = 0;

void Organism::RevertPos() {
    Point temp = pos;
    pos = prevPos;
    prevPos = temp;
};

void Organism::Action(World &W) {}
COLLISION_STATUS Organism::Collision(Organism &other) { return UNDEFINED; }

void Organism::AfterTurn(World &W) {
    getOlder();
//    if (type != HUMAN && age > maxLifeTime) {
//        Die();
//        W.WListener.RecordEvent(classInfo() + " is too old to live...");
//    }
//    else
        breedDecreasePause();
}
