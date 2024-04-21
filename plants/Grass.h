#ifndef PR1_GRASS_H
#define PR1_GRASS_H



#include "../Plant.h"


class Grass: public Plant {
public:
    Grass() : Plant() {
        type = GRASS;
    }
    Grass(int s, int i, int a, Point p) : Plant(s, i, a, p) {
        type = GRASS;
    }

    std::string className() { return "Grass"; };
};




#endif //PR1_GRASS_H
