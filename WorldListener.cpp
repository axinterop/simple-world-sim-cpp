#include "WorldListener.h"

#include <utility>

void WorldListener::RecordEvent(std::string d) { events.push({std::move(d)}); }

void WorldListener::RecordEvent(const WorldEvent &we) { events.push(we); }

void WorldListener::RecordCollision(COLLISION_STATUS c_s, Organism &this_o, Organism &other_o) {
    WorldEvent e;
    if (c_s == BREED) {
        e.details = this_o.classInfo() + " bred with another " + other_o.classInfo();
    } else if (c_s == KILL) {
        e.details = this_o.classInfo() + " killed " + other_o.classInfo();
    } else if (c_s == DIE) {
        e.details = this_o.classInfo() + " ran into " + other_o.classInfo() + " and died";
    } else if (c_s == BLOCK_ATTACK) {
        e.details = other_o.classInfo() + " blocked attack from " + this_o.classInfo();
    } else if (c_s == ESCAPE) {
        e.details = other_o.classInfo() + " escaped from " + this_o.classInfo();
    } else if (c_s == UNDEFINED) {
        e.details = "Undefined collision between " + this_o.classInfo() + " and " + other_o.classInfo();
    }

    if (c_s != STAY)
        RecordEvent(e);
}
