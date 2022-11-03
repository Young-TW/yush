#include <iostream>
#include <string>
#include <map>

#include "./commands/all_commands.h"
#include "./global_var.h"
#include "./parser.cpp"

using namespace std;

int main(){
    cout << "Welcome to yush 0.0.1 \n Copyright (c) 2022 Young Studio.";
    string input;
    
    while(exit_check == 0){
        cout << "\n\n";
        cout << userName << "> ";
        getline(cin, input);
        parse_command(input);
    }
    return 0;
}