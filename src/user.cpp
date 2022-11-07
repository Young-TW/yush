#ifndef USER_H__
#define USER_H__

#include <string>
#include <filesystem>
#include <vector>

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
    home_dir = path(string("/Users/").append(user_name));
    name = user_name;
}

User::~User(){
    // User_list.erase(User);
}

#endif