#ifndef ENV_PATH_CMDS_H
#define ENV_PATH_CMDS_H

#include <string>

std::string env_path_get() {
    #ifdef _WIN32

    #elif __linux__

    #include <cstdlib>

    std::string env_path = std::getenv("PATH");

    #elif __APPLE__

    #endif

    // string_parser(env_path, ':')

    return env_path;
}

#endif