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

void Computer::changeBusy() {
    if(busy)
        busy = false;
    else
        busy = true;
}