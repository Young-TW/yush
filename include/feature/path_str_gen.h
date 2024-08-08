#ifndef FEATURE_PATH_STR_GEN_H
#define FEATURE_PATH_STR_GEN_H

#include <filesystem>
#include <string>
#include <string_view>

std::string path_str_gen(std::string_view home_dir);
std::string reverse_path_str_gen(std::string_view home_dir, std::string_view pwd);

#endif
