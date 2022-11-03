#include <iostream>
#include <string>
#include <map>

#include "./commands/all_commands.h"
#include "./global_var.h"

using namespace std;

int parse_command(string c){
    if(c == "whoami") {
        whoami(userName);
    }
    else if(c == "help") {
        help(commands);
    }
    else if(c == "exit") {
        exit();
    }
    else if(c == "clear") {
        clear();
    }
    else{
        cout << "Unknown command.";
        return 1;
    }
    return 0;
}
