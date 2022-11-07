#include <iostream>
#include <string>
#include <map>

#include "./commands/all_commands.h"
#include "./global_var.h"
#include "./parser.cpp"
#include "./call_function.cpp"
#include "./feature/arrow.cpp"
#include "./user.cpp"

using namespace std;
using namespace std::filesystem;

int main(){
    cout << "Welcome to yush 0.0.1 \nCopyright (c) 2022 Young Studio.";
    User Young = User("Young");
    fs_current_path = User_list.at(current_user).home_dir;
    while(exit_check == 0){
        cout << "\n\n";
        cout << User_list.at(current_user).name << " ";
        if(fs_current_path.u8string() == User_list.at(current_user).home_dir.u8string()){
            cout << "~";
        }else{
            cout << fs_current_path.u8string();
        }
        cout << "> ";
        getline(cin, input);
        input_past.push_back(input);
        place_input_past = input_past.size();
        parse_command(input);
        call_function(parsed_cmd);
    }
    return 0;
}