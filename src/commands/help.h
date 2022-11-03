#ifndef CMD_HELP_H__
#define CMD_HELP_H__

#include <iostream>
#include <map>
using namespace std;

int help(map<string, string> commands){
    for(const auto& c : commands){
        cout << "\n" << c.first << "\t : " << c.second;
    }
    return 0;
}

#endif