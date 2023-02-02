#include <iostream>
#include <fstream>

#include "shell.h"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        return Shell(std::cin).run();
    }
    if (argc == 2) {
        std::ifstream fin(argv[1]);
        return Shell(fin).run();
    }

    return 1;
}