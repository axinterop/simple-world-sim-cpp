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
    for (auto &organism: organisms) {
        delete organism;
    }
}

void World::InitOrganisms() {
    // TODO: Create random num of every organism and set random pos that is
    // within worldArea
    double f = 100; // 80
    double c = f / 10000.0f;
    int oNum = (int) (worldArea.h * worldArea.w * c);
    for (int i = 0; i < oNum * 0.2; i++) {
        CreateOrganism(WOLF);
        CreateOrganism(SHEEP);
        CreateOrganism(FOX);
        CreateOrganism(TURTLE);
        CreateOrganism(ANTILOPE);
    }
//    CreateOrganism(HUMAN);
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
    for (auto &o: organisms) {
        if (o->getPos() == p)
            return false;
    }
    return true;
}

void World::MakeTurn() {
    if (!worldPaused)
        turnsNum++;

    OrganismsSortAndCleanUp();

    for (auto &this_o: organisms) {
        if (this_o->isDead())
            break;

        // World is paused: 'for' until Human
        if (worldPaused && this_o->getType() != HUMAN)
            continue;

        // World is not paused: start of Player's input handling
        if (!worldPaused && this_o->getType() == HUMAN) {
            worldPaused = true;
            return;
        }

        this_o->Action(*this);

        for (auto &other_o: organisms) {
            if (this_o == other_o || other_o->isDead()) {
                continue;
            }
            if (this_o->getPos() == other_o->getPos()) {
                ReactOnCollision(*this_o, *other_o);
            }
        }

        // If World is not paused, it will be ignored
        // If World is paused, current 'this_o' is Human, it made its Action()
        // and Collision(), so unpause
        if (worldPaused)
            worldPaused = false;


        // TODO: During collision if organism dies, call this_o.Die();
        if (!this_o->isDead()) {
            this_o->AfterTurn(*this);
        }
    }
}

void World::CreateOrganism(Organism *o) {
    if (turnsNum != 0)
        o->breedSetPause(30);
    else
        o->breedSetPause(20);
    organisms.push_back(o);

    WorldEvent e;
    e.details = "Create: " + o->className() +
                "(id: " + std::to_string(o->getId()) +
                ", initiative: " + std::to_string(o->getInitiative()) + ")";
    WListener.RecordEvent(e);
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

void World::ReactOnCollision(Organism &this_o, Organism &other_o) {
    COLLISION_STATUS c_s = this_o.Collision(other_o);

    if (c_s == BREED) {
        CreateOffspring(this_o, other_o);
        this_o.breedSetPause();
        other_o.breedSetPause();
    }

    if (c_s == ESCAPE) {
        other_o.setPos(getFreePosNearby(other_o.getPos()));
    }

    WListener.RecordCollision(c_s, this_o, other_o);
}

bool World::WithinWorldArea(Point pos) const {
    if (pos.x >= worldArea.x && pos.x <= worldArea.w && pos.y >= worldArea.y &&
        pos.y <= worldArea.h)
        return true;
    return false;
}

Point World::getRandomPosNearby(Point pos, int k) {
    // TODO: Refactor getRandomPosNearby()
    Point potentialPos = {0, 0};
    int dx[8] = {-1, 1, 0, 0, -1, -1, 1, 1};
    int dy[8] = {0, 0, -1, 1, -1, 1, -1, 1};
    int dIndex[8]{0, 1, 2, 3, 4, 5, 6, 7};
    int iCount = 0;

    while (iCount != 8) {
        potentialPos = pos;
        int randIndex = rand() % 8;
        int sIndex = dIndex[randIndex];
        if (sIndex == -1)
            continue;

        potentialPos.x += dx[sIndex] * k;
        potentialPos.y += dy[sIndex] * k;
        if (WithinWorldArea(potentialPos))
            return potentialPos;
        else
            dIndex[sIndex] = -1;
        iCount++;
    }
    return pos;
}

Point World::getFreePosNearby(Point pos) {
    Point potentialPos = {0, 0};
    int dx[8] = {-1, 1, 0, 0, -1, -1, 1, 1};
    int dy[8] = {0, 0, -1, 1, -1, 1, -1, 1};
    std::vector<int> dIndex {0, 1, 2, 3, 4, 5, 6, 7};
    int iCount = 0;
    int k = 1;

    while (true) {
        if (iCount == 8) {
            iCount = 0;
            k++;
            dIndex = {0, 1, 2, 3, 4, 5, 6, 7};
        }
        potentialPos = pos;
        int randIndex = rand() % 8;
        int sIndex = dIndex[randIndex];
        if (sIndex == -1)
            continue;

        potentialPos.x += dx[sIndex] * k;
        potentialPos.y += dy[sIndex] * k;
        if (WithinWorldArea(potentialPos)) {
            for (auto other_o: organisms) {
                if (other_o->getPos() != potentialPos)
                    return potentialPos;
            }
        }
        else
            dIndex[sIndex] = -1;
        iCount++;
    }
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
    Point potentialPos = p2;
    while (potentialPos == p2) {
        potentialPos = getFreePosNearby(p1);
    }

    return potentialPos;
}



