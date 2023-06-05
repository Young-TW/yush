#include "cmds.h"

#include <filesystem>
#include <fstream>
#include <string>

int cmds::cat(const std::vector<std::string>& arg,
              StreamManager& stream_manager,
              VariableManager& variable_manager) {
    if (arg.size() != 2) {
        stream_manager.err() << "Argument size error.\n";
        return 1;
    }

    auto target_file =
        std::filesystem::path(variable_manager.get("PWD")) / arg[1];
    if (!std::filesystem::is_regular_file(target_file)) {
        stream_manager.err() << "File is not exists.\n";
        return 1;
    }

    std::ifstream fin(target_file);
    std::string str((std::istreambuf_iterator<char>(fin)),
                    std::istreambuf_iterator<char>());
    stream_manager.out() << str;

    return 0;
}
