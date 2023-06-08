#include "cmds.h"

#include <filesystem>
#include <fstream>
#include <string>

int cmds::cat(const std::vector<std::string>& arg,
              StreamManager& stream,
              VariableManager& vars) {
    if (arg.size() != 2) {
        stream.err() << "Argument size error.\n";
        return 1;
    }

    auto target_file =
        std::filesystem::path(vars.get("PWD")) / arg[1];
    if (!std::filesystem::is_regular_file(target_file)) {
        stream.err() << "File is not exists.\n";
        return 1;
    }

    std::ifstream fin(target_file);
    std::string str((std::istreambuf_iterator<char>(fin)),
                    std::istreambuf_iterator<char>());
    stream.out() << str;

    return 0;
}
