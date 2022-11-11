#ifndef USER_H__
#define USER_H__

#include <string>
#include <filesystem>

#include "./global_var.h"

using namespace std;
using namespace std::filesystem;

class User{
    public:
        User();
        User(string user_name);
        string name;
        path home_dir;
        ~User();
};

User::User(string user_name){
    name = user_name;
    if(name == "virtual_user"){
        this -> home_dir = "..";
        return;
    }
    #ifdef __APPLE__
        home_dir = path(string("/Users/").append(user_name));
    #elif __linux__
        home_dir = path(string("/home/").append(user_name));
    #elif __unix__
        home_dir = path(string("/Users/").append(user_name));
    #else
        home_dir = path(string("C://Users/").append(user_name));
    #endif
    return;
}

User::~User(){
    // User_list.erase(User);
    return;
}

#endif