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
#include "plants/Grass.h"
#include "plants/Sonchus.h"
#include "plants/Guarana.h"
#include "plants/Belladonna.h"
#include "plants/H_Sosnowskyi.h"
#include "util.h"


class World {
private:
    bool worldPaused { false };
    PLAYER_ACTION human_action;
    int human_power_turns = 0;
    int human_power_CD = 0;

    const Rect worldArea;
    std::vector<Organism*> organisms;
    std::vector<PlantChunk *> plantChunks;

    int turnsNum {};

    void InitOrganisms();

    Organism& CreateOrganism(Organism *o);
    Organism& CreateOrganism(ORGANISM_E o_t);
    Organism& CreateOrganism(ORGANISM_E o_t, Point p);

    void CreatePlantChunk(ORGANISM_E o_t);
    void CreatePlantChunk(ORGANISM_E o_t, Point pos);


    void ReactOnCollision(Organism &this_o, Organism &other_o);

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
    Point getRandomPosNearby(Point pos, int k = 1);
    Point getFreePosNearby(Point pos);
    int getTurnsNum() { return turnsNum; };

    const std::vector<Organism*> *getOrganisms() { return &organisms; };
    int getOrganismsNum() { return organisms.size(); };

    bool setHumanAction(PLAYER_ACTION a);
    int getHumanPowerTurns() { return human_power_turns; };
    int getHumanPowerCD() { return human_power_CD; };
    PLAYER_ACTION getHumanAction() { return human_action; };

    Point FindPosNearParents(Point p1, Point p2);
    void CreateOffspring(Organism &p1, Organism &p2);
    void CreatePlantOffspring(Organism &p1);

};

#include "Renderer.h"

#endif //PR1_WORLD_H