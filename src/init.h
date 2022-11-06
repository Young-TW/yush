#ifndef INIT_H__
#define INIT_H__

#include <string>

#include "./global_var.h"
#include "./env/system.h"

using namespace std;

int init(){
    system();

    return 0;
}

#endif