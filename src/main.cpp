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
    try {
        lineNumber = 1;
        std::string research;
        file >> research;
        tablesCount = std::stoi(research);

        lineNumber++;
        file >> timeStart >> timeEnd;

        lineNumber++;
        file >> research;
        rate = std::stoi(research);

        lineNumber++;
        while (file.good()) {
            std::string timeEvent, clientName;
            int idEvent;
            unsigned int numberTable;
            file >> timeEvent >> research >> clientName;
            idEvent = std::stoi(research);
            if (idEvent == 2)
                file >> numberTable;
            else
                numberTable = 0;
            events.emplace(idEvent, numberTable, clientName, timeEvent);
            lineNumber++;
        }
    }
    catch (std::exception e) {
        std::cerr << "Mistake in line " << lineNumber << "!\n";
        exit(2);
    }
    file.close();

    Event::vectorComputers(tablesCount, rate);
    Event::timeStartEnd(timeStart, timeEnd);

    std::cout << timeStart << '\n';
    while (!events.empty()) {
        std::string time = events.front().time();
        if(time > timeEnd)
            break;
        events.front().runEvent();
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
