#include <iostream>
#include <fstream>
#include <queue>

#include "event.hpp"

bool isPositiveInteger(const std::string& research) {
    bool result = true;
    if(!research.empty()) {
        if (research[0] < '1' || research[0] > '9')
            result = false;
        else {
            for (int i = 1; i < research.size(); ++i) {
                if (research[i] < '0' || research[i] > '9') {
                    result = false;
                    break;
                }
            }
        }
    }
    else
        result = false;
    return result;
}

bool isRightTime(const std::string& time) {
    bool result = true;
    if(time.size() == 5) {
        for (int i = 0; i < 5; ++i) {
            switch (i) {
                case 0:
                case 1:
                case 3:
                case 4:
                    if (time[i] < '0' || time[i] > '9')
                        result = false;
                    break;
                case 2:
                    if (time[i] != ':')
                        result = false;
                    break;
            }
        }
    }
    else
        result = false;
    return result;
}

bool isRightName(const std::string& name) {
    bool result = true;
    if(!name.empty()) {
        for (auto c: name) {
            if ((c < '0' && c != '-') || (c > '9' && c < 'a' && c != '_') || c > 'z') {
                result = false;
                break;
            }
        }
    }
    else
        result = false;
    return result;
}

int main(int argc, char** argv) {
    std::ifstream file;
    unsigned int tablesCount, rate;
    std::string timeStart, timeEnd;
    std::queue<Event> events;

    if (argc > 1)
        file.open(argv[1]);
    else {
        std::cerr << "Event file of club is missing!";
        std::exit(1);
    }
    try {
        std::string research;
        file >> research;
        if(!isPositiveInteger(research))
            throw std::invalid_argument("Mistake in line 1!\n");
        tablesCount = std::stoi(research);

        file >> timeStart >> timeEnd;
        if(!isRightTime(timeStart) || !isRightTime(timeEnd))
            throw std::invalid_argument("Mistake in line 2!\n");

        file >> research;
        if(!isPositiveInteger(research))
            throw std::invalid_argument("Mistake in line 3!\n");
        rate = std::stoi(research);

        unsigned int lineNumber = 4;
        while (file.good()) {
            std::string timeEvent, clientName;
            int idEvent;
            unsigned int numberTable;
            file >> timeEvent >> research >> clientName;
            if (!isRightTime(timeEvent) || !isPositiveInteger(research) || !isRightName(clientName))
                throw std::invalid_argument("Mistake in the line " + std::to_string(lineNumber) + "!\n");
            idEvent = std::stoi(research);
            if (idEvent == 2)
                file >> numberTable;
            else
                numberTable = 0;
            events.emplace(idEvent, numberTable, clientName, timeEvent);
            lineNumber++;
        }
    }
    catch (std::invalid_argument& e) {
        std::cerr << e.what();
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
