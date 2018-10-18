#include <iostream>
#include <cmath>
#include "../../lib/CImg.templ"
#include "t1-geometric.h"
#include "t0-other.h"
#include "t1-noise-removal.h"

using namespace std;
using namespace cimg_library;

void doHorizontalFlip(CImg<int> &original, CImg<int> &edited){
    cout << "Flipping vertically " << endl;
    for (int x = 0; x < original.width(); x++) {
        displayProgress(x, original.width()-1);
        for (int y = 0; y < original.height(); y++) {
            for (int s = 0; s < original.spectrum(); s++) {
                edited(x, y, 0, s) = original(x, edited.height() - y -1, 0, s);
            }
        }
    }
}

void doVerticalFlip(CImg<int> &original, CImg<int> &edited){
    cout << "Flipping horizontally " << endl;
    for (int x = 0; x < original.width(); x++) {
        displayProgress(x, original.width()-1);
        for (int y = 0; y < original.height(); y++) {
            for (int s = 0; s < original.spectrum(); s++) {
                edited(x, y, 0, s) = original(edited.width() - x - 1, y, 0, s);
            }
        }
    }
}

void doDiagonalFlip(CImg<int> &original, CImg<int> &edited){ //rotate and vflip
    cout << "Flipping diagonally " << endl;
    for (int x = 0; x < original.width(); x++) {
        displayProgress(x, original.width()-1);
        for (int y = 0; y < original.height(); y++) {
            for (int s = 0; s < original.spectrum(); s++) {
                edited(x, y, 0, s) = original(edited.width() - x - 1, edited.height() - y -1, 0, s);
            }
        }
    }
}

void shrinkBy(CImg<int> &original, CImg<int> &edited, char* fac){ //dodac interpolacce
    float factor = atof(fac);

    cout << "Shrinking by: " << factor << endl;
    edited = CImg<int>(original.width()/factor, original.height()/factor, 1, 3, 0);
    for (int x = 0; x < original.width(); x++) {
        displayProgress(x, original.width()-1);
        for (int y = 0; y < original.height(); y++) {
            for (int s = 0; s < original.spectrum(); s++) {
                if (x/factor >= 0 && x/factor < edited.width() && y/factor >= 0 && y/factor < edited.height())
                    edited(x/factor, y/factor, 0, s) = original(x, y, 0, s);
            }
        }
    }
    //applyBilinearInterpolation(edited); //will blur the image, depends on shrinking factor
}

void enlargeBy(CImg<int> &original, CImg<int> &edited, char* fac){ //dodac interpolacce
    float factor = atof(fac);

    float repeat = factor;
    if (factor == floor(factor)) repeat--;
    else repeat = floor(repeat);

    cout << "Enlarging by: " << factor << endl;
    edited = CImg<int>(original.width()*factor, original.height()*factor, 1, 3, 0);
    for (int x = 0; x < original.width(); x++) {
        displayProgress(x, original.width()-1);
        for (int y = 0; y < original.height(); y++) {
            for (int s = 0; s < original.spectrum(); s++) {
                for (int xx = 0; xx < repeat; xx++) {
                    for (int yy = 0; yy < repeat; yy++) {
                        edited(x*factor + xx, y*factor + yy, 0, s) = original(x, y, 0, s);
                    }
                }
            }
        }
    }
    applyBilinearInterpolation(edited);
}
