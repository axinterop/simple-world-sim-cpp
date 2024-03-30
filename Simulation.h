#ifndef PR1_SIMULATION_H
#define PR1_SIMULATION_H

#include "Renderer.h"
#include <chrono>

class Simulation {
public:
    Simulation();
    ~Simulation();
    void RunSimulation();
    Renderer *R;
    float x = 1.0f;
private:
    void UpdateInput();
    void UpdateLogic();
    void RenderSim();

    bool m_endSim { false };
    Rect m_simArea;
    int frameDurCap { 60 }; // TODO: Must be changeable
};


#endif
