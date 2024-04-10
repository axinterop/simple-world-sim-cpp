#include "World.h"

bool OrganismInitiativeComparator(Organism *o1, Organism *o2) {
    if (o1->isDead())
        return false;
    if (o2->isDead())
        return true;

    if (o1->getInitiative() == o2->getInitiative())
        return (o1->getAge() > o2->getAge());
    return o1->getInitiative() > o2->getInitiative();
}

World::World(const Rect &worldArea) : worldArea(worldArea) {
    InitOrganisms();
}

World::~World() {
    for (auto &organism: organisms) {
        delete organism;
    }
}

void World::InitOrganisms() {
    // TODO: Create random num of every organism and set random pos that is within worldArea
//    CreateAnimal(1, 1, {2, 1});
//    CreateAnimal(1, 2, {1,1});
//    CreateAnimal(1, 1, {rand() % worldArea.w + 1,rand() % worldArea.h + 1});
    CreateAnimal(1, 8, {rand() % worldArea.w + 1, rand() % worldArea.h + 1});
    CreateAnimal(1, 4, {rand() % worldArea.w + 1, rand() % worldArea.h + 1});
    CreateAnimal(1, 2, {rand() % worldArea.w + 1, rand() % worldArea.h + 1});
}


void World::OrganismsSortAndCleanUp() {
    // Sort, so dead organisms are at the end
    sort(organisms.begin(), organisms.end(), OrganismInitiativeComparator);
    // Remove from where first dead organism appear until end
    for (int i = 0; i < organisms.size(); i++) {
        if (organisms[i]->isDead()) {
            delete organisms[i];
            organisms.erase(organisms.begin() + i);
        }
    }
}


void World::MakeTurn() {
    turnsNum++;

    OrganismsSortAndCleanUp();

    for (auto &o: organisms) {
        if (!o->isDead()) {
            o->Action(*this);
            WListener.AddEvent(
                    "Animal(" + to_string(o->getId()) + ") with initiative (" + to_string(o->getInitiative()) +
                    ") moved");
            o->Collision(*this);
        }

        // TODO: During collision if organism dies, call o.Die();
        if (!o->isDead()) {
            o->getOlder();
        }

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
    e.details =
            "Animal(" + to_string(an->getId()) + ") with initiative (" + to_string(an->getInitiative()) + ") created";
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

