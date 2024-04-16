#include "Animal.h"

#include "World.h"

void Animal::Action(World &W) {
    MoveInRandomDirection(W);
}

void Animal::Collision(World &W) {
    // TODO: Maybe handle collisions in the world class and just call o.ReactCollision(Organism &other) if there is a collision?
    for (auto other_o: *W.getOrganisms()) {
        if (this == other_o || other_o->isDead())
            continue;
        if (this->getPos() == other_o->getPos()) {
            if (this->getType() == other_o->getType()) {
                RevertPos();
                // TODO: Every animal should contain information about its parents (2 ids) and, if it collides with its parents - do nothing
//                W.CreateOffspring(*this, *other_o); // TODO: Uncomment and implement
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
    setPos(potentialPos);
}

