#ifndef PR1_SIMULATION_H
#define PR1_SIMULATION_H

#include "Renderer.h"
#include <chrono>

class Simulation {
public:
    Simulation();
    ~Simulation();
    void runSimulation();
    Renderer *R;
private:
    void updateInput();
    void updateLogic();
    void renderSim();

    bool m_endSim { false };
    Rect m_simArea;
};


#endif
