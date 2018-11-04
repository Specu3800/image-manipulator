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
            for (int s = 0; s < original.spectrum(); s++) {
                if (original(x, y, 0, s) + value > 255) edited(x, y, 0, s) = 255;
                else if (original(x, y, 0, s) + value < 0) edited(x, y, 0, s) = 0;
                else edited(x, y, 0, s) = original(x, y, 0, s) + value;
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
            for (int s = 0; s < original.spectrum(); s++) {
                int newColor = (original(x, y, 0, s) - 128)*factor + 128;
                if (newColor > 255) edited(x, y, 0, s) = 255;
                else if (newColor< 0) edited(x, y, 0, s) = 0;
                else edited(x, y, 0, s) = newColor;
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
            for (int s = 0; s < original.spectrum(); s++) {
                int newColor = 255 * pow((original(x, y, 0, s)) / 255.0, factor);
                if (newColor > 255) edited(x, y, 0, s) = 255;
                else if (newColor< 0) edited(x, y, 0, s) = 0;
                else edited(x, y, 0, s) = newColor;
            }
        }
    }
}

void changeToNegative(CImg<int> &original, CImg<int> &edited) {
    cout << "Changing image to negative" << endl;
    for (int x = 0; x < original.width(); x++) {
        displayProgress(x, original.width()-1);
        for (int y = 0; y < original.height(); y++) {
            for (int s = 0; s < original.spectrum(); s++) {
                edited(x, y, 0, s) = 255 - original(x, y, 0, s);
            }
        }
    }
}