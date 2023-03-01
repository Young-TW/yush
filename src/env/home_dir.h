#ifndef ENV_HOME_DIR_H
#define ENV_HOME_DIR_H

#include <string>

#include "env/system_var.h"

const std::string home_dir =
#ifdef __WINDOWS__
    "C:/Users/" + user_name
#elif defined(_WIN32)
    "C:/Users/" + user_name
#elif defined(__WIN64)
    "C:/Users/" + user_name
#elif defined(__APPLE__)
    "/Users/" + user_name
#elif defined(__unix__)
    "/home/" + user_name
#elif defined(__linux__)
    "/home/" + user_name
#else
    "ERROR"
#endif
;


#endif