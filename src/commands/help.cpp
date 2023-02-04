#ifndef CMD_HELP_H
#define CMD_HELP_H

#include <map>

#include "stream_manager.hpp"
#include "variable_manager.h"
#include "commands/cmds.h"

static const std::map<std::string, std::string> commands ={
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
    {"time"   , "display current time"},
    {"touch"  , "create an empty file"},
    {"whoami" , "print user name"},
    {"yush"   , "open new yush or run yush script file"},
};

int cmd::help(const std::vector<std::string>& arg, StreamManager& stream_manager, VariableManager& variable_manager){
    for(const auto& c : commands){
        stream_manager.out() << "\n" << c.first << "\t : " << c.second;
    }
    return 0;
}

#endif