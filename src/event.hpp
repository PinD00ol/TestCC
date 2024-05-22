#pragma once

#include <string>
#include <vector>
#include <map>
#include <list>

#include "errors.hpp"
#include "computer.hpp"

class Event {
public:
    Event(int id, unsigned int table, const std::string &name, const std::string &time);

    std::string time(); //возвращает время события
    std::string lineEvent(); //возвращает строку входящего события для вывода в консоль (и проверки тестами)
    std::string runEvent(std::vector<Computer>& computers); //возвращает строку исходящего события для вывода в консоль (и проверки тестами)

    static void timeStartEnd(const std::string &start, const std::string &end);
    static void kickClients(std::vector<Computer>& computers); //очищает список клиентов и выводит их на консоль как исходящее событие с id 11

private:
    static std::map<std::string, unsigned int> clients; //unsigned int отвечает за номер занятого стола
    static std::list<std::string> waitingClients;
    static std::string timeStart;
    static std::string timeEnd;

    int idEvent;
    unsigned int tableNumber;
    std::string clientName;
    std::string timeEvent;

    std::string errorOutput(Errors error) const;
};