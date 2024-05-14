#include "event.hpp"

Event::Event(int id, unsigned int table, std::string name, std::string time) {
    idEvent = id;
    clientName = name;
    numberTable = table;
    timeEvent = time;
}

std::string Event::time() {
    return timeEvent;
}

void Event::run() {

}

void Event::vectorComputers(unsigned int tablesCount, unsigned int rate) {
    for(int i = 1; i <= tablesCount; i++)
        computers.emplace_back(i, rate);
}