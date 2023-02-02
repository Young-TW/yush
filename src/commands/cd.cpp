#ifndef CMD_CD_H
#define CMD_CD_H

#include <string>
#include <filesystem>

#include "commands/cmds.h"

static int cd_single(std::istream& is, std::ostream& os, std::string_view path, std::filesystem::path& current_path) {
    if (path == "..") {
        current_path = current_path.parent_path();
        return 0;
    } else if (path == "/") {
        current_path = current_path.root_path();
        return 0;
    // } else if (path == "~") {
    //     current_path = current_user.home_dir;
    //     return 0;
    } else if (is_directory(current_path.append(path))) {
        return 0;
    } else {
        os << path << " is not a directory";
        return 1;
    }
    return 0;
}

int cmd::cd(const std::vector<std::string>& arg, std::istream& is, std::ostream& os, std::map<std::string, std::string>& variables) {
    if (arg.size() != 2) {
        return 1;
    }

    std::filesystem::path current_path(variables.at("PWD"));
    std::filesystem::path current_path_backup = current_path;
    std::string_view path = arg[1];

    for (size_t i = 0; i < path.size();) {
        auto slash = path.find('/', i);
        if (slash == std::string::npos) {
            slash = path.size();
        }
        if (cd_single(is, os, path.substr(i, slash), current_path)) {
            variables.at("PWD") = current_path_backup.string();
            return 1;
        }
        i = slash + 1;
    }

    variables.at("PWD") = current_path.string();
    return 0;
}

#endif