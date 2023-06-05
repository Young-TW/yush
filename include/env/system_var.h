#ifndef ENV_SYSTEM_VAR_H
#define ENV_SYSTEM_VAR_H

#include <string>

const std::string sys =
#ifdef __APPLE__
    "MacOS"
#elif defined(__linux__)
    "Linux"
#elif defined(__unix__)
    "Unix"
#else
    "Unknown"
#endif
    ;

#endif
