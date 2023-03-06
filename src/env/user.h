#ifndef ENV_USER_H
#define ENV_USER_H

#include <string>

const std::string user_name =
#ifdef __WINDOWS__
    "Young"
#elif defined(_WIN32)
    "Young"
#elif defined(__WIN64)
    "Young"
#elif defined(__APPLE__)
    "young"
#elif defined(__unix__)
    "young"
#elif defined(__linux__)
    "young"
#else
    "young"
#endif
;

#endif