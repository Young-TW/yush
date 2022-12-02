#include <iostream>
#include <string>
#include <map>

#include "./commands/all_commands.h"
#include "./global_var.h"
// #include "./parser.cpp"
// #include "./call_function.cpp"
#include "./feature/arrow.cpp"
#include "./user.h"
#include "./feature/gen_path_str.h"
#include "./feature/yush_script.h"

int init(std::filesystem::path yush_path){
    fs_current_path = yush_path;
    return 0;
}

int loop(){
    exit_check = 0;
    int runtime_status=0;
    while(exit_check == 0){
        std::cout << "\n\n" << theme["name"] << current_user.name << reset << " " << theme["path"] << gen_path_str() << reset;
        if(runtime_status == 1){
            std::cout << theme["warn"] << "\n⟩ " << reset;
        }else{
            std::cout << "\n⟩ ";
        }
        getline(std::cin, input);
        input_past.push_back(input);
        place_input_past = input_past.size();
        parse_command(input);
        runtime_status = call_function(parsed_cmd);
    }
    return exit_check;
}

int main(int argc, char *argv[]){
    if(argc > 1){
        for(int target_index=0;target_index<argc;target_index++){
            init(argv[0]);
            run_yush_script(std::filesystem::path(argv[target_index]));
        }
    }else if(argc == 1){
        std::cout << "yush 0.1.0\n- Young Studio";
        init(argv[0]);
        loop();
    }
    return 0;
}

