#include <iostream>
#include <fstream>

#include "shell.h"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        return Shell().run(std::cin, std::cout, std::cerr);
    }

    if (argc == 2) {
        std::ifstream fin(argv[1]);
        return Shell().run(fin, std::cout, std::cerr);
    }

    return 1;
}