#ifndef PR1_WOLF_H
#define PR1_WOLF_H

#include "../Animal.h"


class Wolf: public Animal {
public:
    Wolf() : Animal() {
        type = WOLF;
    }
    Wolf(int s, int i, int a, Point p) : Animal(s, i, a, p) {
        type = WOLF;
    }

    std::string className() { return "Wolf"; };
};


#endif //PR1_WOLF_H
