
#include "Simulation.h"

Simulation::Simulation() {
    R = new Renderer();
    const WINDOW *t = R->getWin(WIN::S);
    m_simArea.x = getbegx(t) + 1;
    m_simArea.y = getbegy(t) + 1;
    m_simArea.w = getmaxx(t) - 1;
    m_simArea.h = getmaxy(t) - 1;
    x = m_simArea.x; // TODO: TEMP
    y = m_simArea.y; // TODO: TEMP
}

Simulation::~Simulation() {
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

}

void Simulation::renderSim() {
    R->cleanAll();

    // Win boxes
    R->boxWin(WIN::S);
    R->boxWin(WIN::I);
    R->boxWin(WIN::L);

    // Info string
    R->draw("'Any key' for Next Turn", {1, 1}, WIN::I);
    R->draw("'E' to Exit", {1, 2}, WIN::I);

    R->refreshAll();
}
