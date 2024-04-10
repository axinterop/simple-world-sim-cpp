#include "Renderer.h"

Renderer::Renderer() {
    InitializeRenderer();
    newWins();
}

Renderer::~Renderer() {
    delWins();
    endwin();
}


void Renderer::Draw(const std::string &t, const Point &pos) { this->Draw(t, pos, WIN::S); }

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

void Renderer::newWins() {
    float ratio = 0.3;
    Rect s = {0, 0, (int) (COLS * (1 - ratio)), LINES - 7}; // TODO: Has to be resizable
    Rect i = {s.x, (s.y + s.h), (int) (COLS * (1 - ratio)), LINES - s.h}; // TODO: Depends on sim win
    Rect l = {(s.x + s.w), s.y, (int) (COLS * ratio), LINES}; // TODO: Depends on sim win
    Rect r[] = {s, i, l};

    for (int j = 0; j < w_n; j++) {
        WIN w = static_cast<WIN>(j);
        newWin(w, r[j]);
    }
}

void Renderer::newWin(WIN w, Rect &r) {
    WINS[w] = newwin(r.h, r.w, r.y, r.x);
}

void Renderer::delWins() {
    for (int i = 0; i < w_n; i++) {
        WIN w = static_cast<WIN>(i);
        delWin(w);
    }
}

void Renderer::delWin(WIN w) {
    delwin(WINS[w]);
}

void Renderer::Refresh() {
    Refresh(WIN::S);
}

void Renderer::Refresh(WIN w) {
    wrefresh(WINS[w]);
}

void Renderer::RefreshAll() {
    for (int i = 0; i < w_n; i++) {
        WIN w = static_cast<WIN>(i);
        Refresh(w);
    }
}

WINDOW const *Renderer::getWin(WIN w) const {
    return WINS[w];
}

void Renderer::Clean(WIN w) {
    wclear(WINS[w]);
}

void Renderer::CleanAll() {
    for (int i = 0; i < w_n; i++) {
        WIN w = static_cast<WIN>(i);
        wclear(WINS[w]);
    }
}

void Renderer::BoxWin(WIN w) {
    box(WINS[w], 0, 0);
}

void Renderer::EmptyWin(WIN w) {
    Clean(w);
    BoxWin(w);
}

void Renderer::DrawWorld(World *W) {
    for (auto organism: W->organisms) {
        if (organism->isDead())
            continue;
        Draw(to_string(organism->getId()), organism->getPos(), COLOR_PAIR(ORGANISM_COLOR::WOLF));
    }
}

void Renderer::ShowListenersOutput(World *W) {
    // TODO: Fix so the text moves up instead of cleaning and going from beginning
    if (ly == getmaxy(WINS[WIN::L]) - 2) {
        EmptyWin(WIN::L);
        ly = 0;
    }
    Draw("Turn " + to_string(W->getTurnsNum()) + ":", {lx, ly + 1}, WIN::L);
    ly++;
    for (; !W->WListener.events.empty();  W->WListener.events.pop()) {
        if (ly == getmaxy(WINS[WIN::L]) - 2) {
            EmptyWin(WIN::L);
            ly = 0;
        }
        Draw(W->WListener.events.front().details, {lx, ly + 1},WIN::L);
        ly++;
    }
}


void InitializeRenderer() {
    initscr();            /* Start curses mode 		*/
//    timeout(0);             /* Non-breaking input mode */
    raw();                /* Line buffering disabled	*/
    keypad(stdscr, TRUE);        /* We get F1, F2 etc..		*/
    noecho();            /* Don't echo() while we do getch */
    curs_set(0);        /* Sets the cursor state is set to invisible */
    if(has_colors() == FALSE)
        printf("[WARNING]: Terminal does not support colors\n");
    else
        start_color();

    init_pair(ORGANISM_COLOR::WOLF, COLOR_BLACK, COLOR_RED);
    init_pair(ORGANISM_COLOR::SHEEP, COLOR_BLACK, COLOR_WHITE);
    init_pair(ORGANISM_COLOR::TURTLE, COLOR_CYAN, COLOR_GREEN);
    init_pair(ORGANISM_COLOR::ANTILOPE, COLOR_RED, COLOR_YELLOW);

    init_pair(ORGANISM_COLOR::GRASS, COLOR_GREEN, COLOR_BLACK);
    init_pair(ORGANISM_COLOR::SONCHUS, COLOR_YELLOW, COLOR_BLACK);
    init_pair(ORGANISM_COLOR::GUARANA, COLOR_CYAN, COLOR_BLACK);
    init_pair(ORGANISM_COLOR::BELLADONNA, COLOR_BLUE, COLOR_BLACK);
    init_pair(ORGANISM_COLOR::H_SOSNOWSKYI, COLOR_MAGENTA, COLOR_BLACK);
}