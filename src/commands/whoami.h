#ifndef CMD_WHOAMI_H__
#define CMD_WHOAMI_H__

#include <iostream>
#include <string>
using namespace std;

int whoami(string userName){
    cout << userName;
    return 0;
}

#endif