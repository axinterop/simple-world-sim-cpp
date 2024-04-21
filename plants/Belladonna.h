#ifndef PR1_BELLADONNA_H
#define PR1_BELLADONNA_H

#include "../Plant.h"


class Belladonna: public Plant {
public:
    Belladonna() : Plant() {
        type = BELLADONNA;
    }
    Belladonna(int s, int i, int a, Point p) : Plant(s, i, a, p) {
        type = BELLADONNA;
    }

    std::string className() { return "Belladonna"; };
};


#endif //PR1_BELLADONNA_H
