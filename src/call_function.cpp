#include <string>
#include <map>
#include <vector>

#include "src/commands/all_commands.h"
#include "src/global_var.h"

using namespace cmd;

int call_function(std::vector<std::string> input){
    if(input.at(0) == "alias"){
        return alias(input.at(1));
    }
    else if(input.at(0) == "cat"){
        return cat(input.at(1));
    }
    else if(input.at(0) == "cd"){
        return cd(input.at(1));
    }
    else if(input.at(0) == "clear"){
        return clear();
    }
    else if(input.at(0) == "date"){
        return date();
    }
    else if(input.at(0) == "echo"){
        return echo(input);
    }
    else if(input.at(0) == "exit"){
        return exit();
    }
    else if(input.at(0) == "help"){
        return help(commands);
    }
    else if(input.at(0) == "la"){
        return la();
    }
    else if(input.at(0) == "ls"){
        return ls();
    }
    else if(input.at(0) == "mkdir"){
        if(input.at(1) == std::string("")){
            return mkdir();
        }
        return mkdir(input.at(1));
    }
    else if(input.at(0) == "pwd"){
        return pwd();
    }
    else if(input.at(0) == "rm"){
        return rm(input.at(1), input.at(2));
    }
    else if(input.at(0) == "su"){
        if(input.at(1) == ""){
            return su();
        }else{
            return su(input.at(1));
        }
    }
    else if(input.at(0) == "time"){
        return time();
    }else if(input.at(0) == "touch"){
        return touch(input.at(1));
    }
    else if(input.at(0) == "useradd"){
        return useradd();
    }
    else if(input.at(0) == "userdel"){
        return userdel();
    }
    else if(input.at(0) == "whoami"){
        return whoami(current_user.name);
    }
    else if(input.at(0) == "yush"){
        if(input.at(1) == ""){
            return yush();
        }else{
            return yush(input.at(1));
        }
    }
    else{
        return unknown(input.at(0));
    }
    return 0;
}