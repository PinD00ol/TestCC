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
    unsigned int clientID;
    switch (idEvent) {
        case 1:
            for (auto client: clients)
                if (client.clientName == clientName) {
                    error = YouShallNotPass;
                    break;
                }

            if (timeEvent < timeStart || timeEvent > timeEnd)
                error = NotOpenYet;

            if (error != NoErrors)
                errorOutput(error);
            else {
                std::cout << timeEvent << " 1 " << clientName << '\n';
                clients.emplace_back(clientName);
            }
            break;
        case 2:
            error = ClientUnknown;
            for (unsigned int i = 0; i < clients.size(); i++)
                if (clients[i].clientName == clientName) {
                    error = NoErrors;
                    clientID = i;
                    break;
                }

            if (error == ClientUnknown)
                errorOutput(error);
            else {
                if (computers[tableNumber - 1].isBusy())
                    error = PlaceIsBusy;
                else {
                    if (clients[clientID].tableNumber != 0)
                        computers[clients[clientID].tableNumber - 1].busyOff(timeEvent);
                    computers[tableNumber - 1].busyOn(clientName, timeEvent);
                    clients[clientID].tableNumber = tableNumber;
                }

                if(error == PlaceIsBusy)
                    errorOutput(error);
                else
                    std::cout << timeEvent << " 2 " << clientName << ' '  << tableNumber << '\n';
            }
            break;
        case 3:
            for (auto computer: computers)
                if (!computer.isBusy()) {
                    error = ICanWaitNoLonger;
                    break;
                }

            if(waitingClients.size() > computers.size())
                std::cout << timeEvent << " 11 " << clientName << '\n';
            else {
                waitingClients.emplace(clientName);
                std::cout << timeEvent << " 3 " << clientName << '\n';
            }
            break;
        case 4:
            error = ClientUnknown;
            for (unsigned int i = 0; i < clients.size(); i++)
                if (clients[i].clientName == clientName) {
                    error = NoErrors;
                    clientID = i;
                    break;
                }

            if (error == ClientUnknown)
                errorOutput(error);
            else {
                std::cout << timeEvent << " 4 " << clientName << '\n';
                if (clients[clientID].tableNumber != 0) {
                    unsigned int table = clients[clientID].tableNumber - 1;
                    computers[table].busyOff(timeEvent);
                    bool hasFounded = false;

                    while (!waitingClients.empty() && !hasFounded) {
                        Client client = waitingClients.front();
                        waitingClients.pop();

                        for (auto c : clients)
                            if (c.clientName == client.clientName) {
                                computers[table].busyOn(client.clientName, timeEvent);
                                std::cout << timeEvent << " 12 " << clientName << ' '  << tableNumber << '\n';
                                hasFounded = true;
                                break;
                            }
                    }
                }
                auto it = clients.begin() + clientID;
                clients.erase(it);
            }
            break;
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