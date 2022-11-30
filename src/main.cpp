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

int init(){
    std::cout << "yush 0.1.0\n- Young Studio";
    fs_current_path = current_user.home_dir;
    return 0;
}

int loop(){
    int runtime_status=0;
    while(exit_check == 0){
        std::cout << "\n\n" << theme["name"] << current_user.name << reset << " " << theme["path"] << gen_path_str() << reset;
        if(runtime_status == 1){
            std::cout << theme["warn"] << "\n⟩ " << reset;
        }else{
            std::cout << "\n⟩ ";
        }
        getline(cin, input);
        input_past.push_back(input);
        place_input_past = input_past.size();
        parse_command(input);
        runtime_status = call_function(parsed_cmd);
    }
    return exit_check;
}

int main(){
    init();
    loop();
    return 0;
}