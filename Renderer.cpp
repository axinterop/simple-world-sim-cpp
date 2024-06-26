#include "Renderer.h"

Renderer::Renderer(Rect sim_area) {
    InitializeRenderer();
    newWins(sim_area);
}

Renderer::~Renderer() {
    delWins();
    endwin();
}

void Renderer::Draw(const std::string &t, const Point &pos) {
    this->Draw(t, pos, WIN::S);
}

void Renderer::Draw(const std::string &t, const Point &pos, chtype a) {
    this->Draw(t, pos, a, WIN::S);
}

void Renderer::Draw(const std::string &t, const Point &pos, WIN w) {
    mvwprintw(WINS[w], pos.y, pos.x, "%s", t.c_str());
}

void Renderer::Draw(const std::string &t, const Point &pos, chtype a, WIN w) {
    wattron(WINS[w], a);
    this->Draw(t, pos, w);
    wattroff(WINS[w], a);
}

void Renderer::newWins(Rect sim_area) {
    int max_w = (int) COLS - 60;
    int max_h = (int) LINES - 8;
    sim_area.w = std::max(sim_area.w, 50);
    sim_area.h = std::max(sim_area.h, 5);

    sim_area.w = std::min(sim_area.w, max_w);
    sim_area.h = std::min(sim_area.h, max_h);

    Rect s =  sim_area;
    Rect i = {s.x, (s.y + s.h), s.w,
              LINES - s.h}; // TODO: Depends on sim win
    Rect l = {(s.x + s.w), s.y, COLS - s.w,
              LINES}; // TODO: Depends on sim win
    Rect r[] = {s, i, l};

    for (int j = 0; j < w_n; j++) {
        WIN w = static_cast<WIN>(j);
        newWin(w, r[j]);
    }
}

void Renderer::newWin(WIN w, Rect &r) { WINS[w] = newwin(r.h, r.w, r.y, r.x); }

void Renderer::delWins() {
    for (int i = 0; i < w_n; i++) {
        WIN w = static_cast<WIN>(i);
        delWin(w);
    }
}

void Renderer::delWin(WIN w) { delwin(WINS[w]); }

void Renderer::Refresh() { Refresh(WIN::S); }

void Renderer::Refresh(WIN w) { wrefresh(WINS[w]); }

void Renderer::RefreshAll() {
    for (int i = 0; i < w_n; i++) {
        WIN w = static_cast<WIN>(i);
        Refresh(w);
    }
}

WINDOW const *Renderer::getWin(WIN w) const { return WINS[w]; }

void Renderer::Clean(WIN w) { wclear(WINS[w]); }

void Renderer::CleanAll() {
    for (int i = 0; i < w_n; i++) {
        WIN w = static_cast<WIN>(i);
        wclear(WINS[w]);
    }
}

void Renderer::BoxWin(WIN w) { box(WINS[w], 0, 0); }

void Renderer::EmptyWin(WIN w) {
    Clean(w);
    BoxWin(w);
}

void Renderer::DrawWorld(World *W) {
    for (auto p: W->organisms) {
        if (p->getInitiative() != 0)
            continue;
        Draw(p->className().substr(0, 1), p->getPos(),
             COLOR_PAIR(p->getType()));
    }

    for (auto a: W->organisms) {
        if (a->getInitiative() == 0)
            continue;
        if (a->isDead())
            continue;
        if (a->getType() == HUMAN)
            if (W->isPaused())
                Draw("H", a->getPos(), A_BOLD | A_BLINK | A_UNDERLINE);
            else
                Draw("H", a->getPos());

        else {
            Draw(a->className().substr(0, 1), a->getPos(),
                 COLOR_PAIR(a->getType()));
        }
    }

}

void Renderer::ShowListenersOutput(World *W) {
    // TODO: Fix so the text moves up instead of cleaning and going from beginning
    if (ly == getmaxy(WINS[WIN::L]) - 1) {
        EmptyWin(WIN::L);
        ly = 1;
    }

    if (!W->WListener.events.empty()) {
        Draw("- Turn " + std::to_string(W->getTurnsNum()) + ":", {lx, ly++},
             WIN::L);
        for (; !W->WListener.events.empty(); W->WListener.events.pop()) {
            if (ly == getmaxy(WINS[WIN::L]) - 1) {
                EmptyWin(WIN::L);
                ly = 1;
            }
            Draw(W->WListener.events.front().details, {lx, ly++}, WIN::L);
        }
    }
}

void Renderer::ShowPlayerInformation(World *W) {
    if (W->isPaused()) {
        int px = getmaxx(WINS[I]) - 25;
        Draw("Player's turn now!", {px, 1}, A_REVERSE, WIN::I);

        if (W->getHumanPowerTurns() != 0) {
            Draw("Power is active for " + std::to_string(W->getHumanPowerTurns()) + " turns", {px, 2}, WIN::I);
        } else {
            if (W->getHumanPowerCD() != 0) {
                Draw("Power is on cooldown for " + std::to_string(W->getHumanPowerCD()) + " turns", {px, 2}, WIN::I);
            } else
                Draw("Power is ready to use", {px, 2}, A_BOLD, WIN::I);
        }
    }
}

void InitializeRenderer() {
    initscr(); /* Start curses mode 		*/
    //    timeout(0);             /* Non-breaking input mode */
    raw();     /* Line buffering disabled	*/
    keypad(stdscr, TRUE); /* We get F1, F2 etc..		*/
    noecho();             /* Don't echo() while we do getch */
    curs_set(0);          /* Sets the cursor state is set to invisible */
    if (has_colors() == FALSE)
        printf("[WARNING]: Terminal does not support colors\n");
    else
        start_color();

    init_pair(ORGANISM_E::WOLF, COLOR_BLACK, COLOR_RED);
    init_pair(ORGANISM_E::SHEEP, COLOR_BLACK, COLOR_WHITE);
    init_pair(ORGANISM_E::FOX, COLOR_BLACK, COLOR_YELLOW);
    init_pair(ORGANISM_E::TURTLE, COLOR_CYAN, COLOR_GREEN);
    init_pair(ORGANISM_E::ANTILOPE, COLOR_RED, COLOR_YELLOW);

    init_pair(ORGANISM_E::GRASS, COLOR_GREEN, COLOR_BLACK);
    init_pair(ORGANISM_E::SONCHUS, COLOR_YELLOW, COLOR_BLACK);
    init_pair(ORGANISM_E::GUARANA, COLOR_CYAN, COLOR_BLACK);
    init_pair(ORGANISM_E::BELLADONNA, COLOR_BLUE, COLOR_BLACK);
    init_pair(ORGANISM_E::H_SOSNOWSKYI, COLOR_MAGENTA, COLOR_BLACK);
}
