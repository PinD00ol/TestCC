#include "insertion.hpp"
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
    std::string line;
    std::string del = " ";
    std::queue<Event> events;
    std::vector<std::string> lineElements;
    size_t pos;

    std::getline(file, line);
    if (!isPositiveInteger(line))
        throw std::invalid_argument(line);
    tablesCount = std::stoi(line);


    std::getline(file, line);
    pos = line.find(del);
    while ( pos != std::string::npos) {
        lineElements.push_back(line.substr(0, pos));
        line.erase(0, pos + 1);
        pos = line.find(del);
    }
    lineElements.push_back(line);
    line = "";

    if (lineElements.size() != 2 || !isRightTime(lineElements[0]) || !isRightTime(lineElements[1])) {
        for (const auto & lineElement : lineElements)
            line += lineElement + " ";
        throw std::invalid_argument(line);
    }
    timeStart = lineElements[0];
    timeEnd = lineElements[1];
    lineElements.clear();


    std::getline(file, line);
    if (!isPositiveInteger(line))
        throw std::invalid_argument(line);
    rate = std::stoi(line);


    while (std::getline(file, line)) {
        std::string timeEvent, clientName;
        int idEvent;
        unsigned int numberTable;

        pos = line.find(del);
        while ( pos != std::string::npos) {
            lineElements.push_back(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find(del);
        }
        lineElements.push_back(line);
        line = "";

        if (lineElements.size() != 3 && lineElements.size() != 4) {
            for (const auto & lineElement : lineElements)
                line += lineElement + " ";
            throw std::invalid_argument(line);
        }

        if (!isRightTime(lineElements[0]) || !isID(lineElements[1]) || !isRightName(lineElements[2])) {
            for (const auto & lineElement : lineElements)
                line += lineElement + " ";
            throw std::invalid_argument(line);
        }

        if ((lineElements[1] == "2" && lineElements.size() == 3) || (lineElements[1] != "2" && lineElements.size() == 4)) {
            for (const auto & lineElement : lineElements)
                line += lineElement + " ";
            throw std::invalid_argument(line);
        }

        timeEvent = lineElements[0];
        idEvent = std::stoi(lineElements[1]);
        clientName = lineElements[2];

        if(!events.empty() && timeEvent < events.back().time()) {
            for (const auto & lineElement : lineElements)
                line += lineElement + " ";
            throw std::invalid_argument(line);
        }

        if(idEvent == 2) {
            if(!isPositiveInteger(lineElements[3])) {
                for (const auto & lineElement : lineElements)
                    line += lineElement + " ";
                throw std::invalid_argument(line);
            }
            numberTable = std::stoi(lineElements[3]);
            if (numberTable > tablesCount) {
                for (const auto & lineElement : lineElements)
                    line += lineElement + " ";
                throw std::invalid_argument(line);
            }
        }
        else
            numberTable = 0;
        events.emplace(idEvent, numberTable, clientName, timeEvent);
        lineElements.clear();
    }
    return events;
}