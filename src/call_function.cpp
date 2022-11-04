#include <string>
#include <map>
#include <vector>

#include "./commands/all_commands.h"
#include "./global_var.h"

using namespace std;

int call_function(vector<string> i){
    if(i.at(0) == "clear"){
        clear();
    }
    else if(i.at(0) == "echo"){
        echo(i);
    }
    else if(i.at(0) == "exit"){
        exit();
    }
    else if(i.at(0) == "help"){
        help(commands);
    }
    else if(i.at(0) == "whoami"){
        whoami(user_name);
    }
    else{
        unknown();
        return 1;
    }
    return 0;
}