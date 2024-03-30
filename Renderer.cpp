#include <iostream>
#include "Renderer.h"

Renderer::Renderer() {
    InitializeRenderer();
    NewWins();
}

Renderer::~Renderer() {
    DelWins();
    endwin();
}


void Renderer::Draw(const std::string &t, const Point &pos) { this->Draw(t, pos, WIN::S); }

void Renderer::Draw(const std::string &t, const Point &pos, WIN w) {
    mvwprintw(WINS[w], pos.y, pos.x, "%s", t.c_str());
    wrefresh(WINS[w]);
}

void Renderer::NewWins() {
    Rect s = {0, 0, COLS, LINES - 10}; // TODO: Has to be resizable
    Rect i = {
            s.x,
            (s.y + s.h),
            COLS,
            10
    };
    Rect r[] = {s, i};

    for (int j = 0; j < w_n; j++) {
        WIN w = static_cast<WIN>(j);
        NewWin(w, r[j]);
    }
}

void Renderer::NewWin(WIN w, Rect &r) {
    WINS[w] = newwin(r.h, r.w, r.y, r.x);
}

void Renderer::DelWins() {
    for (int i = 0; i < w_n; i++) {
        WIN w = static_cast<WIN>(i);
        DelWin(w);
    }
}

void Renderer::DelWin(WIN w) {
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

WINDOW const *Renderer::GetWin(WIN w) const {
    return WINS[w];
}

void Renderer::CleanAll() {
    for (int i = 0; i < w_n; i++) {
        WIN w = static_cast<WIN>(i);
        wclear(WINS[w]);
    }
}

void Renderer::Box(WIN w) {
    box(WINS[w], 0, 0);
}


void InitializeRenderer() {
    initscr();            /* Start curses mode 		*/
    timeout(0);             /* Non-breaking input mode */
    raw();                /* Line buffering disabled	*/
    keypad(stdscr, TRUE);        /* We get F1, F2 etc..		*/
    noecho();            /* Don't echo() while we do getch */
    curs_set(0);        /* Sets the cursor state is set to invisible */
}