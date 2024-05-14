#include <iostream>
#include <fstream>
#include <queue>

#include "computer.hpp"
#include "event.hpp"

int main(int argc, char** argv) {
    std::ifstream file;
    unsigned int tableCount, lineNumber, payment;
    std::string timeStart, timeEnd;
    std::queue<Event> events;
    std::vector<Computer> computers;

    if(argc > 1)
        file.open(argv[1]);
    else {
        std::cerr << "Event file of club is missing!";
        std::exit(1);
    }

    file >> tableCount >> timeStart >> timeEnd >> payment;
    while (file.good()) {
        std::string timeEvent, clientName;
        int idEvent;
        unsigned int numberTable;
        file >> timeEvent >> idEvent >> clientName;
        if(idEvent == 4) file >> numberTable;
        else numberTable = 0;
        events.emplace(idEvent, numberTable, clientName, timeEvent);
    }
    file.close();

    for(int i = 1; i <= tableCount; i++)
        computers.emplace_back(i);

    return 0;
}
