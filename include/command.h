#ifndef COMMAND_H
#define COMMAND_H

#include <vector>
#include <string>
#include <string_view>

class Command {
    public:
        Command();
        Command(std::string_view cmd);

        int assign(std::string_view cmd);
        int assign(std::vector<std::string>& args);

        int parse();
        int exec();

        bool empty();

        std::vector<std::string> arg(); // return arg

    private:
        enum return_value {
            PID_FAILURE = -1,
            SUCCESS = 0,
            FAILURE = 1,
            EXIT = 2,
            NOT_FOUND = 127,
        };
        std::string command;
        std::vector<std::string> args;
        int runtime_status = 0;

    friend class Shell;
};

#endif