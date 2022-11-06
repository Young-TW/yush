#include <iostream>
using namespace std;

int arrow(){
    char a;
    a = getchar();
    if(a=='033'){
        a = getchar();
        if(a=='['){
            a = getchar();
            switch(a){
                case 'A':
                    break;
                case 'B':
                    break;
                case 'C':
                    break;
                case 'D':
                    break;
            }
        }
    }
    return 0;
}