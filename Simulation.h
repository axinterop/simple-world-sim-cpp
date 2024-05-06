#ifndef PR1_SIMULATION_H
#define PR1_SIMULATION_H

#include "Renderer.h"
#include "World.h"


class Simulation {
public:
    Simulation(int w, int h);
    ~Simulation();
    void RunSimulation();
    Renderer *R;
    World *W;
    bool first_run { true };
private:
    void UpdateInput();
    void UpdateLogic();
    void RenderSim();

    bool m_endSim { false };
};


#endif
