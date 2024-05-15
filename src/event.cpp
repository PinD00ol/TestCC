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

void Event::runEvent() {
    Errors error = NoErrors;
    switch (idEvent) {
        case 1:
            std::cout << timeEvent << " 1 " << clientName << '\n';
            if (timeEvent < timeStart || timeEvent > timeEnd)
                error = NotOpenYet;
            else if(clients.contains(clientName))
                error = YouShallNotPass;

            if (error != NoErrors)
                errorOutput(error);
            else
                clients.insert({clientName, 0});
            break;
        case 2:
            std::cout << timeEvent << " 2 " << clientName << ' '  << tableNumber << '\n';
            error = ClientUnknown;
            if (clients.contains(clientName))
                error = NoErrors;

            if (error == ClientUnknown)
                errorOutput(error);
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
                    errorOutput(error);
            }
            break;
        case 3:
            std::cout << timeEvent << " 3 " << clientName << '\n';
            for (const auto& computer: computers)
                if (!computer.isBusy()) {
                    error = ICanWaitNoLonger;
                    break;
                }

            if(error == ICanWaitNoLonger)
                errorOutput(error);
            else if(waitingClients.size() > computers.size())
                std::cout << timeEvent << " 11 " << clientName << '\n';
            else
                waitingClients.push(clientName);
            break;
        case 4:
            std::cout << timeEvent << " 4 " << clientName << '\n';
            error = ClientUnknown;
            if (clients.contains(clientName))
                error = NoErrors;

            if (error == ClientUnknown)
                errorOutput(error);
            else {
                if (clients[clientName] != 0) {
                    unsigned int table = clients[clientName] - 1;
                    computers[table].busyOff(timeEvent);
                    bool hasFound = false;

                    while (!waitingClients.empty() && !hasFound) {
                        std::string client = waitingClients.front();
                        waitingClients.pop();

                        if (clients.contains(client)) {
                            computers[table].busyOn(client, timeEvent);
                            std::cout << timeEvent << " 12 " << clientName << ' ' << tableNumber << '\n';
                            hasFound = true;
                            break;
                        }
                    }
                }
                clients.erase(clientName);
            }
    }
}


void Event::vectorComputers(unsigned int tablesCount, unsigned int rate) {
    for (int i = 1; i <= tablesCount; i++)
        computers.emplace_back(i, rate);
}

void Event::timeStartEnd(std::string start, std::string end) {
    timeStart = start;
    timeEnd = end;
}

void Event::errorOutput(Errors error) {
    std::cout << timeEvent << " 13 " << error << (error == ICanWaitNoLonger ? "!" : "") << '\n';
}

void Event::kickClients() {

}