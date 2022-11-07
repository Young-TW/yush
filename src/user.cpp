#ifndef USER_H__
#define USER_H__

#include <string>
#include <filesystem>

using namespace std;

class User{
    public:
        User();
        User(string user_name);
        string name;
        filesystem::path home_dir;
};

User::User(string user_name){
    home_dir = string("/Users/").append(user_name);
}

#endif