#ifndef CMD_YUSH_H
#define CMD_YUSH_H

#include <string>
#include <filesystem>
#include <fstream>

#include "stream_manager.hpp"
#include "variable_manager.h"
#include "commands/cmds.h"
#include "shell.h"

int cmd::yush(const std::vector<std::string>& arg, StreamManager& stream_manager, VariableManager& variable_manager) {
    if(arg.size() == 1){
        return Shell().run(stream_manager.in(), stream_manager.out(), stream_manager.err());;
    }else if(arg.size() == 2){
        std::filesystem::path target = std::filesystem::path(variable_manager.get("PWD")) / arg[1];
        if (!std::filesystem::is_regular_file(target)) {
            return 1;
        }

        std::ifstream fin(target);
        return Shell().run(fin, stream_manager.out(), stream_manager.err());
    }else{
        stream_manager.err() << variable_manager.get("COLOR_WARN") << "Error: argument size error." << variable_manager.get("COLOR_RESET");
        return 1;
    }
}

#endif