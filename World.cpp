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
    CreateAnimal(1, 1, {2, 1});
    CreateAnimal(1, 1, {1,1});
    CreateAnimal(1, 1, {rand() % worldArea.w + 1,rand() % worldArea.h + 1});
    CreateAnimal(1, 1, {rand() % worldArea.w + 1,rand() % worldArea.h + 1});
    CreateAnimal(1, 1, {rand() % worldArea.w + 1,rand() % worldArea.h + 1});
    CreateAnimal(1, 1, {rand() % worldArea.w + 1,rand() % worldArea.h + 1});
}


void World::MakeTurn() {
    // TODO: Sort all organisms by initiative (the biggest on the right)
    for (auto & o : organisms) {
        o->Action(*this);
        o->Collision(*this);

        // TODO: During collision if organism dies, call o.Die();
        if (!o->isDead())
            o->getOlder();

    }

    // for every creature:
    // - Action()
    // - check Collision()
    // - react
    // - log event

    // Clean organisms vector from dead organisms
    // Maybe, sort all organisms, so dead organism are on right, and just pop() X times?
    // ...
    for (int i = 0; i < organisms.size(); i++) {
        if (organisms[i]->isDead())
            organisms.erase(organisms.begin() + i);
    }

    turnsNum++;
}

void World::CreateAnimal(Animal *an) {
    organisms.push_back(an);

    WorldEvent e;
    e.details = "Animal(" + to_string(an->getId()) + ") was created";
    WListener.AddEvent(e);
}

void World::CreateAnimal(int s, int i, Point p) {
    CreateAnimal(new Animal(s, i, 0, p));
}

bool World::WithinWorldArea(Point pos) const {
    if (pos.x >= worldArea.x && pos.x <= worldArea.w && pos.y >= worldArea.y && pos.y <= worldArea.h)
        return true;
    return false;
}
