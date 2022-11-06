#include <iostream>
using namespace std;

#include "../global_var.h"

bool place_is_current(){
    if(place_input_past == input_past.size()){
        return 1;
    }
    return 0;
}

int arrow_up(){
    if(place_is_current){
        for(int i=0;i<input_past[place_input_past].length();i++){
            cout << "\b";
        }
    }
    place_input_past--;
    cout << input_past[place_input_past];
    return 0;
}

int arrow_down(){
    if(place_input_past == 0){
        return 1;
    }else if(!place_is_current){
        for(int i=0;i<input_past[place_input_past].length();i++){
            cout << "\b";
            cout << input_past[++place_input_past];
        }
        return 0;
    }else if(place_is_current()){
        for(int i=0;i<input_past[place_input_past].length();i++){
            cout << "\b";
        }
        return 0;
    }else{
        return 1;
    }
}

int arrow_left(){
    return 0;
}

int arrow_right(){
    return 0;
}

int arrow(){
    char a;
    while(true){
        a = getchar();
        if(a=='033'){
            a = getchar();
            if(a=='['){
                a = getchar();
                switch(a){
                    case 'A':
                        arrow_up();
                        break;
                    case 'B':
                        arrow_down();
                        break;
                    case 'C':
                        break;
                    case 'D':
                        break;
                }
            }
        }
    }
    return 0;
}