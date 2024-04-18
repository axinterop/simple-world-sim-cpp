#ifndef PR1_WORLDLISTENER_H
#define PR1_WORLDLISTENER_H

#include <string>
#include <queue>
#include "Organism.h"
#include "util.h"

struct WorldEvent {
//    string title;
//    int priority; // May be useful
    std::string details;
};


class WorldListener {
private:
    std::queue<WorldEvent> events;

    friend class Renderer;
public:
    WorldListener() { events = {}; };
    ~WorldListener() = default;

    void RecordEvent(std::string d);
    void RecordEvent(const WorldEvent& we);

    void RecordCollision(COLLISION_STATUS c_s, Organism &this_o, Organism &other_o);
};


#endif //PR1_WORLDLISTENER_H
