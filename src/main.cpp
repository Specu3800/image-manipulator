#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>

using namespace std;

int main(int argc, char* argv[]) {

    if (argc < 2) {
        cout << "no args" << endl;
        cout << "exit" << endl;
    } else {

        if (strcmp(argv[1], "--help")){
            cout << "really nice help message" << endl;
            cout << "exit" << endl;
        } else if (strcmp(argv[1], "--vflip") != 0){
            cout << "really nice vflip" << endl;
            cout << argv[1] << endl;
            cout << "exit" << endl;
        } else if (strcmp(argv[1], "--hflip") != 0) {
            cout << "really nice hflip" << endl;
            cout << "exit" << endl;
        } else {
            cout << "no maching command" << endl;
            cout << "exit" << endl;
        }
    }


}