#include "WorldListener.h"

#include <utility>

void WorldListener::AddEvent(string d) {
    events.push_back({std::move(d)});
}

void WorldListener::AddEvent(const WorldEvent& we) {
    events.push_back(we);
}
