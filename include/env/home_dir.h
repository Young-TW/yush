#ifndef ENV_HOME_DIR_H
#define ENV_HOME_DIR_H

#include <string>

#ifdef _WIN32 // Both of 32-bit and 64-bit define this.

#include <cstdlib>

std::string home_dir{std::getenv("USERPROFILE")};

#elif __linux__

#include <pwd.h>
#include <unistd.h>

std::string home_dir{getpwuid(getuid())->pw_dir};

#elif __APPLE__

#include <pwd.h>
#include <unistd.h>

std::string home_dir{getpwuid(getuid())->pw_dir};

#endif

#endif
