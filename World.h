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

    void InitOrganisms();

    void CreateAnimal(Animal *an);
    void CreateAnimal(int s, int i, int a, Point p);

    friend class Renderer;
public:
    World(const Rect &worldArea);
    ~World();
    void MakeTurn();
    const Rect worldArea;
    bool WithinWorldArea(Point pos);
};

#include "Renderer.h"

#endif //PR1_WORLD_H