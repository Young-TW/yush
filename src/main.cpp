#include <iostream>
#include <string>
#include <map>

#include "./commands/all_commands.h"
#include "./global_var.h"
#include "./parser.cpp"
#include "./call_function.cpp"
#include "./feature/arrow.cpp"
#include "./user.h"
#include "./feature/gen_path_str.h"

using namespace std;
using namespace std::filesystem;

int init(){
    cout << "Welcome to yush 0.1.0 \nHave a good time!\n- Young Studio";
    fs_current_path = current_user.home_dir;

    return 0;
}

int main(){
    init();
    while(exit_check == 0){
        cout << "\n\n" << theme["name"] << current_user.name << reset << " " << theme["path"] << gen_path_str() << reset << "\n⟩ ";
        getline(cin, input);
        input_past.push_back(input);
        place_input_past = input_past.size();
        parse_command(input);
        call_function(parsed_cmd);
    }
    return 0;
}