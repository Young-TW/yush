#include <iostream>
#include <string>
#include <map>

#include "./commands/all_commands.h"
#include "./global_var.h"
#include "./parser.cpp"
#include "./call_function.cpp"

using namespace std;

int main(){
    cout << "Welcome to yush 0.0.1 \n Copyright (c) 2022 Young Studio.";
    string input;
    
    while(exit_check == 0){
        cout << "\n\n";
        cout << user_name << "> ";
        getline(cin, input);
        parse_command(input);
        call_function(parsed_cmd);
    }
    return 0;
}