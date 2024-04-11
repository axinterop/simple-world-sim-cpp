#ifndef PR1_SHEEP_H
#define PR1_SHEEP_H

#include "../Animal.h"


class Sheep: public Animal {
public:
    using Animal::Animal;
    Sheep() : Animal() {
        type = SHEEP;
    }
    Sheep(int s, int i, int a, Point p) : Animal(s, i, a, p) {
        type = SHEEP;
    }

    std::string className() { return "Sheep"; };
};



#endif //PR1_SHEEP_H
