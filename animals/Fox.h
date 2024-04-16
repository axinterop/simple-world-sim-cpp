#ifndef PR1_FOX_H
#define PR1_FOX_H

#include "../Animal.h"
#include "../World.h"


class Fox: public Animal {
public:
    using Animal::Animal;
    Fox() : Animal() {
        type = FOX;
    }
    Fox(int s, int i, int a, Point p) : Animal(s, i, a, p) {
        type = FOX;
    }

    void Action(World &W) final;

    std::string className() { return "Fox"; };
};



#endif //PR1_FOX_H
