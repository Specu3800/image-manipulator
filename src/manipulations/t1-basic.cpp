#include <iostream>
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
            for (int c = 0; c < 3; c++) {
                if (original(x, y, 0, c) + value > 255) edited(x, y, 0, c) = 255;
                else if (original(x, y, 0, c) + value < 0) edited(x, y, 0, c) = 0;
                else edited(x, y, 0, c) = original(x, y, 0, c) + value;
            }
        }
    }
}

void changeContrast(CImg<int> &original, CImg<int> &edited, char* fac) {
    float factor = atof(fac);
    if (factor < 0) {cout << "Wrong value of the contrast. \nType --help to view information about available commands." << endl; exit(0);}
    cout << "Changing contrast by " << factor << endl;
    float beta = 127 - 127 * factor;
    for (int x = 0; x < original.width(); x++) {
        displayProgress(x, original.width()-1);
        for (int y = 0; y < original.height(); y++) {
            for (int c = 0; c < 3; c++) {
                if (factor * original(x, y, 0, c) + beta > 255) edited(x, y, 0, c) = 255;
                else if (factor * original(x, y, 0, c) + beta < 0) edited(x, y, 0, c) = 0;
                else edited(x, y, 0, c) = factor * original(x, y, 0, c) + beta;
            }
        }
    }
}

void changeToNegative(CImg<int> &original, CImg<int> &edited) {
    cout << "Changing image to negative" << endl;
    for (int x = 0; x < original.width(); x++) {
        displayProgress(x, original.width()-1);
        for (int y = 0; y < original.height(); y++) {
            for (int c = 0; c < 3; c++) {
                edited(x, y, 0, c) = 255 - original(x, y, 0, c);
            }
        }
    }
}