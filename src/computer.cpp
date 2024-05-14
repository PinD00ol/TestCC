#include "computer.hpp"

Computer::Computer(unsigned int n, unsigned int r) {
    number = n;
    rate = r;
    payment = 0;

    timeStartHours = 0;
    timeStartMinutes = 0;
    timeBusyHours = 0;
    timeBusyMinutes = 0;

    clientName = "";

    busy = false;
}

unsigned int Computer::computerNumber() const {
    return number;
}

unsigned int Computer::computerPayment() const {
    return payment;
}

std::string Computer::name() const {
    return clientName;
}

std::string Computer::time() const {
    return (timeBusyHours < 10 ? "0" : "") + std::to_string(timeBusyHours) + ':'
           + (timeStartMinutes < 10 ? "0" : "") + std::to_string(timeStartMinutes);
}

bool Computer::isBusy() const {
    return busy;
}

void Computer::busyOn(std::string name, std::string time) {
    if(!busy) {
        timeStartHours = static_cast<int>(time[0] + time[1]);
        timeStartMinutes = static_cast<int>(time[3] + time[4]);

        clientName = name;
        busy = true;
    }
}

void Computer::busyOff(std::string time) {
    if(busy) {
        int timeHours = static_cast<int>(time[0] + time[1]);
        int timeMinutes = static_cast<int>(time[3] + time[4]);

        int hoursDifference = timeHours - timeStartHours;
        int minutesDifference = timeMinutes - timeStartMinutes;

        if(minutesDifference < 0) {
            minutesDifference = 0 - minutesDifference;
            hoursDifference--;
            payment += rate * (hoursDifference + 1);
        }
        else if(minutesDifference > 0)
            payment += rate * (hoursDifference + 1);
        else
            payment += rate * hoursDifference;

        timeBusyHours += hoursDifference;
        timeBusyMinutes += minutesDifference;
        if(timeBusyMinutes > 59) {
            timeBusyMinutes -= 60;
            timeBusyHours++;
        }

        clientName = "";
        busy = false;
    }
}