
#include "Simulation.h"

Simulation::Simulation() {
    R = new Renderer();
    const WINDOW *t = R->GetWin(WIN::S);
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
    if (ch == KEY_F(1))
        if (frameDurCap < 360)
            frameDurCap += 40;
    if (ch == KEY_F(2))
        if (frameDurCap > 20)
            frameDurCap -= 40;
    if (ch == KEY_F(3))
        frameDurCap = 60;

}

void Simulation::UpdateLogic() {
    // TODO: TEMP
    x += 1;
    y += 1;
    if (x + 1 >= m_simArea.x + m_simArea.w - 1)
        x = m_simArea.x;
    if (y >= m_simArea.y + m_simArea.h - 1)
        y = m_simArea.y;

}

void Simulation::RenderSim() {
    R->CleanAll();

    // Boxes
    R->Box(WIN::S);
    R->Box(WIN::I);
    R->Box(WIN::L);
    // Test string
    R->Draw("  ", {(int) x, (int) y}, A_REVERSE);
    // Info string
    std::string t = std::to_string(frameDurCap);
    R->Draw("F1 - slow down, F2 - speed up, F3 - reset (60 ms)", {1, 1}, WIN::I);
    R->Draw("'E' to Exit", {1,2}, WIN::I);
    R->Draw("Time between frames: " + t + " ms", {60, 1}, WIN::I);

    R->RefreshAll();
}
