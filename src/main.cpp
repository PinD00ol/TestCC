#include <iostream>

#include "event.hpp"
#include "insertion.hpp"

int main(int argc, char** argv) {
    std::ifstream file;
    unsigned int tablesCount, rate;
    std::string timeStart, timeEnd;
    std::queue<Event> events;

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

    Event::vectorComputers(tablesCount, rate);
    Event::timeStartEnd(timeStart, timeEnd);

    std::cout << timeStart << '\n';
    while (!events.empty()) {
        std::string time = events.front().time();
        if(time > timeEnd)
            break;
        std::cout << events.front().lineEvent() << events.front().runEvent();
        events.pop();
    }

    Event::kickClients();
    while (!events.empty()) { //Если остались события, чьё время после закрытия
        events.front().runEvent();
        events.pop();
    }
    std::cout << timeEnd << '\n';
    Event::paymentComputers();

    return 0;
}
