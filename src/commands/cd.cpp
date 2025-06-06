#include <filesystem>
#include <string>

#include "fmt/format.h"

#include "shell.h"

static int cd_single(std::string_view path, std::filesystem::path& current_path,
                     VariableManager& vars) {
    if (path == ".") {
        return 0;
    } else if (path == "..") {
        current_path = current_path.parent_path();
        return 0;
    } else if (path == "~") {
        current_path = vars.get("HOME");
        return 0;
    }

    std::filesystem::path new_path = current_path / std::string(path);
    if (std::filesystem::is_directory(new_path)) {
        current_path = new_path;
        return 0;
    }

    fmt::print(stderr, "cd: {} is not a directory.\n", path);
    return 1;
}

int Shell::cmd_cd(const std::vector<std::string>& arg) {
    if (arg.size() != 2) {
        return 1;
    }

    std::filesystem::path current_path(std::filesystem::current_path());
    std::string_view path = arg[1];

    if (path[0] == '/') {
        current_path = current_path.root_path();
    }

    for (size_t i = 0; i < path.size();) {
        auto slash = path.find('/', i);
        if (slash == std::string::npos) {
            slash = path.size();
        }
        if (cd_single(path.substr(i, slash - i), current_path, vars)) {
            return 1;
        }
        i = slash + 1;
    }

    std::filesystem::current_path(current_path.lexically_normal());
    return 0;
}
