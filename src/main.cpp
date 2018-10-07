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

    if (argc < 2 || argc > 5) {cout << "Wrong number of parameters.\nType --help to view the list of the available commands." << endl; exit(0);
    } else {
        if (argv[1] == string("--help")) displayHelp();
        else if (argv[1] == string("--brightness")) changeBrightness(image, argv[2], argv[4]);
        else if (argv[1] == string("--contrast")) changeContrast(image, argv[2], argv[4]);
        else if (argv[1] == string("--negative")) changeToNegative(image, argv[3]);
        else {cout << "No maching command. \nType --help to view the list of the available commands."; exit(0);}
    }
}

void displayHelp() {
    cout <<
    "###############################################################################\n"
    "#########################---   " << (char)27 << "[1m" << "Image Manipulator" << (char)27 << "[0m" << "   ---#########################\n"
    "###############################################################################\n"
    "#                                                                             #\n"
    "#                          Michał Suliborski  217863                          #\n"
    "#                          Arek Zasina        217868                          #\n"
    "#                                                                             #\n"
    "#                             Politechnika Łódzka                             #\n"
    "#                                 2018/2019                                   #\n"
    "#                                                                             #\n"
    "###############################################################################\n"
    "\n"
    << (char)27 << "[1m" << "USAGE:\n" << (char)27 << "[0m" <<
    "   image-manipulator --command [-argument=value [...]]\n"
    "\n"
    << (char)27 << "[1m" << "COMMANDS:\n" << (char)27 << "[0m" <<
    "   --brightness mod src dest\n"
    "       modifies brightess of image in src by a modificator(-255 <= mod <= 255)\n"
    "       value and saves image in dest\n"
    "\n"
    "   --contrast mod src dest\n"
    "       modifies contrast of image in src by a modificator(0 < mod <= 2)\n"
    "       value and saves image in dest\n"
    "\n"
    "   --negative src dest\n"
    "      outputs negative of image in src to dest\n"
    "\n"
    "   --hflip src dest\n"
    "      outputs horizontally fliped image in src to dest\n"
    "\n"
    "   --vflip src dest\n"
    "      outputs vertically fliped image in src to dest\n"
    "\n"
    "   --dflip src dest\n"
    "      outputs diagonally fliped image in src to dest\n"
    "\n"
    "   --shrik src dest\n"
    "      outputs image in src shrinked by a factor of 2 to dest\n"
    "\n"
    "   --enlarge src dest\n"
    "      outputs image in src enlarged by a factor of 2 to dest\n"
    "\n"
    "   --adaptive src dest\n"
    "      outputs image in src with adaptive filter applied to dest\n"
    "\n"
    "   --min src dest\n"
    "      outputs image in src with minimum filter applied to dest\n"
    "\n"
    "   --max src dest\n"
    "      outputs image in src with maximum filter applied to dest\n"
    "\n"
    "   --mse src1 src2\n"
    "      displays mean square error between images in src1 and src2\n"
    "\n"
    "   --pmse src1 src2\n"
    "      displays peak mean square error between images in src1 and src2\n"
    "\n"
    "   --snr src1 src2\n"
    "      displays signal to noise ratio between images in src1 and src2\n"
    "\n"
    "   --psnr src1 src2\n"
    "      displays peak signal to noise ratio between images in src1 and src2\n"
    "\n"
    "   --md src1 src2\n"
    "      displays maximum difference between images in src1 and src2\n";
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
    if (value < 0) {cout << "Wrong value of the contrast. \nType --help to view information about available commands."; exit(0);}
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





