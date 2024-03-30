#ifndef PR1_SIMULATION_H
#define PR1_SIMULATION_H

#include "Renderer.h"
#include "World.h"

class Simulation {
public:
    Simulation();
    ~Simulation();
    void runSimulation();
    Renderer *R;
    World *W;
private:
    void updateInput();
    void updateLogic();
    void renderSim();

    bool m_endSim { false };
};


#endif
