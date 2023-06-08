#include "cmds.h"

#include <filesystem>
#include <fstream>

int cmds::touch(const std::vector<std::string>& arg,
                StreamManager& stream,
                VariableManager& vars) {
    if (arg.size() != 2) {
        stream.err() << "Argument size error.\n";
        return 1;
    }

    auto new_file = std::filesystem::current_path() / arg[1];
    if (std::filesystem::exists(new_file)) {
        stream.err() << "File already exists.\n";
        return 1;
    }

    std::ofstream fout(new_file);
    return 0;
}
