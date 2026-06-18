#include <string>

#include "fmt/format.h"

#include "shell.h"

int Shell::cmd_export(const std::vector<std::string>& arg) {
    if (arg.size() < 2) {
        for (const auto& entry : this->vars.environment()) {
            fmt::print("export {}\n", entry);
        }
        return 0;
    }

    for (std::size_t i{1}; i < arg.size(); ++i) {
        auto eq{arg[i].find('=')};
        if (eq == std::string::npos) {
            this->vars.mark_exported(arg[i]);
        } else {
            this->vars.set(arg[i].substr(0, eq), arg[i].substr(eq + 1));
            this->vars.mark_exported(arg[i].substr(0, eq));
        }
    }

    return 0;
}
