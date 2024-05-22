#pragma once

#include <string>

class Computer {
public:
    explicit Computer(unsigned int n, unsigned int r);

    unsigned int computerNumber() const; //возвращает номер компьютера
    unsigned int computerPayment() const; //возвращает выручку компьютера

    std::string name() const; //возвращает имя сидящего за этим компьютером клиента (или пустую строку при его отсутствии)
    std::string time() const; //возвращает время работы

    bool isBusy() const;

    void busyOn(const std::string &name, const std::string &time); //выдать компьютер клиенту
    void busyOff(const std::string &time); //забрать компьютер у клиента и подсчитать выручку и время работы

private:
    unsigned int number;
    unsigned int rate;
    unsigned int payment;

    int timeStartHours;
    int timeStartMinutes;
    int timeBusyHours;
    int timeBusyMinutes;

    std::string clientName;

    bool busy;
};