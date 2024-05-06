#ifndef PR1_UTIL_H
#define PR1_UTIL_H

#include <vector>
#include <algorithm>
#include <typeinfo>

struct Point;
struct Rect;

struct Rect {
    int x;
    int y;
    int w;
    int h;
};

struct Point {
    int x;
    int y;

    bool operator==(const Point &other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Point &other) const {
        return !(*this == other);
    }

    Point operator+(const Point &other) const {
        return Point{x + other.x, y + other.y};
    }

    Point operator-(const Point &other) const {
        return Point{x - other.x, y - other.y};
    }

    Rect createRect(Point &other) {
        Rect r {};
        r.x = std::min(this->x, other.x);
        r.y = std::min(this->y, other.y);
        r.w = r.x + std::max(this->x, other.x);
        r.h = r.y + std::max(this->y, other.y);
        return r;
    }
};

typedef enum {
    // Animals
    WOLF = 1,
    SHEEP,
    FOX,
    TURTLE,
    ANTILOPE,
    // Plants
    GRASS,
    SONCHUS,
    GUARANA,
    BELLADONNA,
    H_SOSNOWSKYI,
    // Player
    HUMAN
} ORGANISM_E;

typedef enum {
    GO_LEFT,
    GO_RIGHT,
    GO_UP,
    GO_DOWN,
    POWER,
    NO_ACTION,
} PLAYER_ACTION;

typedef enum {
    MOVE,
    NO_MOVE,
} ORGANISM_ACTION;

typedef enum {
    BREED,
    KILL,
    DIE,
    STAY,
    BLOCK_ATTACK,
    ESCAPE,
    AVOID_DEATH,
    BOOST_EATING,
    DIE_EATING,
    UNDEFINED,
} COLLISION_STATUS;

#endif //PR1_UTIL_H
