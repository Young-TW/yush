#include <string>
#include <filesystem>
#include <fstream>

#include "stream_manager.hpp"
#include "variable_manager.h"
#include "cmds.h"
#include "shell.h"

int cmds::yush(const std::vector<std::string>& arg, StreamManager& stream_manager, VariableManager& variable_manager) {
    if (arg.size() == 1) {
        return Shell().run(stream_manager.in(), stream_manager.out(), stream_manager.err(), true);
    } else if (arg.size() == 2) {
        std::filesystem::path target = std::filesystem::current_path() / arg[1];
        if (!std::filesystem::is_regular_file(target)) {
            return 1;
        }

        std::ifstream fin(target);
        return Shell().run(fin, stream_manager.out(), stream_manager.err(), false);
    } else {
        stream_manager.err() << "Argument size error.\n";
        return 1;
    }
}