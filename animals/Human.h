#ifndef PR1_HUMAN_H
#define PR1_HUMAN_H

#include "../Animal.h"
#include "../World.h"

class Human : public Animal {
  private:
    PLAYER_ACTIONS action;

  public:
    Human() : Animal() { type = HUMAN; }
    Human(int s, int i, int a, Point p) : Animal(s, i, a, p) { type = HUMAN; }

    // Fix this
   void Action(World &W) final;

    std::string className() { return "Human"; };
};

#endif // PR1_HUMAN_H
