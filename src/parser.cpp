#include <string>
#include <map>
#include <vector>

#include "./commands/all_commands.h"
#include "./global_var.h"

using namespace std;

int parse_command(string i){
    parsed_cmd.clear();
    while(true){
        parsed_cmd.push_back(i.substr(0, i.find(" ")));
        i = i.substr(i.find(" ") + 1, i.length());
        if (i.find(" ") == -1) {
            parsed_cmd.push_back(i);
            break;
        }
    }
    return 0;
}
