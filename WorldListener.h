#ifndef PR1_WORLDLISTENER_H
#define PR1_WORLDLISTENER_H

#include <string>
#include <queue>

using namespace std;

struct WorldEvent {
//    string title;
//    int priority; // May be useful
    string details;
};


class WorldListener {
private:
    queue<WorldEvent> events;

    friend class Renderer;
public:
    WorldListener() { events = {}; };
    ~WorldListener() = default;

    void AddEvent(string d);
    void AddEvent(const WorldEvent& we);
};


#endif //PR1_WORLDLISTENER_H
