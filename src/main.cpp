#include <iostream>
#include <fstream>

#include "shell.h"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        return Shell(std::cin).run();
    }
    if (argc == 2) {
        return Shell(std::ifstream(argv[1])).run();
    }

    return 1;
}