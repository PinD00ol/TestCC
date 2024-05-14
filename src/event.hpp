#pragma once

#include <string>
#include <vector>

#include "errors.hpp"
#include "computer.hpp"

class Event {
public:
    Event(int id, unsigned int table, std::string name, std::string time);

    std::string time();

    void run();

    static void vectorComputers(unsigned int tablesCount, unsigned int rate);

private:
    static std::vector<Computer> computers;
    int idEvent;
    unsigned int numberTable;
    std::string clientName;
    std::string timeEvent;
};