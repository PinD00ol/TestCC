#pragma once

#include <string>

#include "errors.hpp"

struct Event {
    int idEvent;
    unsigned int numberTable;
    std::string clientName;
    std::string timeEvent;

    Event(int id, unsigned int table, std::string name, std::string time);
};