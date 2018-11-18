#include <iostream>
#include <cmath>
#include <memory>
#include "../../lib/CImg.templ"
#include "t1-basic.h"
#include "t0-other.h"

using namespace std;
using namespace cimg_library;

CImg<int>& changeBrightness(CImg<int> &original, int value) {
    CImg<int>* edited = new CImg<int>(original.width(), original.height(), 1, original.spectrum(), 0);
    cout << "Changing brightness by " << value << endl;
    for (int x = 0; x < original.width(); x++) {
        displayProgress(x, original.width()-1);
        for (int y = 0; y < original.height(); y++) {
            for (int c = 0; c < original.spectrum(); c++) {
                (*edited)(x, y, 0, c) = normalized(original(x, y, 0, c) + value);
            }
        }
    }
    return *edited;
}

CImg<int>& changeContrast(CImg<int> &original, float factor) {
    if (factor <= 0) {cout << "Wrong value of the contrast. \nType --help to view information about available commands." << endl; exit(0);}
    CImg<int>* edited = new CImg<int>(original.width(), original.height(), 1, original.spectrum(), 0);
    cout << "Changing contrast by " << factor << endl;
    for (int x = 0; x < original.width(); x++) {
        displayProgress(x, original.width()-1);
        for (int y = 0; y < original.height(); y++) {
            for (int c = 0; c < original.spectrum(); c++) {
                (*edited)(x, y, 0, c) = normalized((original(x, y, 0, c) - 128)*factor + 128);
            }
        }
    }
    return *edited;
}
CImg<int>& changeContrast2(CImg<int> &original, float factor) {
    CImg<int>* edited = new CImg<int>(original.width(), original.height(), 1, original.spectrum(), 0);
    if (factor <= 0) {cout << "Wrong value of the contrast. \nType --help to view information about available commands." << endl; exit(0);}
    cout << "Changing contrast by " << factor << endl;
    for (int x = 0; x < original.width(); x++) {
        displayProgress(x, original.width()-1);
        for (int y = 0; y < original.height(); y++) {
            for (int c = 0; c < original.spectrum(); c++) {
                (*edited)(x, y, 0, c) = normalized(255 * pow((original(x, y, 0, c)) / 255.0, factor));
            }
        }
    }
    return *edited;
}

CImg<int>& changeToNegative(CImg<int> &original) {
    CImg<int>* edited = new CImg<int>(original.width(), original.height(), 1, original.spectrum(), 0);
    cout << "Changing image to negative" << endl;
    for (int x = 0; x < original.width(); x++) {
        displayProgress(x, original.width()-1);
        for (int y = 0; y < original.height(); y++) {
            for (int c = 0; c < original.spectrum(); c++) {
                (*edited)(x, y, 0, c) = 255 - original(x, y, 0, c);
            }
        }
    }
    return *edited;
}