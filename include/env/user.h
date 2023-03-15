#ifndef ENV_USER_H
#define ENV_USER_H

#include <string>

const std::string user_name = std::getenv("USER");

#endif
