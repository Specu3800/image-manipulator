#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>

using namespace std;

void displayHelp();
void changeBrightness(char*, char*);
void changeContrast(char*, char*);
void changeToNegative(char*);
void exitWithError(int);

void displayHelp() {
    cout << "really nice help message" << endl;
    exit(0);
}

void changeBrightness(char* val, char* path) {
    cout << "changing brightness to " << val << " of image: " << path << endl;
    exit(0);
}

void changeContrast(char* val, char* path) {
    cout << "changing contrast to " << val << " of image: " << path << endl;
    exit(0);
}

void changeToNegative(char* path) {
    cout << "changing to negative image: " << path << endl;
    exit(0);
}

void exitWithError(int e){
    switch(e){
        case 1:
            cout << "no maching command, use --help for more" << endl;
            break;
        default:
            cout << "error" << endl;
            break;
    }
}


int main(int argc, char* argv[]) {

    if (argc < 2) {
        cout << "no args" << endl;
        cout << "exit" << endl;
    } else {
        if (argv[1] == string("--help")) displayHelp();
        else if (argv[1] == string("--brightness")) changeBrightness(argv[2], argv[3]);
        else if (argv[1] == string("--contrast")) changeContrast(argv[2], argv[3]);
        else if (argv[1] == string("--negative")) changeToNegative(argv[2]);
        else exitWithError(1);
    }
}

