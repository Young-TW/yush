#include <iostream>
#include <chrono>
#include <iomanip>

#include "stream_manager.hpp"
#include "variable_manager.h"
#include "cmds.h"

int cmd::date(const std::vector<std::string>& arg, StreamManager& stream_manager, VariableManager& variable_manager) {
    std::time_t time_now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    stream_manager.out() << std::ctime(&time_now);
    return 0;
}