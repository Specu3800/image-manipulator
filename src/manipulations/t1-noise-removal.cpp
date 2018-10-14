#include <iostream>
#include <vector>
#include <algorithm>
#include "../../lib/CImg.templ"
#include "t1-noise-removal.h"

using namespace std;
using namespace cimg_library;


CImg<int> applyAdaptiveMedianFilter(CImg<int> img, char* maxD){
    int maxDepth = atoi(maxD);
    vector<int> pixels;
    int currDepth;
    for (int x = 0; x < img.width(); x++) {
        for (int y = 0; y < img.height(); y++) {
            for (int j = 0; j < 3; j++) {

                currDepth = 3;
                while(true) {

                    if(currDepth > maxDepth) break;

                    int shift = (currDepth-1)/2;
                    for (int x2 = 0; x2 < currDepth; x2++) {
                        for (int y2 = 0; y2 < currDepth; y2++) {
                            if (x - shift + x2 >= 0 && x - shift + x2 < img.width() && y - shift + y2 >= 0 && y - shift + y2 < img.height()) {
                                pixels.push_back(img(x - shift + x2, y - shift + y2, 0, j));
                            }
                        }
                    }
                    sort(pixels.begin(), pixels.end());
                    if (img(x, y, 0, j) == pixels[(pixels.size()-1) / 2]){
                        pixels.clear();
                        currDepth += 2;
                        continue;
                    } else {
                        img(x, y, 0, j) = pixels[(pixels.size()-1) / 2];
                        pixels.clear();
                        break;}
                }
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
