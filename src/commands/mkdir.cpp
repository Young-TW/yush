#include "cmds.h"

#include <filesystem>

int cmds::mkdir(const std::vector<std::string>& arg,
                StreamManager& stream,
                VariableManager& vars) {
    if (arg.size() != 2) {
        stream.err() << "Argument size error.\n";
        return 1;
    }

    auto new_directory = std::filesystem::current_path() / arg[1];
    if (!exists(new_directory)) {
        std::filesystem::create_directories(new_directory);
        return 0;
    } else {
        stream.err() << "Directory already exists.\n";
        return 1;
    }
}
