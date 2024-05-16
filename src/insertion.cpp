#include "insertion.h"
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
    if (time.size() == 5) {
        if (time[0] < '0' || time[0] > '2')
            result = false;
        else if (time[1] < '0' || time[1] > '9' || time[0] == '2' && time[1] > '3')
            result = false;
        else if (time[2] != ':')
            result = false;
        else if (time[3] < '0' || time[3] > '5')
            result = false;
        else if (time[4] < '0' || time[4] > '9')
            result = false;
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

bool isID(const std::string& research) {
    bool result = true;
    if(research.size() == 1) {
        if (research[0] < '1' || research[0] > '4')
            result = false;
    }
    else
        result = false;
    return result;
}

std::queue<Event> inputEvents(std::ifstream& file,unsigned int& tablesCount, unsigned int& rate, std::string& timeStart, std::string& timeEnd) {
    std::string research;
    std::queue<Event> events;
    file >> research;
    if(!isPositiveInteger(research))
        throw std::invalid_argument("Mistake in the line 1!\n");
    tablesCount = std::stoi(research);

    file >> timeStart >> timeEnd;
    if(!isRightTime(timeStart) || !isRightTime(timeEnd))
        throw std::invalid_argument("Mistake in the line 2!\n");

    file >> research;
    if(!isPositiveInteger(research))
        throw std::invalid_argument("Mistake in the line 3!\n");
    rate = std::stoi(research);

    unsigned int lineNumber = 4;
    while (file.good()) {
        std::string timeEvent, clientName;
        int idEvent;
        unsigned int numberTable;
        file >> timeEvent >> research >> clientName;
        if (!isRightTime(timeEvent) || !isID(research) || !isRightName(clientName))
            throw std::invalid_argument("Mistake in the line " + std::to_string(lineNumber) + "!\n");
        idEvent = std::stoi(research);
        if (idEvent == 2) {
            file >> research;
            if(!isPositiveInteger(research))
                throw std::invalid_argument("Mistake in the line " + std::to_string(lineNumber) + "!\n");
            numberTable = std::stoi(research);
            if(numberTable > tablesCount)
                throw std::invalid_argument("Mistake in the line " + std::to_string(lineNumber) + "!\n");
        }
        else
            numberTable = 0;
        events.emplace(idEvent, numberTable, clientName, timeEvent);
        lineNumber++;
    }
    return events;
}