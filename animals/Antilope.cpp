#include "Antilope.h"

void Antilope::Action(World &W) {
    setPos(W.getRandomPosNearby(pos, 2));
}
