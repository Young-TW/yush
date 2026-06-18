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

    std::filesystem::path new_path{current_path / std::string(path)};
    if (std::filesystem::is_directory(new_path)) {
        current_path = new_path;
        return 0;
    }

    fmt::print(stderr, "cd: {} is not a directory.\n", path);
    return 1;
}

int Shell::cmd_cd(const std::vector<std::string>& arg) {
    std::filesystem::path old_path(std::filesystem::current_path());
    std::filesystem::path current_path{old_path};

    std::string target;
    bool report{false};
    if (arg.size() < 2) {
        target = std::string(vars.get("HOME"));
    } else if (arg[1] == "-") {
        std::string_view old{vars.get("OLDPWD")};
        if (old.empty()) {
            fmt::print(stderr, "cd: OLDPWD not set\n");
            return 1;
        }
        target = std::string(old);
        report = true;
    } else {
        target = arg[1];
    }

    std::string_view path{target};

    if (!path.empty() && path[0] == '/') {
        current_path = current_path.root_path();
    }

    for (size_t i{0}; i < path.size();) {
        auto slash{path.find('/', i)};
        if (slash == std::string::npos) {
            slash = path.size();
        }
        if (cd_single(path.substr(i, slash - i), current_path, vars)) {
            return 1;
        }
        i = slash + 1;
    }

    current_path = current_path.lexically_normal();
    std::filesystem::current_path(current_path);
    vars.set("OLDPWD", old_path.string());
    vars.set("PWD", current_path.string());
    if (report) {
        fmt::print("{}\n", current_path.string());
    }
    return 0;
}
