#ifndef PR1_SONCHUS_H
#define PR1_SONCHUS_H

#include "../Plant.h"


class Sonchus: public Plant {
public:
    Sonchus() : Plant() {
        type = SONCHUS;
    }
    Sonchus(int s, int i, int a, Point p) : Plant(s, i, a, p) {
        type = SONCHUS;
    }

    std::string className() { return "Sonchus"; };
};


#endif //PR1_SONCHUS_H
