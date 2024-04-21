#ifndef PR1_ORGANISM_H
#define PR1_ORGANISM_H

#include "util.h"
#include <string>


class World;

class Organism {
protected:
    int id;
    ORGANISM_E type;
    int strength;
    int initiative;
    int age;
    Point prevPos;
    Point pos;
    static int free_id;
    int breedPause = 0;
    int maxLifeTime = -1;
    void randLifeTime() { maxLifeTime = 100 + rand() % 1000; }
    bool has_free_pos_nearby { true };
public:
    Organism() :
            id(-1), strength(-1), initiative(-1), age(-1), pos({-1, -1}) { randLifeTime(); };
    Organism(int s, int i, int a, Point p) :
            id(free_id++), strength(s), initiative(i), age(a), pos(p) { randLifeTime(); };
    ~Organism() = default;
    int getId() { return id; };
    ORGANISM_E getType() { return type; };
    int getStrength() { return strength; };
    int getInitiative() { return initiative; };
    int getAge() { return age; };
    void getOlder() { age++; };

    void Die() { age = -1; };
    bool isDead() { return age == -1; };
    bool canMakeTurn = false;

    void setPos(Point newPos) { prevPos = pos; pos = newPos; };
    Point getPos() { return pos; };

    Point getPrevPos() { return prevPos; };
    void RevertPos();

    void breedDecreasePause() { if (breedPause > 0) breedPause--; };
    void breedSetPause() { if (breedPause == 0) breedPause = 20; };
    void breedSetPause(int value) { breedPause = value; };
    bool canBreed() { return breedPause == 0; };

    virtual void AfterTurn(World &W);

    virtual void Action(World &W) = 0;
    virtual COLLISION_STATUS Collision(Organism &other) = 0;
    virtual std::string className() = 0;
    std::string classInfo() {
        return className() + "[" + std::to_string(id) + "]{" + std::to_string(strength) + "," +
               std::to_string(initiative) + "}";
    };
};

#endif //PR1_ORGANISM_H
