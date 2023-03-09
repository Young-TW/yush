#include <filesystem>

#include "stream_manager.hpp"
#include "variable_manager.h"
#include "cmds.h"

int cmd::ls(const std::vector<std::string>& arg, StreamManager& stream_manager, VariableManager& variable_manager) {
    std::filesystem::path current_path(variable_manager.get("PWD"));

    if (!std::filesystem::exists(current_path)) {
        stream_manager.err() << "This directory is not exists.\n";
        return 1;
    }

    std::filesystem::directory_iterator list(current_path);
    for (auto& it : list) {
        if (it.path().filename().string()[0] != '.') {
            if (it.is_directory()) {
                stream_manager.out() << variable_manager.get("COLOR_DIR") << it.path().filename().string() << variable_manager.get("COLOR_RESET") << '/';
            } else {
                stream_manager.out() << it.path().filename().string();
            }
            stream_manager.out() << "\t";
        }
    }

    stream_manager.out() << "\n";
    return 0;
}

int cmd::la(const std::vector<std::string>& arg, StreamManager& stream_manager, VariableManager& variable_manager) {
    std::filesystem::path current_path(variable_manager.get("PWD"));

    if (!std::filesystem::exists(current_path)) {
        return 1;
    }

    std::filesystem::directory_iterator list(current_path);
    for (auto& it : list) {
        if (it.is_directory()) {
            stream_manager.out() << variable_manager.get("COLOR_DIR") << it.path().filename().string() << variable_manager.get("COLOR_RESET") << '/';
        } else {
            stream_manager.out() << it.path().filename().string();
        }
        stream_manager.out() << "\t";
    }

    stream_manager.out() << "\n";
    return 0;
}