#include <iostream>
#include <cmath>
#include "../../lib/CImg.templ"
#include "t1-geometric.h"
#include "t0-other.h"

using namespace std;
using namespace cimg_library;

CImg<int> doHorizontalFlip(CImg<int> img){
    cout << "Flipping vertically " << endl;
    for (int x = 0; x < img.width(); x++) {
        for (int y = 0; y < img.height()/2; y++) {
            for (int j = 0; j < 3; j++) {
                swap(img(x, y, 0, j), img(x, img.height() - y -1, 0, j));
            }
        }
    }
    return img;
}

CImg<int> doVerticalFlip(CImg<int> img){
    cout << "Flipping horizontally " << endl;
    for (int x = 0; x < img.width()/2; x++) {
        for (int y = 0; y < img.height(); y++) {
            for (int j = 0; j < 3; j++) {
                swap(img(x, y, 0, j), img(img.width() - x - 1, y, 0, j));
            }
        }
    }
    return img;
}

CImg<int> doDiagonalFlip(CImg<int> img){ //rotate and vflip
    cout << "Flipping diagonally " << endl;
    for (int x = 0; x < img.width(); x++) {
        for (int y = 0; y < img.height()/2; y++) {
            for (int j = 0; j < 3; j++) {
                swap(img(x, y, 0, j), img(img.width() - x - 1, img.height() - y -1, 0, j));
            }
        }
    }
    return img;
}

CImg<int> shrinkBy(CImg<int> img, char* fac){ //dodaj interpolacje
    float factor = atof(fac);

    cout << "Shrinking by: " << factor << endl;
    CImg<int> newImg(img.width()/factor, img.height()/factor, 1, 3, 0);
    for (int x = 0; x < img.width(); x++) {
        for (int y = 0; y < img.height(); y++) {
            cout << x << " " << y << endl;
            for (int j = 0; j < 3; j++) {
                if (x/factor >= 0 && x/factor < newImg.width() && y/factor >= 0 && y/factor < newImg.height())
                        newImg(x/factor, y/factor, 0, j) = img(x, y, 0, j);
            }
        }
    }
    return applyBilinearInterpolation(newImg);
}

CImg<int> enlargeBy(CImg<int> img, char* fac){ //dodaj interpolacje
    float factor = atof(fac);

    float repeat = factor;
    if (factor == floor(factor)) repeat--;
    else repeat = floor(repeat);

    cout << "Enlarging by: " << factor << endl;
    CImg<int> newImg(img.width()*factor, img.height()*factor, 1, 3, 0);
    for (int x = 0; x < img.width(); x++) {
        for (int y = 0; y < img.height(); y++) {
            for (int j = 0; j < 3; j++) {
                for (int xx = 0; xx < repeat; xx++) {
                    for (int yy = 0; yy < repeat; yy++) {
                        newImg(x*factor + xx, y*factor + yy, 0, j) = img(x, y, 0, j);
                    }
                }
            }
        }
    }
    return applyBilinearInterpolation(newImg);
}
