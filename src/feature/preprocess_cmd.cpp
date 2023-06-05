#include <string>

std::string preprocess_cmd(const std::string& cmd) {
    if (cmd.empty()) {
        return "";
    }

    size_t flag = 0;
    while (cmd[flag] == ' ') {
        flag++;
    }

    std::string ans;
    for (size_t i = flag; i < cmd.size(); i++) {
        if (cmd[i] == ' ') {
            if (i + 1 < cmd.size() && cmd[i + 1] == ' ') {
                continue;
            }
        }
        ans += cmd[i];
    }

    return ans;
}