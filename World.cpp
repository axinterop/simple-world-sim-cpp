#include "World.h"

World::World(Renderer *r, Rect &a) {
    R = r;
    worldArea = a;
    initOrganisms();
}

World::~World() {

}

void World::initOrganisms() {
    // TODO: Create random num of every organism and set random pos that is within worldArea
}

void World::makeTurn() {
    // for every creature:
    // - action()
    // - check collision()
    // - react
    // - log event
}

void World::drawWorld() {
    // for every creature call draw()
}
