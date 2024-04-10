#ifndef PR1_WORLD_H
#define PR1_WORLD_H

#include <vector>
#include <algorithm>

#include "WorldListener.h"
#include "Organism.h"
#include "Animal.h"
#include "util.h"


using namespace std;

class World {
private:
    const Rect worldArea;
    WorldListener WListener {};
    vector<Organism*> organisms;

    int turnsNum {};

    void InitOrganisms();

    void OrganismsSortAndCleanUp();

    friend class Renderer;
public:
    World(const Rect &worldArea);
    ~World();

    void MakeTurn();

    void CreateAnimal(Animal *an);
    void CreateAnimal(int s, int i,  Point p);

    bool WithinWorldArea(Point pos) const;
    int getTurnsNum() { return turnsNum; };

    const vector<Organism*> *getOrganisms() { return &organisms; };
    int getOrganismsNum() { return organisms.size(); };
};

#include "Renderer.h"

#endif //PR1_WORLD_H