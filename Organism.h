#ifndef PR1_ORGANISM_H
#define PR1_ORGANISM_H

#include "util.h"

class World;

class Organism {
protected:
    int id;
    int strength;
    int initiative;
    int age;
    Point pos;
    static int free_id;
public:
    Organism() :
            id(-1), strength(-1), initiative(-1), age(-1), pos({-1, -1}) {};

    Organism(int s, int i, int a, Point p) :
            id(free_id++), strength(s), initiative(i), age(a), pos(p) { };

    ~Organism() = default;

    virtual void Action(World &W) = 0;

    virtual void Collision(World &W) = 0;

    int getId() { return id; };

    int getStrength() { return strength; };

    int getInitiative() { return initiative; };

    int getAge() { return age; };

    void setAge(int value) { age = value; };

    Point getPos() { return pos; };
};

#endif //PR1_ORGANISM_H
