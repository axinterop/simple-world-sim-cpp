#ifndef PR1_RENDERER_H
#define PR1_RENDERER_H

#include <string>
#include <vector>
#include "ncurses.h"

#include "World.h"
#include "WorldListener.h"

#include "util.h"

typedef enum {
    S, // Main
    I, // Info
    L // Log
} WIN;

class Renderer {
private:
    WINDOW *WINS[3];
    const int w_n = 3;
    void newWins();
    void newWin(WIN w, Rect &r);
    void delWins();
    void delWin(WIN w);
public:
    Renderer();
    ~Renderer();

    void Draw(const std::string& t, const Point &pos);
    void Draw(const std::string& t, const Point &pos, chtype a);
    void Draw(const std::string& t, const Point &pos, WIN w);
    void Draw(const std::string& t, const Point &pos, chtype a, WIN w);

    void DrawWorld(World *W);
    void ShowListenersOutput(World *W);

    void Refresh();
    void Refresh(WIN w);
    void RefreshAll();
    void CleanAll();
    void BoxWin(WIN w);
    WINDOW const *getWin(WIN w) const;
};

void InitializeRenderer();

#endif
