#include <iostream>
#include <fstream>

#include "computer.h"
#include "event.h"

int main(int argc, char** argv) {
    std::ifstream file;
    if(argc > 1)
        file.open(argv[1]);
    else {
        std::cerr << "Event file of club is missing!";
        std::exit(1);
    }



    while (file.good()) {
    }
    return 0;
}
