#ifndef _FEATURE_GEN_PATH_STR_H_
#define _FEATURE_GEN_PATH_STR_H_

#include <string>

#include "src/global_var.h"

std::string gen_path_str(){
    std::string s = "~";
    std::string n = current_user.home_dir.string();
    std::string m = fs_current_path.string();
    for(size_t i=0; i<n.length(); i++){
        if(n[i] != m[i]){
            s = m;
            return s;
        }
    }
    m.erase(m.begin() ,m.begin() + n.length());
    s.append(m);
    return s;
}

#endif