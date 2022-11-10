#include <iostream>
#include <string>
#include <map>

#include "./commands/all_commands.h"
#include "./global_var.h"
#include "./parser.cpp"
#include "./call_function.cpp"
#include "./feature/arrow.cpp"
#include "./user.cpp"
#include "./feature/gen_path_str.h"
#include "./feature/color_text.h"
#include "./feature/theme.h"

using namespace std;
using namespace std::filesystem;

int main(){
    cout << "Welcome to yush 0.0.1 \nCopyright (c) 2022 Young Studio.";
    fs_current_path = current_user.home_dir;
    while(exit_check == 0){
        cout << "\n\n" << theme_def["name_color"] << current_user.name << reset << " " << theme_def["path_color"] << gen_path_str() << reset << "\n⟩ ";
        getline(cin, input);
        input_past.push_back(input);
        place_input_past = input_past.size();
        parse_command(input);
        call_function(parsed_cmd);
    }
    return 0;
}