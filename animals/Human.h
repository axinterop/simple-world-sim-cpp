#ifndef PR1_HUMAN_H
#define PR1_HUMAN_H


#include "../Animal.h"

class Human: public Animal {
public:
    using Animal::Animal;
    Human() : Animal() {
        type = HUMAN;
    }
    Human(int s, int i, int a, Point p) : Animal(s, i, a, p) {
        type = HUMAN;
    }

    void Action();

    std::string className() { return "Human"; };
};



#endif //PR1_HUMAN_H
