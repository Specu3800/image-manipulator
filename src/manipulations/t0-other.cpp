#include <iostream>
#include "../../lib/CImg.templ"
#include "t0-other.h"

using namespace std;
using namespace cimg_library;

CImg<int> applyBilinearInterpolation(CImg<int> img){
    for (int x = 0; x < img.width(); x++) {
        for (int y = 0; y < img.height(); y++) {

            if(x-1 < 0 || x + 1 >= img.width() || y-1 < 0 || y + 1 >= img.height()) continue; //not for borders
            if(img(x, y, 0, 0) != 0 || img(x, y, 0, 1) != 0 || img(x, y, 0, 2) != 0) continue; //apply only on black pixels
            if(img(x+1, y+1, 0, 0) == 0 && img(x+1, y+1, 0, 1) == 0 && img(x+1, y+1, 0, 2) == 0) continue; //if surrounded by black pixels
            if(img(x+1, y-1, 0, 0) == 0 && img(x+1, y-1, 0, 1) == 0 && img(x+1, y-1, 0, 2) == 0) continue;
            if(img(x-1, y+1, 0, 0) == 0 && img(x-1, y+1, 0, 1) == 0 && img(x-1, y+1, 0, 2) == 0) continue;
            if(img(x-1, y-1, 0, 0) == 0 && img(x-1, y-1, 0, 1) == 0 && img(x-1, y-1, 0, 2) == 0) continue;
            for (int j = 0; j < 3; j++) {
                img(x, y-1, 0, j) = 0.5*img(x-1, y-1, 0, j) + 0.5*img(x+1, y-1, 0, j);
                img(x, y+1, 0, j) = 0.5*img(x-1, y+1, 0, j) + 0.5*img(x+1, y+1, 0, j);
                img(x+1, y, 0, j) = 0.5*img(x+1, y-1, 0, j) + 0.5*img(x+1, y+1, 0, j);
                img(x-1, y, 0, j) = 0.5*img(x-1, y+1, 0, j) + 0.5*img(x-1, y-1, 0, j);
                img(x, y, 0, j) = 0.5*img(x, y-1, 0, j) + 0.5*img(x, y+1, 0, j);
            }
        }
    }
    return img;
}


int getR(int color){
    return (color - (color % (256*256))) / (256*256);
}
int getG(int color){
    return ((color % (256*256)) - (color%256))/256;
}
int getB(int color){
    return color % 256;
}

int getColor(int r, int g, int b){
    return r*256*256 + g*256 + b;
}

