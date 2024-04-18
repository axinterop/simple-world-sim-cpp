#include "Fox.h"

void Fox::Action(World &W) {
    Point potentialPos {};
    potentialPos = W.getRandomPosNearby(pos);
    bool enemy_avoided = false;
    for (auto other_o: *W.getOrganisms()) {
        while (potentialPos == other_o->getPos() && strength < other_o->getStrength()) {
            potentialPos = W.getRandomPosNearby(pos);
            enemy_avoided = true;
        }
    }
    if (enemy_avoided)
        W.WListener.RecordEvent(classInfo() + " avoided animal(s) of greater strength");
    setPos(potentialPos);
}
