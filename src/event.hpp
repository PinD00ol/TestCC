#pragma once

#include <string>

#include "errors.hpp"
#include "computer.hpp"

class Event {
public:
    Event(int id, unsigned int table, std::string name, std::string time);

private:
    int idEvent;
    unsigned int numberTable;
    std::string clientName;
    std::string timeEvent;
};