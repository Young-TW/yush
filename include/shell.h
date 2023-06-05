#ifndef SHELL_H
#define SHELL_H

#include <filesystem>
#include <string>
#include <string_view>
#include <vector>
#include "cmds.h"
#include "env/system_var.h"
#include "stream_manager.hpp"
#include "variable_manager.h"

class Shell {
   public:
    Shell(std::istream& in, std::ostream& out, std::ostream& err);
    int run(bool);

   private:
    int output();

    int runtime_status;
    VariableManager variable_manager;
    StreamManager stream_manager;
};

#endif
