#include <string>
#include <filesystem>

#include "stream_manager.hpp"
#include "variable_manager.h"
#include "commands/cmds.h"

int cmd::rm(const std::vector<std::string>& arg, StreamManager& stream_manager, VariableManager& variable_manager){
    if(arg.at(1) == "-rf"){
        return !std::filesystem::remove(std::filesystem::path(variable_manager.get("PWD")) / arg.at(2));
    }else{
        return !std::filesystem::remove(std::filesystem::path(variable_manager.get("PWD")) / arg.at(1));
    }

    return 0;
}