#include <iostream>
#include "../../lib/CImg.templ"
#include "t1-basic.h"

using namespace std;
using namespace cimg_library;

CImg<int> changeBrightness(CImg<int> img, char* val) {
    int value = atoi(val);
    cout << "Changing brightness by " << val << endl;
    for (int x = 0; x < img.width(); x++) {
        for (int y = 0; y < img.height(); y++) {
            for (int j = 0; j < 3; j++) {
                if (img(x, y, 0, j) + value > 255) img(x, y, 0, j) = 255;
                else if (img(x, y, 0, j) + value < 0) img(x, y, 0, j) = 0;
                else img(x, y, 0, j) = img(x, y, 0, j) + value;
            }
        }
    }
    return img;
}

CImg<int> changeContrast(CImg<int> img, char* val) {
    float value = atof(val);
    if (value < 0) {cout << "Wrong value of the contrast. \nType --help to view information about available commands."; exit(0);}
    cout << "Changing contrast by " << value << endl;
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
    return img;
}

CImg<int> changeToNegative(CImg<int> img) {
    cout << "Changing image to negative" << endl;
    for (int x = 0; x < img.width(); x++) {
        for (int y = 0; y < img.height(); y++) {
            for (int j = 0; j < 3; j++) {
                img(x, y, 0, j) = 255 - img(x, y, 0, j);
            }
        }
    }
    return img;
}