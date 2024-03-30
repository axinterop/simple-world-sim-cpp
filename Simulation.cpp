
#include "Simulation.h"

Simulation::Simulation() {
    R = new Renderer();
}

Simulation::~Simulation() {
    delete R;
}

void Simulation::RunSimulation() {
    auto prevFT = std::chrono::steady_clock::now();
    auto curFT = std::chrono::steady_clock::now();

    while (!m_endSim) {
        curFT = std::chrono::steady_clock::now();
        int frameDurMS = std::chrono::duration_cast<std::chrono::milliseconds>(curFT - prevFT).count();

        if (frameDurMS > this->frameDurCap) {
            prevFT = curFT;
            UpdateInput();
            UpdateLogic();
            RenderSim();
        }

    }
}

void Simulation::UpdateInput() {
    int ch;
    ch = getch();
    if (ch == 'e')
        m_endSim = true;
    if (ch == KEY_F(2))
        if (frameDurCap > 20)
            frameDurCap -= 40;
    if (ch == KEY_F(1))
        if (frameDurCap < 240)
            frameDurCap += 40;
    if (ch == KEY_F(3))
        frameDurCap = 60;

}

void Simulation::UpdateLogic() {
    x += 1;
    if (x >= getmaxx(R->GetWin(WIN::S)) - 1)
        x = 0;
}

void Simulation::RenderSim() {
    R->CleanAll();
    R->Box(WIN::S);
    R->Box(WIN::I);
    R->Draw("Hi", {(int) x, 1});
    R->RefreshAll();
}
