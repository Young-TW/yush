#ifndef GEN_PATH_STR__
#define GEN_PATH_STR__

#include <string>

#include "../global_var.h"

string gen_path_str(){
    string s = "~";
    string n = User_list.at(current_user).home_dir.u8string();
    string m = fs_current_path.u8string();
    for(size_t i=0;i<n.length();i++){
        if(n[i] != m[i]){
            s = m;
            return s;
        }
    }
    m.erase(m.begin(),m.begin()+n.length());
    s.append(m);
    return s;
}

#endif