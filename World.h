#ifndef PR1_WORLD_H
#define PR1_WORLD_H



#include "WorldListener.h"
#include "Organism.h"
#include "animals/Wolf.h"
#include "animals/Sheep.h"
#include "animals/Fox.h"
#include "animals/Turtle.h"
#include "animals/Antilope.h"
#include "animals/Human.h"
#include "util.h"


class World {
private:
    bool worldPaused { false };
    PLAYER_ACTIONS human_action;

    const Rect worldArea;
    std::vector<Organism*> organisms;
    std::vector<Organism*> children;

    int turnsNum {};

    void InitOrganisms();

    void CreateOrganism(Organism *o);
    void CreateOrganism(ORGANISM_E o_t);
    void CreateOrganism(ORGANISM_E o_t, Point p);

    void OrganismsSortAndCleanUp();

    bool isPlaceFree(Point p);

    friend class Renderer;
public:
    WorldListener WListener {};

    World(const Rect &worldArea);
    ~World();

    void MakeTurn();
    bool isPaused() { return worldPaused; };

    bool WithinWorldArea(Point pos) const;
    int getTurnsNum() { return turnsNum; };

    const std::vector<Organism*> *getOrganisms() { return &organisms; };
    int getOrganismsNum() { return organisms.size(); };

    void setHumanAction(PLAYER_ACTIONS a) { human_action = a; };
    PLAYER_ACTIONS getHumanAction() { return human_action; };

    Point FindPosNearParents(Point p1, Point p2);
    void CreateOffspring(Organism &p1, Organism &p2);
};

#include "Renderer.h"

#endif //PR1_WORLD_H