#ifndef PR1_RENDERER_H
#define PR1_RENDERER_H

#include <string>
#include <vector>
#include "ncurses.h"

#include "util.h"

typedef enum {
    S, // Main
    I, // Info
    L // Log
} WIN;

class Renderer {
public:
    Renderer();
    ~Renderer();

    void draw(const std::string& t, const Point &pos);
    void draw(const std::string& t, const Point &pos, chtype a);
    void draw(const std::string& t, const Point &pos, WIN w);
    void draw(const std::string& t, const Point &pos, chtype a, WIN w);

    void refresh();
    void refresh(WIN w);
    void refreshAll();
    void cleanAll();
    void boxWin(WIN w);
    WINDOW const *getWin(WIN w) const;
private:
    WINDOW *WINS[3];
    const int w_n = 3;
    void newWins();
    void newWin(WIN w, Rect &r);
    void delWins();
    void delWin(WIN w);

};

void initializeRenderer();

#endif
