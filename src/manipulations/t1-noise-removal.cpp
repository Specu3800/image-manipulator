#include <iostream>
#include <vector>
#include <algorithm>
#include "../../lib/CImg.templ"
#include "t1-noise-removal.h"

using namespace std;
using namespace cimg_library;

void applyAdaptiveMedianFilter(CImg<int> &original, CImg<int> &edited, char* maxD){
    int maxDepth = atoi(maxD);
    vector<int> pixels;
    int currDepth;
    for (int x = 0; x < original.width(); x++) {
        for (int y = 0; y < original.height(); y++) {
            for (int c = 0; c < 3; c++) {
                currDepth = 1;
                while(true) {

                    for (int xx = 0; xx < currDepth * 2 + 1; xx++) {
                        for (int yy = 0; yy < currDepth * 2 + 1; yy++) {
                            if (x - currDepth + xx >= 0 && x - currDepth + xx < original.width() && y - currDepth + yy >= 0 && y - currDepth + yy < original.height()) {
                                pixels.push_back(original(x - currDepth + xx, y - currDepth + yy, 0, c));
                            }
                        }
                    }
                    sort(pixels.begin(), pixels.end());
                    int zmed;
                    if (pixels.size() % 2 == 0) zmed = (pixels[pixels.size() / 2 - 1] + pixels[pixels.size() / 2]) / 2;
                    else zmed = pixels[pixels.size() / 2];
                    int zmin = pixels[0];
                    int zmax = pixels[pixels.size() - 1];

                    int A1 = zmed - zmin;
                    int A2 = zmed - zmax;

                    if (A1 > 0 && A2 < 0) {
                        int B1 = original(x, y, 0, c) - zmin;
                        int B2 = original(x, y, 0, c) - zmax;

                        if (B1 > 0 && B2 < 0) edited(x, y, 0, c) = original(x, y, 0, c);
                        else edited(x, y, 0, c) = zmed;

                        break;
                    } else {
                        currDepth++;
                        if(currDepth > maxDepth) {
                            edited(x, y, 0, c) = original(x, y, 0, c);
                            break;
                        }
                    }
                }
                pixels.clear();
            }
        }
    }
}

void applyMinimumFilter(CImg<int> &original, CImg<int> &edited, char* maxD){
    int maxDepth = atoi(maxD);
    vector<int> pixels;
    for (int x = 0; x < original.width(); x++) {
        for (int y = 0; y < original.height(); y++) {
            for (int c = 0; c < 3; c++) {

                for (int xx = 0; xx < maxDepth*2 + 1; xx++) {
                    for (int yy = 0; yy < maxDepth*2 + 1; yy++) {
                        if (x - maxDepth + xx >= 0 && x - maxDepth + xx < original.width() && y - maxDepth + yy >= 0 && y - maxDepth + yy < original.height()) {
                            pixels.push_back(original(x - maxDepth + xx, y - maxDepth + yy, 0, c));
                        }
                    }
                }
                sort(pixels.begin(), pixels.end());
                edited(x, y, 0, c) = pixels[0];
                pixels.clear();
            }
        }
    }
}

void applyMaximumFilter(CImg<int> &original, CImg<int> &edited, char* maxD){
    int maxDepth = atoi(maxD);
    vector<int> pixels;
    for (int x = 0; x < original.width(); x++) {
        for (int y = 0; y < original.height(); y++) {
            for (int c = 0; c < 3; c++) {

                for (int xx = 0; xx < maxDepth*2 + 1; xx++) {
                    for (int yy = 0; yy < maxDepth*2 + 1; yy++) {
                        if (x - maxDepth + xx >= 0 && x - maxDepth + xx < original.width() && y - maxDepth + yy >= 0 && y - maxDepth + yy < original.height()) {
                            pixels.push_back(original(x - maxDepth + xx, y - maxDepth + yy, 0, c));
                        }
                    }
                }
                sort(pixels.begin(), pixels.end());
                edited(x, y, 0, c) = pixels[pixels.size()-1];
                pixels.clear();
            }
        }
    }
}
