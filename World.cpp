#include "World.h"
#include <iostream> // TODO: remove temp

World::World(Rect &a) {
    worldArea = a;
    std::cout << "WORKS" << std::endl;
    InitOrganisms();
}

World::~World() {
    for (auto & organism : organisms)
        delete organism;
}

void World::InitOrganisms() {
    // TODO: Create random num of every organism and set random pos that is within worldArea
    Animal *a = new Animal();
    organisms.push_back(a);

    // TODO: Move this to WorldListener, so will pass only *a to func;
    WorldEvent e;
//    e.title = "  Animal creation...";
    e.details = "Animal(" + to_string(a->getId()) + ") was created";
    WListener.AddEvent(e);
}

void World::MakeTurn() {
//    string e_title = "  Animal acting...";
    for (auto & organism : organisms) {
        organism->Action();
        WListener.AddEvent("Animal acted");
        organism->Collision();
        WListener.AddEvent("Animal collided");
    }
    // for every creature:
    // - Action()
    // - check Collision()
    // - react
    // - log event
}
