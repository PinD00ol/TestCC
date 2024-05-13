#pragma once

#include <string>

struct Event {
    int hour;
    int minute;
    int idEvent;
    int table;
    std::string clientName;
    Event(int h, int m, int id, std::string name, int t);
};