#ifndef ENV_PATH_CMDS_H
#define ENV_PATH_CMDS_H

#include <string>

std::string env_path_get() {
    std::string env_path = std::getenv("PATH");
    return env_path;
}

#endif