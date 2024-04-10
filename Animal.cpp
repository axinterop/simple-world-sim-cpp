#include "Animal.h"

#include "World.h"

void Animal::Action(World &W) {
    MoveInRandomDirection(W);
}

void Animal::Collision(World &W) {
    for (auto other_o: *W.getOrganisms()) {
        if (this == other_o || other_o->isDead())
            continue;
        if (this->getPos() == other_o->getPos()) {
            if (auto as_animal = dynamic_cast<Animal*>(other_o)) {
                // TODO: Give a birth
                RevertPos();
            }
        }
    }
}

void Animal::MoveInRandomDirection(World &W) {
    // TODO: Refactor MoveInRandomDirection()
    Point potentialPos = {};
    int dx[8] = {-1, 1, 0, 0, -1, -1, 1, 1};
    int dy[8] = {0, 0, -1, 1, -1, 1, -1, 1};
    while (!W.WithinWorldArea(potentialPos)) {
        potentialPos = pos;
        int s = rand() % 8;
        potentialPos.x += dx[s];
        potentialPos.y += dy[s];
    }
    prevPos = pos;
    pos = potentialPos;
}
