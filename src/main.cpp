#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cmath>
//#include "libs/CImg.h"

using namespace std;
//using namespace cimg_library;

void displayHelp();
void changeBrightness(char*, char*);
void changeContrast(char*, char*);
void changeToNegative(char*);
void exitWithError(int);

void displayHelp() {
    cout << "#############################################################################\n"
            "########################---   Image Manipulator   ---########################\n"
            "#############################################################################\n"
            "#                                                                           #\n"
            "#                         Michał Suliborski  217863                         #\n"
            "#                         Arek Zasina        217868                         #\n"
            "#                                                                           #\n"
            "#                            Politechnika Łódzka                            #\n"
            "#                                2018/2019                                  #\n"
            "#                                                                           #\n"
            "#############################################################################\n"
            "\n"
            << (char)27 << "[1m" << "USAGE:\n" << (char)27 << "[0m" <<
            "   image-manipulator --command [-argument=value [...]]\n"
            "\n"
            << (char)27 << "[1m" << "COMMANDS:\n" << (char)27 << "[0m" <<
            "   --brightness mod srcPth destPth\n"
            "       modifies brightess of image in srcPth by a modificator(mod) value and saves image in destPth\n"
            "\n"
            "   --contrast mod srcPth destPth\n"
            "       modifies contrast of image in srcPth by a modificator(mod) value and saves image in destPth\n"
            "\n"
            "	--negative srcPth destPth\n"
            "		outputs negative of image in srcPth to destPth\n"
            "\n"
            "	--hflip srcPth destPth\n"
            "		outputs horizontally fliped image in srcPth to destPth\n"
            "\n"
            "	--vflip srcPth destPth\n"
            "		outputs vertically fliped image in srcPth to destPth\n"
            "\n"
            "	--dflip srcPth destPth\n"
            "		outputs diagonally fliped image in srcPth to destPth\n"
            "\n"
            "	--shrik srcPth destPth\n"
            "		outputs image in srcPth shrinked by a factor of 2 to destPth\n"
            "\n"
            "	--enlarge srcPth destPth\n"
            "		outputs image in srcPth enlarged by a factor of 2 to destPth\n"
            "\n"
            "	--adaptive srcPth destPth\n"
            "		outputs image in srcPth with adaptive filter applied to destPth\n"
            "\n"
            "	--min srcPth destPth\n"
            "		outputs image in srcPth with minimum filter applied to destPth\n"
            "\n"
            "	--max srcPth destPth\n"
            "		outputs image in srcPth with maximum filter applied to destPth\n"
            "\n"
            "	--mse srcPth1 srcPth2\n"
            "		analyses and displays mean square error between images in srcPth1 and srcPth2\n"
            "\n"
            "	--pmse srcPth1 srcPth2\n"
            "		analyses and displays peak mean square error between images in srcPth1 and srcPth2\n"
            "\n"
            "	--snr srcPth1 srcPth2\n"
            "		analyses and displays signal to noise ratio between images in srcPth1 and srcPth2\n"
            "\n"
            "	--psnr srcPth1 srcPth2\n"
            "		analyses and displays peak signal to noise ratio between images in srcPth1 and srcPth2\n"
            "\n"
            "	--md srcPth1 srcPth2\n"
            "		analyses and displays maximum difference between images in srcPth1 and srcPth2\n"
            "\n";

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
//    CImg<unsigned char> image("../img/color-24bit/lenac.bmp");
//    CImgDisplay main_disp(image,"Click a point");
//    image.blur(2.5);
//    CImgDisplay main2_disp(image,"Click a point");
//    image.save("file.bmp");



    if (argc < 2 || argc > 5) {
        cout << "Wrong number of parameters. Type --help to view the list of the available commands." << endl;
        cout << "exit" << endl;
    } else {
        if (argv[1] == string("--help")) displayHelp();
        else if (argv[1] == string("--brightness")) changeBrightness(argv[2], argv[3]);
        else if (argv[1] == string("--contrast")) changeContrast(argv[2], argv[3]);
        else if (argv[1] == string("--negative")) changeToNegative(argv[2]);
        else exitWithError(1);
    }
}

