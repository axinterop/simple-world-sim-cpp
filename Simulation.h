#ifndef PR1_SIMULATION_H
#define PR1_SIMULATION_H

#include "Renderer.h"
#include "World.h"


class Simulation {
public:
    Simulation();
    ~Simulation();
    void RunSimulation();
    Renderer *R;
    World *W;
private:
    void UpdateInput();
    void UpdateLogic();
    void RenderSim();

    bool m_endSim { false };
};


#endif
