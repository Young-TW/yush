#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <string_view>
#include <vector>

class Command {
public:
    Command();
    Command(std::string_view cmd);

    int assign(std::string_view cmd);
    int assign(std::vector<std::string>& args);
    int assign(Command& cmd);

    int parse();
    int exec();

    bool empty();

    std::vector<std::string> arg();  // return arg

private:
    std::string command;
    std::vector<std::string> args;
    int runtime_status = 0;

    friend class Shell;
};

#endif