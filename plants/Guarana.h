#ifndef PR1_GUARANA_H
#define PR1_GUARANA_H


#include "../Plant.h"


class Guarana: public Plant {
public:
    Guarana() : Plant() {
        type = GUARANA;
    }
    Guarana(int s, int i, int a, Point p) : Plant(s, i, a, p) {
        type = GUARANA;
    }

    std::string className() { return "Guarana"; };
};


#endif //PR1_GUARANA_H
