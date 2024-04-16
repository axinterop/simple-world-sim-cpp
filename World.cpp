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

World::World(const Rect &worldArea) : worldArea(worldArea) { InitOrganisms(); }

World::~World() {
    for (auto &organism : organisms) {
        delete organism;
    }
}

void World::InitOrganisms() {
    // TODO: Create random num of every organism and set random pos that is
    // within worldArea
    double f = 80;
    double c = f / 10000.0f;
    int oNum = (int)(worldArea.h * worldArea.w * c);
    for (int i = 0; i < oNum * 0.2; i++) {
        CreateOrganism(WOLF);
        CreateOrganism(SHEEP);
        CreateOrganism(FOX);
        CreateOrganism(TURTLE);
        CreateOrganism(ANTILOPE);
    }
    //    CreateOrganism(WOLF);
    //    CreateOrganism(SHEEP);
    //    CreateOrganism(FOX);
    //    CreateOrganism(TURTLE);
    //    CreateOrganism(ANTILOPE);
    CreateOrganism(HUMAN);
}

void World::OrganismsSortAndCleanUp() {
    if (!is_sorted(organisms.begin(), organisms.end(),
                   OrganismInitiativeComparator)) {
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
}

bool World::isPlaceFree(Point p) {
    for (auto &o : organisms) {
        if (o->getPos() == p)
            return false;
    }
    return true;
}

void World::MakeTurn() {
    if (!worldPaused)
        turnsNum++;

    OrganismsSortAndCleanUp();

    for (auto &o : organisms) {
        // World is paused, 'for' until Human
        if (worldPaused && o->getType() != HUMAN)
            continue;

        if (!o->isDead()) {
            // World is not paused, begin to handle Player input
            if (!worldPaused && o->getType() == HUMAN) {
                worldPaused = true;
                return;
            }



            o->Action(*this);
            //            WListener.AddEvent(
            //                    o->className() + "(" + to_string(o->getId()) +
            //                    ") with initiative (" +
            //                    to_string(o->getInitiative()) +
            //                    ") moved");
            o->Collision(*this);

            // If World is unpaused, it will be ignored
            // If World is paused, current 'o' is Human, it made its Action()
            // and Collision(), so unpause
            if (worldPaused)
                worldPaused = false;

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

void World::CreateOrganism(Organism *o) {
    organisms.push_back(o);

    WorldEvent e;
    e.details = "Create: " + o->className() +
                "(id: " + std::to_string(o->getId()) +
                ", initiative: " + std::to_string(o->getInitiative()) + ")";
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
    if (pos.x >= worldArea.x && pos.x <= worldArea.w && pos.y >= worldArea.y &&
        pos.y <= worldArea.h)
        return true;
    return false;
}

void World::CreateOffspring(Organism &p1, Organism &p2) {

    if (p1.getType() != p2.getType())
        return;
    Point newPos {};
    if (p1.getPos() == p2.getPos())
        newPos = FindPosNearParents(p1.getPrevPos(), p2.getPos());
    else
        newPos = FindPosNearParents(p1.getPos(), p2.getPos());
    ORGANISM_E type = p1.getType();
    CreateOrganism(type, newPos);
}

Point World::FindPosNearParents(Point p1, Point p2) {
    Point r = {p1.x + p1.x - p2.x, p1.y + p1.y - p2.y};
    return r;
}

