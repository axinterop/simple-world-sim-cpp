#include "WorldListener.h"

#include <utility>

void WorldListener::AddEvent(std::string d) { events.push({std::move(d)}); }

void WorldListener::AddEvent(const WorldEvent &we) { events.push(we); }
