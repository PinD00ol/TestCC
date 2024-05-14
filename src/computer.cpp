#include "computer.hpp"

Computer::Computer(int n) {
    number = n;
}

bool Computer::isBusy() const {
    return busy;
}

int Computer::computerNumber() const {
    return number;
}

std::string Computer::name() const {
    return clientName;
}

void Computer::busyOn(std::string name) {
    if(!busy) {
        clientName = name;
        busy = true;
    }
}

void Computer::busyOff() {
    if(busy) {
        clientName = "";
        busy = false;
    }
}