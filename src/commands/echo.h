#ifndef CMD_ECHO_H__
#define CMD_ECHO_H__

#include <iostream>
#include <vector>
#include <string>
using namespace std;

int echo(vector<string> i){
    for(int j=1;j<i.size();j++){
        cout << i.at(j) << " ";
    }
    return 0;
}

#endif