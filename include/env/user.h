#ifndef ENV_USER_H
#define ENV_USER_H

#include <string>

const std::string user_name =
#ifdef _WIN32
    std::getenv("USERNAME")
#elif __APPLE__
    std::getenv("USER")
#elif __unix__
    std::getenv("USER")
#elif __linux__
    std::getenv("USER")
#else
    #error Unsupported platform.
#endif
;

#endif
