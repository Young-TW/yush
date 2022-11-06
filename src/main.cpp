#include <iostream>
#include <string>
#include <map>
#include <thread>

#include "./commands/all_commands.h"
#include "./global_var.h"
#include "./parser.cpp"
#include "./call_function.cpp"
#include "./feature/arrow.cpp"

using namespace std;
using namespace std::filesystem;

int main(){
    cout << "Welcome to yush 0.0.1 \n Copyright (c) 2022 Young Studio.";
    while(exit_check == 0){
        cout << "\n\n";
        cout << user_name << " " << fs_current_path << "> ";
        // thread th_arrow(arrow);
        getline(cin, input);
        input_past.at(place_input_past) = input;
        place_input_past = input_past.size();
        parse_command(input);
        call_function(parsed_cmd);
    }
    return 0;
}