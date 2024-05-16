#pragma once

#include <string>
#include <vector>
#include <map>
#include <list>

#include "errors.hpp"
#include "computer.hpp"

class Event {
public:
    Event(int id, unsigned int table, std::string name, std::string time);

    std::string time();
    std::string lineEvent();
    std::string runEvent();

    static void vectorComputers(size_t tablesCount, unsigned int rate);
    static void timeStartEnd(std::string start, std::string end);
    static void kickClients();
    static void paymentComputers();

private:
    static std::vector<Computer> computers;
    static std::map<std::string, unsigned int> clients; //unsigned int отвечает за номер занятого стола
    static std::list<std::string> waitingClients;
    static std::string timeStart;
    static std::string timeEnd;

    int idEvent;
    unsigned int tableNumber;
    std::string clientName;
    std::string timeEvent;

    std::string errorOutput(Errors error);
};