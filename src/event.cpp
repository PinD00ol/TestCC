#include <iostream>
#include <algorithm>
#include "event.hpp"

Event::Event(int id, unsigned int table, const std::string &name, const std::string &time) {
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

std::string Event::runEvent(std::vector<Computer>& computers) {
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
                    result = errorOutput(PlaceIsBusy);
                else {
                    if (clients[clientName] != 0)
                        computers[clients[clientName] - 1].busyOff(timeEvent);
                    computers[tableNumber - 1].busyOn(clientName, timeEvent);
                    clients[clientName] = tableNumber;

                    auto eventClient = std::find(waitingClients.begin(), waitingClients.end(), clientName);
                    if(eventClient != waitingClients.end())
                        waitingClients.erase(eventClient);

                }
            }
            break;
        case 3:
            if(!clients.contains(clientName))
                clients.insert({clientName, 0});

            for (const auto& computer: computers)
                if (!computer.isBusy()) {
                    error = ICanWaitNoLonger;
                    break;
                }

            if(error == ICanWaitNoLonger) {
                result = errorOutput(error);
                if(std::find(waitingClients.begin(), waitingClients.end(), clientName) == waitingClients.end())
                    waitingClients.push_back(clientName);
            }
            else if(waitingClients.size() > computers.size()) {
                result = timeEvent + " 11 " + clientName + '\n';
                clients.erase(clientName);
            }
            else
            if(std::find(waitingClients.begin(), waitingClients.end(), clientName) == waitingClients.end())
                waitingClients.push_back(clientName);
            break;
        case 4:
            error = ClientUnknown;
            if (clients.contains(clientName))
                error = NoErrors;

            if (error == ClientUnknown)
                result = errorOutput(error);
            else {
                if (clients[clientName] != 0) {
                    unsigned int table = clients[clientName] - 1;
                    computers[table].busyOff(timeEvent);

                    if (!waitingClients.empty()) {
                        std::string client = waitingClients.front();
                        waitingClients.pop_front();

                        computers[table].busyOn(client, timeEvent);
                        clients[client] = table + 1;
                        result = timeEvent + " 12 " + client + ' ' + std::to_string(table + 1) + '\n';
                    }
                }
                else {
                    auto eventClient = std::find(waitingClients.begin(), waitingClients.end(), clientName);
                    if(eventClient != waitingClients.end())
                        waitingClients.erase(eventClient);
                }
                clients.erase(clientName);
            }
    }
    return result;
}

void Event::timeStartEnd(const std::string &start, const std::string &end) {
    timeStart = start;
    timeEnd = end;
}

std::string Event::errorOutput(Errors error) const {
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

void Event::kickClients(std::vector<Computer>& computers) {
    for (const auto& client: clients) {
        if(client.second != 0)
            computers[client.second - 1].busyOff(timeEnd);
        std::cout << timeEnd << " 11 " << client.first << '\n';
    }
    waitingClients.clear();
    clients.clear();
}

std::map<std::string, unsigned int> Event::clients;
std::list<std::string> Event::waitingClients;
std::string Event::timeStart = "00:00";
std::string Event::timeEnd = "00:00";