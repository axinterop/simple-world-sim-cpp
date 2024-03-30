#include <iostream>
#include "Renderer.h"

Renderer::Renderer() {
    initializeRenderer();
    newWins();
}

Renderer::~Renderer() {
    delWins();
    endwin();
}


void Renderer::draw(const std::string &t, const Point &pos) { this->draw(t, pos, WIN::S); }

void Renderer::draw(const std::string &t, const Point &pos, chtype a) {
    this->draw(t, pos, a, WIN::S);
}

void Renderer::draw(const std::string &t, const Point &pos, WIN w) {
    mvwprintw(WINS[w], pos.y, pos.x, "%s", t.c_str());
}

void Renderer::draw(const std::string &t, const Point &pos, chtype a, WIN w) {
    wattron(WINS[w], a);
    this->draw(t, pos, w);
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

void Renderer::refresh() {
    refresh(WIN::S);
}

void Renderer::refresh(WIN w) {
    wrefresh(WINS[w]);
}

void Renderer::refreshAll() {
    for (int i = 0; i < w_n; i++) {
        WIN w = static_cast<WIN>(i);
        refresh(w);
    }
}

WINDOW const *Renderer::getWin(WIN w) const {
    return WINS[w];
}

void Renderer::cleanAll() {
    for (int i = 0; i < w_n; i++) {
        WIN w = static_cast<WIN>(i);
        wclear(WINS[w]);
    }
}

void Renderer::boxWin(WIN w) {
    box(WINS[w], 0, 0);
}


void initializeRenderer() {
    initscr();            /* Start curses mode 		*/
//    timeout(0);             /* Non-breaking input mode */
    raw();                /* Line buffering disabled	*/
    keypad(stdscr, TRUE);        /* We get F1, F2 etc..		*/
    noecho();            /* Don't echo() while we do getch */
    curs_set(0);        /* Sets the cursor state is set to invisible */
}