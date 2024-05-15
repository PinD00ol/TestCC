#include <iostream>
#include "event.hpp"

Event::Event(int id, unsigned int table, std::string name, std::string time) {
    idEvent = id;
    clientName = name;
    tableNumber = table;
    timeEvent = time;
}

std::string Event::time() {
    return timeEvent;
}

std::string Event::lineEvent() {
    return timeEvent + ' ' + std::to_string(idEvent) + ' ' + clientName
        + (tableNumber == 0 ? "\n" : ' ' + std::to_string(tableNumber) + '\n');
}

std::string Event::runEvent() {
    Errors error = NoErrors;
    std::string result = "";
    switch (idEvent) {
        case 1:
            if (timeEvent < timeStart || timeEvent > timeEnd)
                error = NotOpenYet;
            else if(clients.contains(clientName))
                error = YouShallNotPass;

            if (error != NoErrors)
                result = errorOutput(error);
            else
                clients.insert({clientName, 0});
            break;
        case 2:
            error = ClientUnknown;
            if (clients.contains(clientName))
                error = NoErrors;

            if (error == ClientUnknown)
                result = errorOutput(error);
            else {
                if (computers[tableNumber - 1].isBusy())
                    error = PlaceIsBusy;
                else {
                    if (clients[clientName] != 0)
                        computers[clients[clientName] - 1].busyOff(timeEvent);
                    computers[tableNumber - 1].busyOn(clientName, timeEvent);
                    clients[clientName] = tableNumber;
                }

                if(error == PlaceIsBusy)
                    result = errorOutput(error);
            }
            break;
        case 3:
            std::cout << timeEvent << " 3 " << clientName << '\n';
            error = ClientUnknown;
            if (clients.contains(clientName))
                error = NoErrors;

            if (error == ClientUnknown)
                result = errorOutput(error);
            else {
                for (const auto& computer: computers)
                    if (!computer.isBusy()) {
                        error = ICanWaitNoLonger;
                        break;
                    }

                if(error == ICanWaitNoLonger)
                    result = errorOutput(error);
                else if(waitingClients.size() > computers.size())
                    std::cout << timeEvent << " 11 " << clientName << '\n';
                else
                    waitingClients.push(clientName);
            }
            break;
        case 4:
            std::cout << timeEvent << " 4 " << clientName << '\n';
            error = ClientUnknown;
            if (clients.contains(clientName))
                error = NoErrors;

            if (error == ClientUnknown)
                result = errorOutput(error);
            else {
                if (clients[clientName] != 0) {
                    unsigned int table = clients[clientName] - 1;
                    computers[table].busyOff(timeEvent);

                    while (!waitingClients.empty()) {
                        std::string client = waitingClients.front();
                        waitingClients.pop();

                        if (clients.contains(client)) {
                            computers[table].busyOn(client, timeEvent);
                            clients[client] = table + 1;
                            std::cout << timeEvent << " 12 " << clientName << ' ' << tableNumber << '\n';
                            break;
                        }
                    }
                }
                clients.erase(clientName);
            }
    }
    return result;
}

Computer Event::computer(unsigned int n) {
    return n >= computers.size() ? Computer(0, 0) : computers[n];
}

void Event::vectorComputers(unsigned int tablesCount, unsigned int rate) {
    for (int i = 1; i <= tablesCount; i++)
        computers.emplace_back(i, rate);
}

void Event::timeStartEnd(std::string start, std::string end) {
    timeStart = start;
    timeEnd = end;
}

std::string Event::errorOutput(Errors error) {
    std::string errString;
    switch (error) {
        case NotOpenYet:
            errString = "NotOpenYet\n";
            break;
        case YouShallNotPass:
            errString = "YouShallNotPass\n";
            break;
        case PlaceIsBusy:
            errString = "PlaceIsBusy\n";
            break;
        case ICanWaitNoLonger:
            errString = "ICanWaitNoLonger!\n";
            break;
        case ClientUnknown:
            errString = "ClientUnknown\n";
            break;
    }
    return timeEvent + " 13 " + errString;
}

void Event::kickClients() {
    while (!waitingClients.empty())
        waitingClients.pop();
    for (const auto& client: clients) {
        if(client.second != 0)
            computers[client.second - 1].busyOff(timeEnd);
        std::cout << timeEnd << " 11 " << client.first << '\n';
    }
    clients.clear();
}

void Event::paymentComputers() {
    for (const auto& computer: computers)
        std::cout << computer.computerNumber() << ' ' << computer.computerPayment() << ' ' << computer.time() << '\n';
}

std::vector<Computer> Event::computers;
std::map<std::string, unsigned int> Event::clients;
std::queue<std::string> Event::waitingClients;
std::string Event::timeStart = "00:00";
std::string Event::timeEnd = "00:00";