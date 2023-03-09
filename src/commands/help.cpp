#include <map>

#include "stream_manager.hpp"
#include "variable_manager.h"
#include "cmds.h"

static const std::map<std::string, std::string> commands = {
    {"alias"  , "set command into another name"},
    {"cat"    , "print content of selected file"},
    {"cd"     , "change current path"},
    {"cp"     , "copy selected file"},
    {"clear"  , "clear texts"},
    {"date"   , "display current date & time"},
    {"echo"   , "display texts or using $ to display varible"},
    {"exit"   , "exit shell"},
    {"help"   , "print all commands"},
    {"ls"     , "display file and directory in current path"},
    {"mkdir"  , "create directory in current path"},
    {"mv"     , "move selected file"},
    {"pwd"    , "display current path"},
    {"rm"     , "remove selected file or directory"},
    {"touch"  , "create an empty file"},
    {"whoami" , "print user name"},
    {"yush"   , "open new yush or run yush script file"},
};

int cmd::help(const std::vector<std::string>& arg, StreamManager& stream_manager, VariableManager& variable_manager) {
    for (const auto& c : commands) {
        stream_manager.out() << "\n" << c.first << "\t : " << c.second;
    }

    stream_manager.out() << "\n";

    return 0;
}