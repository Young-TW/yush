#ifndef ENV_PATH_CMDS_H
#define ENV_PATH_CMDS_H

#include <string>

std::string env_path_get() {
    #ifdef _WIN32

    std::string env_path = std::getenv("Path");

    #elif __linux__

    std::string env_path = std::getenv("PATH");

    #elif __APPLE__

    std::string env_path = std::getenv("PATH");

    #endif

    return env_path;
}

#endif