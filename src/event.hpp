#pragma once

#include <string>
#include <vector>
#include <queue>

#include "errors.hpp"
#include "computer.hpp"
#include "client.hpp"

class Event {
public:
    Event(int id, unsigned int table, std::string name, std::string time);

    std::string time();
    void runEvent();

    static void vectorComputers(unsigned int tablesCount, unsigned int rate);
    static void timeStartEnd(std::string start, std::string end);
    static void paymentComputers();
    static void kickClients();

private:
    static std::vector<Computer> computers;
    static std::vector<Client> clients;
    static std::queue<Client> waitingClients;
    static std::string timeStart;
    static std::string timeEnd;

    int idEvent;
    unsigned int tableNumber;
    std::string clientName;
    std::string timeEvent;

    void errorOutput(Errors error);
};