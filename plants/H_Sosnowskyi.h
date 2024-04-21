#ifndef PR1_H_SOSNOWSKYI_H
#define PR1_H_SOSNOWSKYI_H

#include "../Plant.h"


class H_Sosnowskyi: public Plant {
public:
    H_Sosnowskyi() : Plant() {
        type = H_SOSNOWSKYI;
    }
    H_Sosnowskyi(int s, int i, int a, Point p) : Plant(s, i, a, p) {
        type = H_SOSNOWSKYI;
    }

    std::string className() { return "H. Sosnowskyi"; };
};


#endif //PR1_H_SOSNOWSKYI_H
