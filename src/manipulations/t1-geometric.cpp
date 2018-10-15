#include <iostream>
#include <cmath>
#include "../../lib/CImg.templ"
#include "t1-geometric.h"
#include "t0-other.h"

using namespace std;
using namespace cimg_library;

void doHorizontalFlip(CImg<int> &original, CImg<int> &edited){
    cout << "Flipping vertically " << endl;
    edited = original;
    for (int x = 0; x < original.width(); x++) {
        for (int y = 0; y < original.height()/2; y++) {
            for (int c = 0; c < 3; c++) {
                swap(edited(x, y, 0, c), edited(x, edited.height() - y -1, 0, c));
            }
        }
    }
}

void doVerticalFlip(CImg<int> &original, CImg<int> &edited){
    cout << "Flipping horizontally " << endl;
    edited = original;
    for (int x = 0; x < original.width()/2; x++) {
        for (int y = 0; y < original.height(); y++) {
            for (int c = 0; c < 3; c++) {
                swap(edited(x, y, 0, c), edited(edited.width() - x - 1, y, 0, c));
            }
        }
    }
}

void doDiagonalFlip(CImg<int> &original, CImg<int> &edited){ //rotate and vflip
    cout << "Flipping diagonally " << endl;
    edited = original;
    for (int x = 0; x < original.width(); x++) {
        for (int y = 0; y < original.height()/2; y++) {
            for (int c = 0; c < 3; c++) {
                swap(edited(x, y, 0, c), edited(edited.width() - x - 1, edited.height() - y -1, 0, c));
            }
        }
    }
}

void shrinkBy(CImg<int> &original, CImg<int> &edited, char* fac){ //dodac interpolacce
    float factor = atof(fac);

    cout << "Shrinking by: " << factor << endl;
    edited = CImg<int>(original.width()/factor, original.height()/factor, 1, 3, 0);
    for (int x = 0; x < original.width(); x++) {
        for (int y = 0; y < original.height(); y++) {
            cout << x << " " << y << endl;
            for (int c = 0; c < 3; c++) {
                if (x/factor >= 0 && x/factor < edited.width() && y/factor >= 0 && y/factor < edited.height())
                    edited(x/factor, y/factor, 0, c) = original(x, y, 0, c);
            }
        }
    }
}

void enlargeBy(CImg<int> &original, CImg<int> &edited, char* fac){ //dodac interpolacce
    float factor = atof(fac);

    float repeat = factor;
    if (factor == floor(factor)) repeat--;
    else repeat = floor(repeat);

    cout << "Enlarging by: " << factor << endl;
    edited = CImg<int>(original.width()*factor, original.height()*factor, 1, 3, 0);
    for (int x = 0; x < original.width(); x++) {
        for (int y = 0; y < original.height(); y++) {
            for (int c = 0; c < 3; c++) {
                for (int xx = 0; xx < repeat; xx++) {
                    for (int yy = 0; yy < repeat; yy++) {
                        edited(x*factor + xx, y*factor + yy, 0, c) = original(x, y, 0, c);
                    }
                }
            }
        }
    }
    applyBilinearInterpolation(edited);
}
