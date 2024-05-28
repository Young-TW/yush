#include <filesystem>
#include <string>
#include <string_view>

#include "feature/path_str_gen.h"

std::string path_str_gen(std::string_view home_dir) {
    std::string pwd =
        std::filesystem::current_path().lexically_normal().string();
    if (pwd.substr(0, home_dir.size()) == home_dir) {
        return std::string("~") +
               std::string(pwd.substr(home_dir.size(), std::string_view::npos));
    } else {
        return std::string(pwd);
    }
}

std::string reverse_path_str_gen(std::string_view home_dir,
                                 std::string_view pwd) {
    if (pwd.substr(0, 1) == "~") {
        return std::string(home_dir) +
               std::string(pwd.substr(1, std::string_view::npos));
    } else {
        return std::string(pwd);
    }
}