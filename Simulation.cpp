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
        // Allow user to see the interface and the world before the first turn
        if (first_run) {
            RenderSim();
            first_run = false;
            continue;
        }
        UpdateLogic();
        RenderSim();
    }
}

void Simulation::UpdateInput() {
    int ch;
    ch = getch();
    if (ch == 'e') {
        m_endSim = true;
        return;
    }

    if (W->isPaused()) {
        W->setHumanAction(NO_ACTION);
        if (ch == KEY_LEFT)
            W->setHumanAction(GO_LEFT);
        else if (ch == KEY_RIGHT)
            W->setHumanAction(GO_RIGHT);
        else if (ch == KEY_UP)
            W->setHumanAction(GO_UP);
        else if (ch == KEY_DOWN)
            W->setHumanAction(GO_DOWN);
        else if (ch == '1')
            W->setHumanAction(POWER);
    }
}

void Simulation::UpdateLogic() {
    W->MakeTurn();
    // If World is paused, it doesn't matter,
    // return from this function and RenderSim() normally
}

void Simulation::RenderSim() {
    R->EmptyWin(WIN::S);
    R->EmptyWin(WIN::I);
    R->BoxWin(WIN::L);

    // Draw worlds
    R->DrawWorld(W);


    // Info string
    R->ShowPlayerInformation(W);

    R->Draw("Turns passed: " + std::to_string(W->getTurnsNum()), {1, 1}, WIN::I);
    R->Draw("Organisms alive: " + std::to_string(W->getOrganismsNum()), {1, 2}, WIN::I);

    R->Draw("Any key for Next Turn", {1, 4}, WIN::I);
    R->Draw("'E' to Exit", {1, 5}, WIN::I);

    // Log string
    R->ShowListenersOutput(W);

    R->RefreshAll();
}
