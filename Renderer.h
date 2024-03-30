#ifndef PR1_RENDERER_H
#define PR1_RENDERER_H

#include <string>
#include <vector>
#include "ncurses.h"

struct Point {
    int x;
    int y;
};

struct Rect {
    int x;
    int y;
    int w;
    int h;
};

typedef enum {
    S, // Main
    I, // Info
    L // Log
} WIN;

class Renderer {
public:
    Renderer();
    ~Renderer();

    void Draw(const std::string& t, const Point &pos);
    void Draw(const std::string& t, const Point &pos, WIN w);

    void Refresh();
    void Refresh(WIN w);
    void RefreshAll();
    void CleanAll();
    void Box(WIN w);
    WINDOW const *GetWin(WIN w) const;
private:
    WINDOW *WINS[3];
    const int w_n = 3;
    void NewWins();
    void NewWin(WIN w, Rect &r);
    void DelWins();
    void DelWin(WIN w);

};

void InitializeRenderer();

#endif
