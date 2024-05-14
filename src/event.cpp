#include "event.hpp"

Event::Event(int id, unsigned int table, std::string name, std::string time) {
    idEvent = id;
    clientName = name;
    numberTable = table;
    timeEvent = time;
}