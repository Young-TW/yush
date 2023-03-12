#include <filesystem>

#include "stream_manager.hpp"
#include "variable_manager.h"
#include "cmds.h"

int cmds::pwd(const std::vector<std::string>& arg, StreamManager& stream_manager, VariableManager& variable_manager) {
    stream_manager.out() << std::filesystem::current_path() << "\n";
    return 0;
}