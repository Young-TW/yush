#ifndef CMD_HELP_H
#define CMD_HELP_H

#include <iostream>
#include <map>

const std::map<std::string, std::string> commands ={
    {"alias"  , "set command into another name"},
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
    {"yush"   , "open new yush or run yush script file"},
};

int cmd::help(std::map<std::string, std::string> commands){
    for(const auto& c : commands){
        std::cout << "\n" << c.first << "\t : " << c.second;
    }
    return 0;
}

#endif