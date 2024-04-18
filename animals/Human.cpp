#include "Human.h"

void Human::Action(World &W) {
    PLAYER_ACTION a = W.getHumanAction();
    // Movement
    if (a != NO_ACTION && a != POWER) {
        Point potentialPos = {pos.x, pos.y};
        if (a == GO_RIGHT) {
            potentialPos.x += 1;
        } else if (a == GO_LEFT) {
            potentialPos.x -= 1;
        } else if (a == GO_DOWN) {
            potentialPos.y += 1;
        } else if (a == GO_UP) {
            potentialPos.y -= 1;
        }
        if (W.WithinWorldArea(potentialPos))
            setPos(potentialPos);
    } else if (a == POWER) {
        // Power
    }
}