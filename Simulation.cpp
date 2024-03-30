
#include "Simulation.h"

Simulation::Simulation() {
    R = new Renderer();
    const WINDOW *t = R->getWin(WIN::S);
    Rect w_area;
    w_area.x = getbegx(t) + 1;
    w_area.y = getbegy(t) + 1;
    w_area.w = getmaxx(t) - 1;
    w_area.h = getmaxy(t) - 1;

    W = new World(R, w_area);
}

Simulation::~Simulation() {
    delete W;
    delete R;
}

void Simulation::runSimulation() {
    while (!m_endSim) {
        updateInput();
        updateLogic();
        renderSim();
    }
}

void Simulation::updateInput() {
    int ch;
    ch = getch();
    if (ch == 'e')
        m_endSim = true;
}

void Simulation::updateLogic() {
    W->makeTurn();
}

void Simulation::renderSim() {
    R->cleanAll();

    // Draw world
    W->drawWorld();

    // Box windows
    R->boxWin(WIN::S);
    R->boxWin(WIN::I);
    R->boxWin(WIN::L);

    // Info string
    R->draw("'Any key' for Next Turn", {1, 1}, WIN::I);
    R->draw("'E' to Exit", {1, 2}, WIN::I);

    R->refreshAll();
}
