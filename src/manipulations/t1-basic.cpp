#include <iostream>
#include <cmath>
#include "../../lib/CImg.templ"
#include "t1-basic.h"
#include "t0-other.h"

using namespace std;
using namespace cimg_library;

void changeBrightness(CImg<int> &original, CImg<int> &edited, char* val) {
    int value = atoi(val);
    cout << "Changing brightness by " << val << endl;
    for (int x = 0; x < original.width(); x++) {
        displayProgress(x, original.width()-1);
        for (int y = 0; y < original.height(); y++) {
            for (int c = 0; c < original.spectrum(); c++) {
                if (original(x, y, 0, c) + value > 255) edited(x, y, 0, c) = 255;
                else if (original(x, y, 0, c) + value < 0) edited(x, y, 0, c) = 0;
                else edited(x, y, 0, c) = original(x, y, 0, c) + value;
            }
        }
    }
}

void changeContrast(CImg<int> &original, CImg<int> &edited, char* fac) {
    float factor = atof(fac);
    if (factor <= 0) {cout << "Wrong value of the contrast. \nType --help to view information about available commands." << endl; exit(0);}
    cout << "Changing contrast by " << factor << endl;
    for (int x = 0; x < original.width(); x++) {
        displayProgress(x, original.width()-1);
        for (int y = 0; y < original.height(); y++) {
            for (int c = 0; c < original.spectrum(); c++) {
                int newColor = (original(x, y, 0, c) - 128)*factor + 128;
                if (newColor > 255) edited(x, y, 0, c) = 255;
                else if (newColor< 0) edited(x, y, 0, c) = 0;
                else edited(x, y, 0, c) = newColor;
            }
        }
    }
}
void changeContrast2(CImg<int> &original, CImg<int> &edited, char* fac) {
    float factor = atof(fac);
    if (factor <= 0) {cout << "Wrong value of the contrast. \nType --help to view information about available commands." << endl; exit(0);}
    cout << "Changing contrast by " << factor << endl;
    for (int x = 0; x < original.width(); x++) {
        displayProgress(x, original.width()-1);
        for (int y = 0; y < original.height(); y++) {
            for (int c = 0; c < original.spectrum(); c++) {
                int newColor = 255 * pow((original(x, y, 0, c)) / 255.0, factor);
                if (newColor > 255) edited(x, y, 0, c) = 255;
                else if (newColor< 0) edited(x, y, 0, c) = 0;
                else edited(x, y, 0, c) = newColor;
            }
        }
    }
}

void changeToNegative(CImg<int> &original, CImg<int> &edited) {
    cout << "Changing image to negative" << endl;
    for (int x = 0; x < original.width(); x++) {
        displayProgress(x, original.width()-1);
        for (int y = 0; y < original.height(); y++) {
            for (int c = 0; c < original.spectrum(); c++) {
                edited(x, y, 0, c) = 255 - original(x, y, 0, c);
            }
        }
    }
}