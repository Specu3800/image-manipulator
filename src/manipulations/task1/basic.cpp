#include <iostream>
#include <cmath>
#include <memory>
#include "lib/CImg.templ"
#include "basic.h"
#include "helpers.h"

using namespace std;
using namespace cimg_library;

CImg<int>& changeBrightness(CImg<int> &original, int value) {
    CImg<int>* edited = new CImg<int>(original.width(), original.height(), 1, original.spectrum(), 0);
    for (int x = 0; x < original.width(); x++) {
        for (int y = 0; y < original.height(); y++) {
            for (int c = 0; c < original.spectrum(); c++) {
                (*edited)(x, y, c) = normalize(original(x, y, c) + value);
            }
        }
    }
    return *edited;
}

CImg<int>& changeContrast(CImg<int> &original, float factor) {
    if (factor <= 0) {cout << "Wrong value of the contrast. \nType --help to view information about available commands." << endl; exit(0);}
    CImg<int>* edited = new CImg<int>(original.width(), original.height(), 1, original.spectrum(), 0);
    for (int x = 0; x < original.width(); x++) {
        for (int y = 0; y < original.height(); y++) {
            for (int c = 0; c < original.spectrum(); c++) {
                (*edited)(x, y, c) = normalize((original(x, y, c) - 128) * factor + 128);
            }
        }
    }
    return *edited;
}
CImg<int>& changeContrast2(CImg<int> &original, float factor) {
    CImg<int>* edited = new CImg<int>(original.width(), original.height(), 1, original.spectrum(), 0);
    if (factor <= 0) {cout << "Wrong value of the contrast. \nType --help to view information about available commands." << endl; exit(0);}
    for (int x = 0; x < original.width(); x++) {
        for (int y = 0; y < original.height(); y++) {
            for (int c = 0; c < original.spectrum(); c++) {
                (*edited)(x, y, c) = normalize(255 * pow((original(x, y, c)) / 255.0, factor));
            }
        }
    }
    return *edited;
}

CImg<int>& changeToNegative(CImg<int> &original) {
    CImg<int>* edited = new CImg<int>(original.width(), original.height(), 1, original.spectrum(), 0);
    for (int x = 0; x < original.width(); x++) {
        for (int y = 0; y < original.height(); y++) {
            for (int c = 0; c < original.spectrum(); c++) {
                (*edited)(x, y, c) = 255 - original(x, y, c);
            }
        }
    }
    return *edited;
}