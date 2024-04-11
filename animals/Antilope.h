#ifndef PR1_ANTILOPE_H
#define PR1_ANTILOPE_H


#include "../Animal.h"

class Antilope: public Animal {
public:
    using Animal::Animal;
    Antilope() : Animal() {
        type = ANTILOPE;
    }
    Antilope(int s, int i, int a, Point p) : Animal(s, i, a, p) {
        type = ANTILOPE;
    }

    std::string className() { return "Antilope"; };
};



#endif //PR1_ANTILOPE_H
