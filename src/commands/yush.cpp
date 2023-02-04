#ifndef CMD_YUSH_H
#define CMD_YUSH_H

#include <string>
#include <filesystem>
#include <fstream>

#include "commands/cmds.h"
#include "shell.h"

int cmd::yush(const std::vector<std::string>& arg, std::istream& is, std::ostream& os, std::map<std::string, std::string>& variables) {
    if(arg.size() == 1){
        return Shell().run();;
    }else if(arg.size() == 2){
        std::filesystem::path target = std::filesystem::path(variables.at("PWD")) / arg[1];
        if (!std::filesystem::is_regular_file(target)) {
            return 1;
        }

        std::ifstream fin(target);
        return Shell(fin).run();
    }else{
        os << variables.at("COLOR_WARN") << "Error: argument size error." << variables.at("COLOR_RESET");
        return 1;
    }
}

#endif