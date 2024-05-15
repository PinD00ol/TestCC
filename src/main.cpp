#include <iostream>
#include <fstream>
#include <queue>

#include "event.hpp"

int main(int argc, char** argv) {
    std::ifstream file;
    unsigned int tablesCount, lineNumber, rate;
    std::string timeStart, timeEnd;
    std::queue<Event> events;

    if (argc > 1)
        file.open(argv[1]);
    else {
        std::cerr << "Event file of club is missing!";
        std::exit(1);
    }

    file >> tablesCount >> timeStart >> timeEnd >> rate;
    lineNumber = 4;
    while (file.good()) {
        std::string timeEvent, clientName;
        int idEvent;
        unsigned int numberTable;
        file >> timeEvent >> idEvent >> clientName;
        if (idEvent == 2)
            file >> numberTable;
        else
            numberTable = 0;
        events.emplace(idEvent, numberTable, clientName, timeEvent);
        lineNumber++;
    }
    file.close();

    Event::vectorComputers(tablesCount, rate);
    Event::timeStartEnd(timeStart, timeEnd);

    std::cout << timeStart << '\n';
    while (!events.empty()) {
        std::string time = events.front().time();
        if(time > timeEnd)
            break;
        Event event = events.front();
        event.runEvent();
        //events.front().runEvent();
        events.pop();
    }

    Event::kickClients();
    while (!events.empty()) {
        events.front().runEvent();
        events.pop();
    }
    std::cout << timeEnd << '\n';
    Event::paymentComputers();

    return 0;
}
