#ifndef FEATURE_RAND_STR_GEN_H
#define FEATURE_RAND_STR_GEN_H

#include <ctime>
#include <iostream>
#ifdef __APPLE__
#include <unistd.h>
#elif __unix__
#include <unistd.h>
#elif __linux__
#include <unistd.h>
#else
#include <io.h>
#endif
#include <string>

std::string gen_random(const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return tmp_s;
}

#endif