#include "computer.hpp"

Computer::Computer(unsigned int n, unsigned int r) {
    number = n;
    rate = r;
    payment = 0;

    clientName = "";
    timeStart = "00:00";
    timeBusy = "00:00";

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
    return timeBusy;
}

bool Computer::isBusy() const {
    return busy;
}

void Computer::busyOn(std::string name, std::string time) {
    if(!busy) {
        clientName = name;
        timeStart = time;
        busy = true;
    }
}

void Computer::busyOff(std::string time) {
    if(busy) {
        int timeHours = static_cast<int>(time[0] + time[1]);
        int timeMinutes = static_cast<int>(time[3] + time[4]);
        int timeStartHours = static_cast<int>(timeStart[0] + timeStart[1]);
        int timeStartMinutes = static_cast<int>(timeStart[3] + timeStart[4]);
        int timeBusyHours = static_cast<int>(timeBusy[0] + timeBusy[1]);
        int timeBusyMinutes = static_cast<int>(timeBusy[3] + timeBusy[4]);

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

        timeBusy = (timeBusyHours < 10 ? '0' + std::to_string(timeBusyHours) : std::to_string(timeBusyHours)) + ':'
                 + (timeStartMinutes < 10 ? '0' + std::to_string(timeBusyMinutes) : std::to_string(timeStartMinutes));

        clientName = "";
        timeStart = "00:00";
        busy = false;
    }
}