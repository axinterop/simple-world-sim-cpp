#ifndef PR1_HUMAN_H
#define PR1_HUMAN_H

#include "../Animal.h"
#include "../World.h"

class Human : public Animal {
  private:
    PLAYER_ACTION action;
    bool power_is_active = false;
    int power_turns = 0;
    int power_cool_down = 0;
  public:
    Human() : Animal() { type = HUMAN; }
    Human(int s, int i, int a, Point p) : Animal(s, i, a, p) { type = HUMAN; }

    // Fix this
   void Action(World &W) final;

    std::string className() { return "Human"; };

    void AfterTurn(World &W);
    void PowerActivate();
    void PowerDeactivate();
    bool isPowerful() { return power_is_active; }
    int getPowerTurns() { return power_turns; }
    int getPowerCD() { return power_cool_down; }
};

#endif // PR1_HUMAN_H
