#ifndef ENV_HOME_DIR_H
#define ENV_HOME_DIR_H

#include <string>
#include <pwd.h>
#include <unistd.h>

const std::string home_dir{getpwuid(getuid())->pw_dir};

#endif