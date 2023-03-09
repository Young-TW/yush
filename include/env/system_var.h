#ifndef ENV_SYSTEM_VAR_H
#define ENV_SYSTEM_VAR_H

#include <string>

const std::string sys =
#ifdef __WINDOWS__
    "Windows"
#elif defined(_WIN32)
    "Windows"
#elif defined(__WIN64)
    "Windows"
#elif defined(__APPLE__)
    "MacOS"
#elif defined(__unix__)
    "Unix"
#elif defined(__linux__)
    "Linux"
#else
    "Unknown"
#endif
;

#endif