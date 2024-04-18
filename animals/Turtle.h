#ifndef PR1_TURTLE_H
#define PR1_TURTLE_H

#include "../Animal.h"

class Turtle: public Animal {
public:
    using Animal::Animal;
    Turtle() : Animal() {
        type = TURTLE;
    }
    Turtle(int s, int i, int a, Point p) : Animal(s, i, a, p) {
        type = TURTLE;
    }

    void Action(World &W) final;

    std::string className() { return "Turtle"; };
};



#endif //PR1_TURTLE_H
