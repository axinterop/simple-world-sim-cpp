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
    for (auto &chunk: plantChunks) {
        delete chunk;
    }
}

void World::InitOrganisms() {
    // within worldArea
    double f = 80; // 80
    double c = f / 10000.0f;
    int oNum = (int) (worldArea.h * worldArea.w * c);
    for (int i = 0; i < oNum * 0.2; i++) {
        CreateOrganism(WOLF);
        CreateOrganism(SHEEP);
        CreateOrganism(FOX);
        CreateOrganism(TURTLE);
        CreateOrganism(ANTILOPE);
        CreatePlantChunk(GRASS);
        CreatePlantChunk(SONCHUS);
        CreatePlantChunk(GUARANA);
        CreatePlantChunk(BELLADONNA);
        CreatePlantChunk(H_SOSNOWSKYI);
    }
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

    for (auto o: organisms)
        o->canMakeTurn = true;


    for (auto &chunk: plantChunks) {
        if (chunk->isEmpty())
            delete chunk;
        else
            chunk->seeded_this_turn = false;
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
        if (this_o->isDead() || !this_o->canMakeTurn)
            break;


        // World is not paused: start of Player's input handling
        if (!worldPaused && this_o->getType() == HUMAN) {
            auto h = dynamic_cast<Human*>(this_o);
            human_power_turns = h->getPowerTurns();
            human_power_CD = h->getPowerCD();
            worldPaused = true;
            return;
        }

        // World is paused: 'for' until Human
        if (worldPaused && this_o->getType() != HUMAN)
            continue;

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


        if (!this_o->isDead()) {
            this_o->AfterTurn(*this);
        }
    }
}

Organism& World::CreateOrganism(Organism *o) {
    if (turnsNum != 0) {
        o->breedSetPause(30);
        o->canMakeTurn = false;
    }
    else {
        o->breedSetPause(20);
        o->canMakeTurn = true;
    }
    organisms.push_back(o);
    return *o;
}

Organism& World::CreateOrganism(ORGANISM_E o_t) {
    Point potentialPos = {};
    do {
        potentialPos = {rand() % worldArea.w + 1, rand() % worldArea.h + 1};
    } while (!isPlaceFree(potentialPos));
    return CreateOrganism(o_t, potentialPos);
}

Organism& World::CreateOrganism(ORGANISM_E o_t, Point p) {
    // TODO: Hard coded strengths and initiatives
    if (o_t == WOLF)
        return CreateOrganism(new Wolf(9, 5, 0, p));
    else if (o_t == SHEEP)
        return CreateOrganism(new Sheep(4, 4, 0, p));
    else if (o_t == FOX)
        return CreateOrganism(new Fox(3, 7, 0, p));
    else if (o_t == TURTLE)
        return CreateOrganism(new Turtle(2, 1, 0, p));
    else if (o_t == ANTILOPE)
        return CreateOrganism(new Antilope(4, 4, 0, p));
    else if (o_t == HUMAN)
        return CreateOrganism(new Human(5, 4, 0, p));

    else if (o_t == GRASS)
        return CreateOrganism(new Grass(0, 0, 0, p));
    else if (o_t == SONCHUS)
        return CreateOrganism(new Sonchus(0, 0, 0, p));
    else if (o_t == GUARANA)
        return CreateOrganism(new Guarana(0, 0, 0, p));
    else if (o_t == BELLADONNA)
        return CreateOrganism(new Belladonna(99, 0, 0, p));
    else if (o_t == H_SOSNOWSKYI)
        return CreateOrganism(new H_Sosnowskyi(10, 0, 0, p));
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

void World::CreatePlantOffspring(Organism &p1) {
    ORGANISM_E type = p1.getType();
    auto *p = dynamic_cast<Plant *>(&p1);
    auto *pChunk = p->getChunk();
    for (auto & organism : organisms)
        if (organism->getId() == p->getRandomChunkPlantID()) {
            Point new_pos = getFreePosNearby(organism->getPos());
            if (new_pos == Point{0, 0})
                return;
            auto *new_plant = dynamic_cast<Plant *>(&CreateOrganism(type, new_pos));
            new_plant->setChunk(pChunk);
            pChunk->addPlantID(new_plant->getId());
            break;
        }
}

Point World::FindPosNearParents(Point p1, Point p2) {
    Point potentialPos = p2;
    while (potentialPos == p2) {
        potentialPos = getFreePosNearby(p1);
    }
    return potentialPos;
}

void World::CreatePlantChunk(ORGANISM_E o_t, Point pos) {
    PlantChunk *plantChunk = new PlantChunk();

    auto plant = dynamic_cast<Plant *>(&CreateOrganism(o_t, pos));

    plantChunk->addPlantID(plant->getId());
    plantChunks.push_back(plantChunk);
    plant->setChunk(plantChunk);
}

void World::CreatePlantChunk(ORGANISM_E o_t) {
    Point potentialPos = {};
    do {
        potentialPos = {rand() % worldArea.w + 1, rand() % worldArea.h + 1};
    } while (!isPlaceFree(potentialPos));
    CreatePlantChunk(o_t, potentialPos);
}

bool World::setHumanAction(PLAYER_ACTION a) {
    human_action = a;
    return true;
}



