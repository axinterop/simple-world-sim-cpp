#ifndef PR1_WORLD_H
#define PR1_WORLD_H

#include <vector>
#include <algorithm>
#include <typeinfo>

#include "WorldListener.h"
#include "Organism.h"
#include "animals/Wolf.h"
#include "animals/Sheep.h"
#include "animals/Fox.h"
#include "animals/Turtle.h"
#include "animals/Antilope.h"
#include "animals/Human.h"
#include "util.h"


using namespace std;

class World {
private:
    const Rect worldArea;
    WorldListener WListener {};
    vector<Organism*> organisms;

    int turnsNum {};

    void InitOrganisms();

    void CreateOrganism(Organism *o);
    void CreateOrganism(ORGANISM_E o_t);
    void CreateOrganism(ORGANISM_E o_t, Point p);

    void OrganismsSortAndCleanUp();

    bool isPlaceFree(Point p);

    friend class Renderer;
public:
    World(const Rect &worldArea);

    ~World();

    void MakeTurn();

    bool WithinWorldArea(Point pos) const;
    int getTurnsNum() { return turnsNum; };

    const vector<Organism*> *getOrganisms() { return &organisms; };
    int getOrganismsNum() { return organisms.size(); };
};

#include "Renderer.h"

#endif //PR1_WORLD_H