#include "cmds.h"

#include <filesystem>

int cmds::ls(const std::vector<std::string>& arg, StreamManager& stream_manager,
             VariableManager& variable_manager) {
    if (!std::filesystem::exists(std::filesystem::current_path())) {
        stream_manager.err() << "This directory is not exists.\n";
        return 1;
    }

    std::filesystem::directory_iterator list(std::filesystem::current_path());
    for (auto& it : list) {
        if (it.path().filename().string()[0] != '.') {
            if (it.is_directory()) {
                stream_manager.out()
                    << variable_manager.get("COLOR_DIR")
                    << it.path().filename().string()
                    << variable_manager.get("COLOR_RESET") << '/';
            } else {
                stream_manager.out() << it.path().filename().string();
            }
            stream_manager.out() << "\t";
        }
    }

    stream_manager.out() << "\n";
    return 0;
}

int cmds::la(const std::vector<std::string>& arg, StreamManager& stream_manager,
             VariableManager& variable_manager) {
    if (!std::filesystem::exists(std::filesystem::current_path())) {
        return 1;
    }

    std::filesystem::directory_iterator list(std::filesystem::current_path());
    for (auto& it : list) {
        if (it.is_directory()) {
            stream_manager.out() << variable_manager.get("COLOR_DIR")
                                 << it.path().filename().string()
                                 << variable_manager.get("COLOR_RESET") << '/';
        } else {
            stream_manager.out() << it.path().filename().string();
        }
        stream_manager.out() << "\t";
    }

    stream_manager.out() << "\n";
    return 0;
}
