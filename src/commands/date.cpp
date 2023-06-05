#include "cmds.h"

#include <chrono>
#include <iostream>

int cmds::date(const std::vector<std::string>& arg,
               StreamManager& stream_manager,
               VariableManager& variable_manager) {
    std::time_t time_now =
        std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    stream_manager.out() << std::ctime(&time_now);
    return 0;
}
