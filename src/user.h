#ifndef _USER_H_
#define _USER_H_

#include <string>
#include <filesystem>

class User{
    public:
        User();
        User(std::string user_name);
        std::string name;
        std::filesystem::path home_dir;
        ~User();
};

User::User(std::string user_name){
    name = user_name;
    if(name == "virtual_user"){
        this -> home_dir = "..";
        return;
    }
    #ifdef __APPLE__
        home_dir = std::filesystem::path(std::string("/Users/").append(user_name));
    #elif __linux__
        home_dir = std::filesystem::path(std::string("/home/").append(user_name));
    #elif __unix__
        home_dir = std::filesystem::path(std::string("/Users/").append(user_name));
    #else
        home_dir = std::filesystem::path(std::string("C://Users/").append(user_name));
    #endif
    return;
}

User::~User(){
    // User_list.erase(User);
    return;
}

#endif