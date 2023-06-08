#include "cmds.h"

#include <filesystem>

int cmds::pwd(const std::vector<std::string>& arg,
              StreamManager& stream,
              VariableManager& vars) {
    stream.out() << std::filesystem::current_path() << "\n";
    return 0;
}
