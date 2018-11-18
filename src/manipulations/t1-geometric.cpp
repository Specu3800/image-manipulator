#include <iostream>
#include <cmath>
#include "../../lib/CImg.templ"
#include "t1-geometric.h"
#include "t0-other.h"
#include "t1-noise-removal-operations.h"

using namespace std;
using namespace cimg_library;

CImg<int>& doHorizontalFlip(CImg<int> &original){
    CImg<int>* edited = new CImg<int>(original.width(), original.height(), 1, original.spectrum(), 0);
    cout << "Flipping vertically " << endl;
    for (int x = 0; x < original.width(); x++) {
        displayProgress(x, original.width()-1);
        for (int y = 0; y < original.height(); y++) {
            for (int c = 0; c < original.spectrum(); c++) {
                (*edited)(x, y, 0, c) = original(x, original.height() - y -1, 0, c);
            }
        }
    }
    return *edited;
}

CImg<int>& doVerticalFlip(CImg<int> &original){
    CImg<int>* edited = new CImg<int>(original.width(), original.height(), 1, original.spectrum(), 0);
    cout << "Flipping horizontally " << endl;
    for (int x = 0; x < original.width(); x++) {
        displayProgress(x, original.width()-1);
        for (int y = 0; y < original.height(); y++) {
            for (int c = 0; c < original.spectrum(); c++) {
                (*edited)(x, y, 0, c) = original(original.width() - x - 1, y, 0, c);
            }
        }
    }
    return *edited;
}

CImg<int>& doDiagonalFlip(CImg<int> &original){
    CImg<int>* edited = new CImg<int>(original.width(), original.height(), 1, original.spectrum(), 0);
    cout << "Flipping diagonally " << endl;
    for (int x = 0; x < original.width(); x++) {
        displayProgress(x, original.width()-1);
        for (int y = 0; y < original.height(); y++) {
            for (int c = 0; c < original.spectrum(); c++) {
                (*edited)(x, y, 0, c) = original(original.width() - x - 1, original.height() - y -1, 0, c);
            }
        }
    }
    return *edited;
}

CImg<int>& shrinkBy(CImg<int> &original, float factor){
    CImg<int>* edited = new CImg<int>(original.width()/factor, original.height()/factor, 1, original.spectrum(), 0);
    cout << "Shrinking by: " << factor << endl;
    for (int x = 0; x < original.width(); x++) {
        displayProgress(x, original.width()-1);
        for (int y = 0; y < original.height(); y++) {
            for (int c = 0; c < original.spectrum(); c++) {
                if (x/factor >= 0 && x/factor < original.width() && y/factor >= 0 && y/factor < original.height())
                    (*edited)(x/factor, y/factor, 0, c) = original(x, y, 0, c);
            }
        }
    }
    //edited = &applyBilinearInterpolation(*edited); //will blur the image, depends on shrinking factor
    return *edited;
}

CImg<int>& enlargeBy(CImg<int> &original, float factor){
    CImg<int>* edited = new CImg<int>(original.width()*factor, original.height()*factor, 1, original.spectrum(), 0);
    float repeat = factor;
    if (factor == floor(factor)) repeat--;
    else repeat = floor(repeat);

    cout << "Enlarging by: " << factor << endl;
    for (int x = 0; x < original.width(); x++) {
        displayProgress(x, original.width()-1);
        for (int y = 0; y < original.height(); y++) {
            for (int c = 0; c < original.spectrum(); c++) {
                for (int xx = 0; xx < repeat; xx++) {
                    for (int yy = 0; yy < repeat; yy++) {
                        (*edited)(x*factor + xx, y*factor + yy, 0, c) = original(x, y, 0, c);
                    }
                }
            }
        }
    }
    edited = &applyBilinearInterpolation(*edited); //just do it
    return *edited;
}
