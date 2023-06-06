#include <unistd.h>

#include <string>
#include <vector>

#include "cmds.h"
#include "feature/string_parser.h"
#include "shell.h"

int Shell::exec_shell_builtin(const std::vector<std::string>& arg) {
    using namespace cmds;
    static const std::unordered_map<std::string, decltype(&alias)> command_map{
        {"alias", alias}, {"cat", cat},
        {"cd", cd},       {"clear", clear},
        {"cp", cp},       {"date", date},
        {"echo", echo},   {"function", function},
        {"help", help},   {"la", la},
        {"ls", ls},       {"mkdir", mkdir},
        {"mv", mv},       {"pwd", pwd},
        {"rm", rm},       {"set", set},
        {"touch", touch}, {"whoami", whoami},
        {"yush", yush},
    };

    auto command_it = command_map.find(arg[0]);
    if (command_it != command_map.cend()) {
        return command_it->second(arg, stream_manager, variable_manager);
    }

    return 127;
}

int Shell::exec_cmd(const std::string current_command,
             const std::vector<std::string>& arg) {
    if (current_command.empty()) {
        return 0;
    }

    int shell_builtin_ans =
        exec_shell_builtin(arg);

    if (shell_builtin_ans != 127) {
        return shell_builtin_ans;
    }

    std::vector<std::string> cmd_paths =
        string_parser(variable_manager.get("PATH"), ':');

    for (const auto& cmd : cmd_paths) {
        std::filesystem::path cmd_path = cmd / std::filesystem::path(arg[0]);

        if (std::filesystem::exists(cmd_path) &&
            std::filesystem::is_regular_file(cmd_path)) {
            return std::system(current_command.c_str());
        }
    }

    stream_manager.err() << "command `" << arg[0] << "` not found.\n";

    return 127;
}
