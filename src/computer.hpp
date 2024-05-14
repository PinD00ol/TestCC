#pragma once

#include <string>

class Computer {
public:
    explicit Computer(int n);

    bool isBusy() const;
    int computerNumber() const;
    std::string name() const;

    void busyOn(std::string name);
    void busyOff();

private:
    int number;
    std::string clientName = "";
    bool busy = false;
};