#include "event.h"

Event::Event(int h, int m, int id, std::string name, int t) {
    hour = h;
    minute = m;
    idEvent = id;
    clientName = name;
    table = t;
}