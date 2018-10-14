#include <iostream>
#include <vector>
#include <algorithm>
#include "../../lib/CImg.templ"
#include "t1-noise-removal.h"

using namespace std;
using namespace cimg_library;

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


CImg<int> applyAdaptiveMedianFilter(CImg<int> img, int maxLevel){
    vector<int> pixels;
    int shift = (maxLevel-1)/2;
    for (int x = 0; x < img.width(); x++) {
        for (int y = 0; y < img.height(); y++) {
            for (int j = 0; j < 3; j++) {
                for (int x2 = 0; x2 < maxLevel; x2++) {
                    for (int y2 = 0; y2 < maxLevel; y2++) {
                        if (x - shift + x2 >= 0 && x - shift + x2 < img.width() && y - shift + y2 >= 0 &&
                            y - shift + y2 < img.height()) {
                            pixels.push_back(img(x - shift + x2, y - shift + y2, 0, j));
                        }
                    }
                }
                sort(pixels.begin(), pixels.end());
                //if (pixels.size() % 2 != 0) {
                    img(x, y, 0, j) = pixels[(pixels.size()-1) / 2];
                //} else {
                  //  img(x, y, 0, 0) = (pixels[pixels.size()/2] + pixels[pixels.size()/2 + 1]) / 2;
                //}
                pixels.clear();
            }
        }
    }
    return img;
}

CImg<int> applyMinimumFilter(CImg<int> img){
    return img;
}

CImg<int> applyMaximumFilter(CImg<int> img){
    return img;
}
