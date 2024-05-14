#pragma once

#include <string>

class Computer {
public:
    explicit Computer(unsigned int n, unsigned int r);

    unsigned int computerNumber() const;
    unsigned int computerPayment() const;

    std::string name() const;
    std::string time() const;

    bool isBusy() const;

    void busyOn(std::string name, std::string time);
    void busyOff(std::string time);

private:
    unsigned int number;
    unsigned int rate;
    unsigned int payment;

    std::string clientName;
    std::string timeStart;
    std::string timeBusy;

    bool busy;
};