#ifndef CMD_TIME_H
#define CMD_TIME_H

#include <ctime>
#include <vector>

#include "stream_manager.hpp"
#include "variable_manager.h"
#include "commands/cmds.h"

int cmd::time(const std::vector<std::string>& arg, StreamManager& stream_manager, VariableManager& variable_manager){
    /*
    time_t curr_time;
    curr_time = time(NULL);

    char *tm = ctime(&curr_time);
    string i = tm;
    vector<string> time;
    while(true){
        time.push_back(i.substr(0, i.find(" ")));
        i = i.substr(i.find(" ") + 1, i.length());
        if (i.find(" ") == -1) {
            time.push_back(i);
            break;
        }
    }
    cout << time.at(4);
    */
    return 0;
}

#endif