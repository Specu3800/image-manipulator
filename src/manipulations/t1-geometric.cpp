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
    return img;
}

CImg<int> doDiagonalFlip(CImg<int> img){ //rotate and vflip
    return img;
}

CImg<int> shrinkBy(CImg<int> img, char* fac){ //dodaj interpolacje
    return img;
}

CImg<int> enlargeBy(CImg<int> img, char* fac){ //dodaj interpolacje
    float factor = atof(fac);
    float repeat = factor;
    if (factor == floor(factor)) repeat--;
    else repeat = floor(repeat);
    cout << "repeat: " << repeat << endl;

    cout << "Enlarging by: " << factor << endl;
    int newX = img.width()*factor, newY = img.height()*factor;
    CImg<int> newImg(newX, newY,1,3,0);
    cout << newX << newY << endl;
    for (int x = 0; x < img.width(); x++) {
        for (int y = 0; y < img.height(); y++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < repeat; k++) {
                    if(x-k < 0 || x + k >= newImg.width() || y-k < 0 || y + k >= newImg.height()) continue; //not for borders
                    newImg(x * factor + k, y * factor, 0, j) = img(x, y, 0, j);
                    newImg(x * factor, y * factor - k, 0, j) = img(x, y, 0, j);
                    newImg(x * factor + k, y * factor + k, 0, j) = img(x, y, 0, j);

                }
            }
        }
    }
    return newImg;
    return applyBilinearInterpolation(newImg);
}
CImg<int> simpleEnlargeBy(CImg<int> img, char* fac){ //dodaj interpolacje
    float factor = atof(fac);
    cout << "Enlarging by: " << factor << endl;
    int newX = img.width()*factor, newY = img.height()*factor;
    CImg<int> newImg(newX, newY,1,3,0);
    cout << newX << newY << endl;
    for (int x = 0; x < img.width(); x++) {
        for (int y = 0; y < img.height(); y++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    newImg(x * factor, y * factor, 0, j) = img(x, y, 0, j);
                }
            }
        }
    }
    return newImg;
}
