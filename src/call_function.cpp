#include <string>
#include <map>
#include <vector>

#include "./commands/all_commands.h"
#include "./global_var.h"

using namespace std;

int call_function(vector<string> i){
    if(i.at(0) == "cat"){
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
    else if(i.at(0) == "pwd"){
        return pwd();
    }
    else if(i.at(0) == "time"){
        return time();
    }
    else if(i.at(0) == "useradd"){
        return useradd();
    }
    else if(i.at(0) == "userdel"){
        return userdel();
    }
    else if(i.at(0) == "whoami"){
        return whoami(Young.name);
    }
    else{
        unknown();
        return 1;
    }
    return 0;
}