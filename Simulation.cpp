#include "Simulation.h"
#include <ncurses.h>

Simulation::Simulation() {
    R = new Renderer();
    const WINDOW *t = R->getWin(WIN::S);
    Rect w_area;
    w_area.x = getbegx(t) + 1;
    w_area.y = getbegy(t) + 1;
    w_area.w = getmaxx(t) - 2; // Exclude the left and right borders
    w_area.h = getmaxy(t) - 2; // Exclude the top and bottom borders

    W = new World(w_area);
}

Simulation::~Simulation() {
    delete W;
    delete R;
}

void Simulation::RunSimulation() {
    // First input is blocked by ncurses, leaving user with blank screen
    mvprintw(0, 0, "Press Any key to start simulation or 'E' to exit...");

    while (!m_endSim) {
        UpdateInput();
        UpdateLogic();
        RenderSim();
    }
}

void Simulation::UpdateInput() {
    int ch;
    ch = getch();
    if (ch == 'e')
        m_endSim = true;
}

void Simulation::UpdateLogic() { W->MakeTurn(); }

void Simulation::RenderSim() {
    R->EmptyWin(WIN::S);
    R->EmptyWin(WIN::I);
    R->BoxWin(WIN::L);

    // Draw worlds
    R->DrawWorld(W);

    // Info string
    R->Draw("Any key for Next Turn", {1, 1}, WIN::I);
    R->Draw("'E' to Exit", {1, 2}, WIN::I);

    // Log string
    R->ShowListenersOutput(W);

    R->RefreshAll();
}
