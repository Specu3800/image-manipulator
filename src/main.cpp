#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include "libs/CImg.h"

using namespace std;
using namespace cimg_library;

void displayHelp();
void changeBrightness(CImg<unsigned char>, char*, char*);
void changeContrast(CImg<unsigned char>, char*, char*);
void changeToNegative(CImg<unsigned char>, char*);

int main(int argc, char* argv[]) {
    CImg<unsigned char> image("../img/color-24bit/lenac.bmp");
    image.save("../out/original.bmp");

    if (argc < 2 || argc > 5) {
        cout << "Wrong number of parameters. Type --help to view the list of the available commands." << endl;
        cout << "exit" << endl;
    } else {
        if (argv[1] == string("--help")) displayHelp();
        else if (argv[1] == string("--brightness")) changeBrightness(image, argv[2], argv[4]);
        else if (argv[1] == string("--contrast")) changeContrast(image, argv[2], argv[4]);
        else if (argv[1] == string("--negative")) changeToNegative(image, argv[3]);
        else {cout << "No maching command. Type --help to view the list of the available commands."; exit(0);}
    }
}

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
            "       modifies brightess of image in srcPth by a modificator(-255 <= mod <= 255) value and saves image in destPth\n"
            "\n"
            "   --contrast mod srcPth destPth\n"
            "       modifies contrast of image in srcPth by a modificator(0 < mod <= 2) value and saves image in destPth\n"
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

void changeBrightness(CImg<unsigned char> img, char* val, char* path) {
    int value = atoi(val);
    cout << "Changing brightness by " << val << " of image: " << path << endl;
    for (int x = 0; x < img.width(); x++) {
        for (int y = 0; y < img.height(); y++) {
            for (int j = 0; j < 3; j++) {
                if (img(x, y, 0, j) + value > 255) img(x, y, 0, j) = 255;
                else if (img(x, y, 0, j) + value < 0) img(x, y, 0, j) = 0;
                else img(x, y, 0, j) = img(x, y, 0, j) + value;
            }
        }
    }
    img.save(path);
    exit(0);
}

void changeContrast(CImg<unsigned char> img, char* val, char* path) {
    float value = atof(val);
    if (value < 0) {cout << "Wrong value of the contrast - value should be a positive number"; exit(0);}

    cout << "Changing contrast by " << value << " of image: " << path << endl;
    float beta = 128 - 128 * value;
    for (int x = 0; x < img.width(); x++) {
        for (int y = 0; y < img.height(); y++) {
            for (int j = 0; j < 3; j++) {
                if (value * img(x, y, 0, j) + beta > 255) img(x, y, 0, j) = 255;
                else if (value * img(x, y, 0, j) + beta < 0) img(x, y, 0, j) = 0;
                else img(x, y, 0, j) = value * img(x, y, 0, j) + beta;
            }
        }
    }
    img.save(path);
    exit(0);
}

void changeToNegative(CImg<unsigned char> img, char* path) {
    cout << "Changing image " << path << " to negative" << endl;
    for (int x = 0; x < img.width(); x++) {
        for (int y = 0; y < img.height(); y++) {
            for (int j = 0; j < 3; j++) {
                img(x, y, 0, j) = 255 - img(x, y, 0, j);
            }
        }
    }
    img.save(path);
    exit(0);
}





