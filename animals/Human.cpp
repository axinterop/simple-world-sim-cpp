#include "Human.h"

void Human::Action(World &W) {
    PLAYER_ACTION a = W.getHumanAction();
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
        if (power_cool_down == 0) {
            PowerActivate();
            W.WListener.RecordEvent("Power activated: invincibility for 5 turns");
        }
    }
}

void Human::AfterTurn(World &W) {
    getOlder();
    if (power_is_active) {
        if (power_turns == 0) {
            PowerDeactivate();
            W.WListener.RecordEvent("Power deactivated.");
        }
        else {
            power_turns--;
            power_cool_down = 5;
        }
    } else if (!power_is_active) {
        if (power_cool_down != 0)
            power_cool_down--;
    }
}

void Human::PowerActivate() {
    power_is_active = true;
    power_turns = 6;
    power_cool_down = 0;
}

void Human::PowerDeactivate() {
    power_is_active = false;
    power_turns = 0;
    power_cool_down = 5;
}
