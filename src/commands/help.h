#ifndef _CMD_HELP_H_
#define _CMD_HELP_H_

#include <iostream>
#include <map>

std::map<std::string, std::string> commands ={
    {"cat"    , "print content of file"},
    {"cd"     , "change current path"},
    {"clear"  , "clear texts"},
    {"date"   , "display current date"},
    {"echo"   , "display texts or using $ to display varible"},
    {"exit"   , "exit shell"},
    {"help"   , "print all commands"},
    {"ls"     , "display file and directory in current path"},
    {"mkdir"  , "create directory in current path"},
    {"pwd"    , "display current path"},
    {"rm"     , "remove selected file or directory"},
    {"su"     , "switch to another user"},
    {"time"   , "display current time"},
    {"touch"  , "create an empty file"},
    {"useradd", "add another user"},
    {"userdel", "delete selected user"},
    {"whoami" , "print user name"},
};

int help(std::map<std::string, std::string> commands){
    for(const auto& c : commands){
        std::cout << "\n" << c.first << "\t : " << c.second;
    }
    return 0;
}

#endif