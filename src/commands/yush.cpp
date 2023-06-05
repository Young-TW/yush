#include "cmds.h"

#include <filesystem>
#include <fstream>
#include <string>
#include "shell.h"

int cmds::yush(const std::vector<std::string>& arg,
               StreamManager& stream_manager,
               VariableManager& variable_manager) {
    if (arg.size() == 1) {
        return Shell(stream_manager.in(), stream_manager.out(),
                     stream_manager.err())
            .run(true);
    } else if (arg.size() == 2) {
        std::filesystem::path target = std::filesystem::current_path() / arg[1];
        if (!std::filesystem::is_regular_file(target)) {
            return 1;
        }

        std::ifstream fin(target);
        return Shell(fin, stream_manager.out(), stream_manager.err())
            .run(false);
    } else {
        stream_manager.err() << "Argument size error.\n";
        return 1;
    }
}
