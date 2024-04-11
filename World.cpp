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
    CreateOrganism(WOLF);
    CreateOrganism(SHEEP);
    CreateOrganism(FOX);
    CreateOrganism(TURTLE);
    CreateOrganism(ANTILOPE);
    CreateOrganism(HUMAN);
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


bool World::isPlaceFree(Point p) {
    for (auto &o: organisms) {
        if (o->getPos() == p)
            return false;
    }
    return true;
}

void World::MakeTurn() {
    turnsNum++;

    OrganismsSortAndCleanUp();

    for (auto &o: organisms) {
        if (!o->isDead()) {
            o->Action(*this);
            WListener.AddEvent(
                    o->className() + "(" + to_string(o->getId()) + ") with initiative (" + to_string(o->getInitiative()) +
                    ") moved");
            o->Collision(*this);
        }

//        if (turnsNum == 5 && o->getId() == 1)
//            o->Die();

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

void World::CreateOrganism(Organism *o) {
    organisms.push_back(o);

    WorldEvent e;
    e.details =
            "Create: " + o->className() + "(id: " + to_string(o->getId()) + ", initiative: " + to_string(o->getInitiative()) + ")";
    WListener.AddEvent(e);
}

void World::CreateOrganism(ORGANISM_E o_t) {
    Point potentialPos = {};
    do {
        potentialPos = {rand() % worldArea.w + 1, rand() % worldArea.h + 1};
    } while (!isPlaceFree(potentialPos));
    CreateOrganism(o_t, potentialPos);
}

void World::CreateOrganism(ORGANISM_E o_t, Point p) {
    // TODO: Hard coded strengths and initiatives
    if (o_t == WOLF)
        CreateOrganism(new Wolf(9, 5, 0, p));
    else if (o_t == SHEEP)
        CreateOrganism(new Sheep(4, 4, 0, p));
    else if (o_t == FOX)
        CreateOrganism(new Fox(3, 7, 0, p));
    else if (o_t == TURTLE)
        CreateOrganism(new Turtle(2, 1, 0, p));
    else if (o_t == ANTILOPE)
        CreateOrganism(new Antilope(4, 4, 0, p));
    else if (o_t == HUMAN)
        CreateOrganism(new Human(5, 4, 0, p));
}

bool World::WithinWorldArea(Point pos) const {
    if (pos.x >= worldArea.x && pos.x <= worldArea.w && pos.y >= worldArea.y && pos.y <= worldArea.h)
        return true;
    return false;
}

