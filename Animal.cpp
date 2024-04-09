#include "Animal.h"

#include "World.h"

void Animal::Action(World &W) {
    MoveInRandomDirection(W);
}

void Animal::Collision(World &W) {

}

void Animal::MoveInRandomDirection(World &W) {
    // TODO: Refactor MoveInRandomDirection()
    Point potentialPos = {};
    int dx[8] = {-1, 1, 0, 0, -1, -1, 1, 1};
    int dy[8] = {0, 0, -1, 1, -1, 1, -1, 1};
    while (!W.WithinWorldArea(potentialPos)) {
        potentialPos = pos;
        potentialPos.x += dx[rand() % 8];
        potentialPos.y += dy[rand() % 8];
    }
    pos = potentialPos;
}
