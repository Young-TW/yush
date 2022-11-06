#include <iostream>
using namespace std;

int main(){
    cout << "Your system is ";
    #ifdef __WINDOWS__
            cout << "Windows";
            #ifdef __WIN64
                    cout << "64\n";
            #elif
                    cout << "32\n";
            #endif
    #elif __APPLE__
            cout << "Apple\n";
    #elif _unix
            cout << "UNIX\n";
    #elif _linux
            cout << "Linux\n";
    #else
            cout << "other\n";
    #endif

    return 0;
}