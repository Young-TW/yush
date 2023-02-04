#ifndef CMD_DATE_H
#define CMD_DATE_H

#include <ctime>
#include <vector>
#include <string>

#include "stream_manager.hpp"
#include "variable_manager.h"
#include "commands/cmds.h"

int cmd::date(const std::vector<std::string>& arg, StreamManager& stream_manager, VariableManager& variable_manager) {
    /*
    time_t curr_time;
    curr_time = time(NULL);

    char *tm = ctime(&curr_time);
    string i = tm;
    vector<string> date;
    while(true){
        date.push_back(i.substr(0, i.find(" ")));
        i = i.substr(i.find(" ") + 1, i.length());
        if (i.find(" ") == -1) {
            date.push_back(i);
            break;
        }
    }
    date.at(5).pop_back();
    cout << date.at(5) << " " << date.at(1) << " " << date.at(3);
    */
    return 0;
}

#endif