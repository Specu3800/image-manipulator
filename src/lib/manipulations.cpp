//
// Created by mike on 11/10/18.
//

#include <iostream>
#include "manipulations.h"
#include "CImg.templ"

using namespace std;
using namespace cimg_library;

CImg<int> changeBrightness(CImg<int> img, char* val, char* path) {
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
    return img;
}

CImg<int> changeContrast(CImg<int> img, char* val, char* path) {
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
    return img;
}

CImg<int> changeToNegative(CImg<int> img, char* path) {
    cout << "Changing image " << path << " to negative" << endl;
    for (int x = 0; x < img.width(); x++) {
        for (int y = 0; y < img.height(); y++) {
            for (int j = 0; j < 3; j++) {
                img(x, y, 0, j) = 255 - img(x, y, 0, j);
            }
        }
    }
    img.save(path);
    return img;
}