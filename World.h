#ifndef PR1_WORLD_H
#define PR1_WORLD_H

#include <vector>

#include "Renderer.h"
#include "Organism.h"
#include "util.h"

using namespace std;

class World {
private:
    const Renderer *R; // TODO: If something doesn't work - remove const
    Rect worldArea;
    vector<Organism> organisms;

    void initOrganisms();
public:
    World(Renderer *, Rect &);
    ~World();
    void makeTurn();
    void drawWorld();

};


#endif //PR1_WORLD_H
