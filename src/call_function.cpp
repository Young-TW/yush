#include <string>
#include <map>
#include <vector>

#include "./commands/all_commands.h"
#include "./global_var.h"

int call_function(std::vector<string> i){
    if(i.at(0) == "alias"){
        return alias(i.at(1));
    }
    else if(i.at(0) == "cat"){
        return cat(i.at(1));
    }
    else if(i.at(0) == "cd"){
        return cd(i.at(1));
    }
    else if(i.at(0) == "clear"){
        return clear();
    }
    else if(i.at(0) == "date"){
        return date();
    }
    else if(i.at(0) == "echo"){
        return echo(i);
    }
    else if(i.at(0) == "exit"){
        return exit();
    }
    else if(i.at(0) == "help"){
        return help(commands);
    }
    else if(i.at(0) == "la"){
        return la();
    }
    else if(i.at(0) == "ls"){
        return ls();
    }
    else if(i.at(0) == "mkdir"){
        if(i.at(1) == string("")){
            return mkdir();
        }
        return mkdir(i.at(1));
    }
    else if(i.at(0) == "pwd"){
        return pwd();
    }
    else if(i.at(0) == "rm"){
        return rm(i.at(1), i.at(2));
    }
    else if(i.at(0) == "su"){
        if(i.at(1) == ""){
            return su();
        }else{
            return su(i.at(1));
        }
    }
    else if(i.at(0) == "time"){
        return time();
    }else if(i.at(0) == "touch"){
        return touch(i.at(1));
    }
    else if(i.at(0) == "useradd"){
        return useradd();
    }
    else if(i.at(0) == "userdel"){
        return userdel();
    }
    else if(i.at(0) == "whoami"){
        return whoami(current_user.name);
    }
    else{
        return unknown(i.at(0));
    }
    return 0;
}