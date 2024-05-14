#pragma once

#include <string>

struct Client {
    Client(std::string name);

    std::string clientName;
    unsigned int tableNumber;
};

