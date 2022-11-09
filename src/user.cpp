#ifndef USER_H__
#define USER_H__

#include <string>
#include <filesystem>
#include <vector>
#include <algorithm>

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
    #ifdef __APPLE__
        home_dir = path(string("/Users/").append(user_name));
    #elif __Linux__
        transform(user_name.begin(), user_name.end(), user_name.begin(), [](unsigned char c){ return std::tolower(c); });
        home_dir = path(string("/home/").append(tolower(user_name)));
    #elif __Unix
        home_dir = path(string("/Users/").append(user_name));
    #else
        home_dir = path(string("C://Users/").append(user_name));
    #endif
}

User::~User(){
    // User_list.erase(User);
}

#endif