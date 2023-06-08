#include "cmds.h"

#include <filesystem>

int cmds::ls(const std::vector<std::string>& arg, StreamManager& stream,
             VariableManager& vars) {
    if (!std::filesystem::exists(std::filesystem::current_path())) {
        stream.err() << "This directory is not exists.\n";
        return 1;
    }

    std::filesystem::directory_iterator list(std::filesystem::current_path());
    for (auto& it : list) {
        if (it.path().filename().string()[0] != '.') {
            if (it.is_directory()) {
                stream.out()
                    << vars.get("COLOR_DIR")
                    << it.path().filename().string()
                    << vars.get("COLOR_RESET") << '/';
            } else {
                stream.out() << it.path().filename().string();
            }
            stream.out() << "\t";
        }
    }

    stream.out() << "\n";
    return 0;
}

int cmds::la(const std::vector<std::string>& arg, StreamManager& stream,
             VariableManager& vars) {
    if (!std::filesystem::exists(std::filesystem::current_path())) {
        return 1;
    }

    std::filesystem::directory_iterator list(std::filesystem::current_path());
    for (auto& it : list) {
        if (it.is_directory()) {
            stream.out() << vars.get("COLOR_DIR")
                                 << it.path().filename().string()
                                 << vars.get("COLOR_RESET") << '/';
        } else {
            stream.out() << it.path().filename().string();
        }
        stream.out() << "\t";
    }

    stream.out() << "\n";
    return 0;
}
