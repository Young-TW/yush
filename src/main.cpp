#include <iostream>
#include <fstream>

#include "shell.h"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        Shell shell(std::cin, std::cout, std::cerr);
        shell.init();
        return shell.run(true);
    }

    if (argc >= 2) {
        std::ifstream fin(argv[1]);
        return Shell(std::cin, std::cout, std::cerr).run(false);
    }

    return 1;
}