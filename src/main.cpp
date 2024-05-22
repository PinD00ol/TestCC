#include <iostream>

#include "event.hpp"
#include "insertion.hpp"

int main(int argc, char** argv) {
    std::ifstream file;
    unsigned int tablesCount, rate;
    std::string timeStart, timeEnd;
    std::queue<Event> events;
    std::vector<Computer> computers;

    if (argc > 1)
        file.open(argv[1]);
    else {
        std::cerr << "Event file of club is missing!";
        std::exit(1);
    }
    try {
        events = inputEvents(file, tablesCount, rate, timeStart, timeEnd);
    }
    catch (std::invalid_argument& e) {
        std::cerr << e.what();
        exit(2);
    }
    file.close();

    for (unsigned int i = 1; i <= tablesCount; i++)
        computers.emplace_back(i, rate);

    Event::timeStartEnd(timeStart, timeEnd);

    std::cout << timeStart << '\n';
    while (!events.empty()) {
        if(std::string time = events.front().time(); time > timeEnd)
            break;
        std::cout << events.front().lineEvent() << events.front().runEvent(computers);
        events.pop();
    }

    Event::kickClients(computers);
    while (!events.empty()) { //Если остались события, чьё время после закрытия
        events.front().runEvent(computers);
        events.pop();
    }
    std::cout << timeEnd << '\n';

    for (const auto& computer: computers)
        std::cout << computer.computerNumber() << ' ' << computer.computerPayment() << ' ' << computer.time() << '\n';

    return 0;
}
