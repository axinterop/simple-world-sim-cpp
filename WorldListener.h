#ifndef PR1_WORLDLISTENER_H
#define PR1_WORLDLISTENER_H

#include <string>
#include <queue>

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

    void AddEvent(std::string d);
    void AddEvent(const WorldEvent& we);
};


#endif //PR1_WORLDLISTENER_H
