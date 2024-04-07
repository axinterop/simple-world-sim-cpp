#ifndef PR1_WORLD_H
#define PR1_WORLD_H

#include <vector>

#include "WorldListener.h"
#include "Organism.h"
#include "Animal.h"
#include "util.h"


using namespace std;

class World {
private:
    WorldListener WListener {};
    vector<Organism*> organisms;

    Rect worldArea;
    void InitOrganisms();

    friend class Renderer;
public:
    World(Rect &);
    ~World();
    void MakeTurn();
};

#include "Renderer.h"

#endif //PR1_WORLD_H