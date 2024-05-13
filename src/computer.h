#pragma once

class Computer {
public:
    explicit Computer(int n);

    bool isBusy() const;
    int computerNumber() const;

    void changeBusy();

private:
    int number;
    bool busy = false;
};