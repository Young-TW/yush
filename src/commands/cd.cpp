#ifndef CMD_CD_H
#define CMD_CD_H

#include <string>
#include <filesystem>

#include "stream_manager.hpp"
#include "variable_manager.h"
#include "commands/cmds.h"

static int cd_single(StreamManager& stream_manager, std::string_view path, std::filesystem::path& current_path) {
    if (path == "..") {
        current_path = current_path.parent_path();
        return 0;
    } else if (path == "/") {
        current_path = current_path.root_path();
        return 0;
    // } else if (path == "~") {
    //     current_path = current_user.home_dir;
    //     return 0;
    } else if (std::filesystem::is_directory(current_path.append(path))) {
        return 0;
    } else {
        stream_manager.err() << '`' << path << "` is not a directory.\n";
        return 1;
    }
    return 0;
}

int cmd::cd(const std::vector<std::string>& arg, StreamManager& stream_manager, VariableManager& variable_manager) {
    if (arg.size() != 2) {
        return 1;
    }

    std::filesystem::path current_path(variable_manager.get("PWD"));
    std::string_view path = arg[1];

    for (size_t i = 0; i < path.size();) {
        auto slash = path.find('/', i);
        if (slash == std::string::npos) {
            slash = path.size();
        }
        if (cd_single(stream_manager, path.substr(i, slash), current_path)) {
            return 1;
        }
        i = slash + 1;
    }

    variable_manager.set("PWD", current_path.string());
    stream_manager.out() << variable_manager.get("PWD");
    return 0;
}

#endif