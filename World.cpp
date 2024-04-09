#include "World.h"

World::World(const Rect &worldArea) : worldArea(worldArea) {
    InitOrganisms();
}

World::~World() {
    for (auto & organism : organisms) {
        delete organism;
    }
}

void World::InitOrganisms() {
    // TODO: Create random num of every organism and set random pos that is within worldArea
    CreateAnimal(1, 1, 1, {rand() % worldArea.w + 1,rand() % worldArea.h + 1});
    CreateAnimal(1, 1, 1, {1,1});
}

void World::MakeTurn() {
    for (auto & organism : organisms) {
        organism->Action(*this);
        organism->Collision(*this);
    }
    // for every creature:
    // - Action()
    // - check Collision()
    // - react
    // - log event
}

void World::CreateAnimal(Animal *an) {
    organisms.push_back(an);

    WorldEvent e;
    e.details = "Animal(" + to_string(an->getId()) + ") was created";
    WListener.AddEvent(e);
}

void World::CreateAnimal(int s, int i, int a, Point p) {
    CreateAnimal(new Animal(s, i, a, p));
}

bool World::WithinWorldArea(Point pos) {
    if (pos.x >= worldArea.x && pos.x <= worldArea.w && pos.y >= worldArea.y && pos.y <= worldArea.h)
        return true;
    return false;
}
