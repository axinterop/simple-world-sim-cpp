#include "WorldListener.h"

#include <utility>

void WorldListener::AddEvent(string d) { events.push({std::move(d)}); }

void WorldListener::AddEvent(const WorldEvent &we) { events.push(we); }
