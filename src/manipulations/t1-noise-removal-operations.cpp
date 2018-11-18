#include <iostream>
#include <algorithm>
#include "../../lib/CImg.templ"
#include "t1-noise-removal-operations.h"
#include "t0-other.h"

using namespace std;
using namespace cimg_library;

CImg<int>& applyAdaptiveMedianFilter(CImg<int> &original, int maxDepth){
    if (maxDepth < 1) {cout << "Wrong depth value. \nType --help to view information about available commands." << endl; exit(0);}
    CImg<int>* edited = new CImg<int>(original.width(), original.height(), 1, original.spectrum(), 0);
    int pixels[(maxDepth*2+1)*(maxDepth*2+1)];
    int pixelsSize = 0;
    int currDepth;
    for (int x = 0; x < original.width(); x++) {
        displayProgress(x, original.width()-1);
        for (int y = 0; y < original.height(); y++) {
            for (int c = 0; c < original.spectrum(); c++) {

                currDepth = 1;
                while(true) {
                    pixelsSize = 0;
                    for (int xx = 0; xx < currDepth * 2 + 1; xx++) {
                        for (int yy = 0; yy < currDepth * 2 + 1; yy++) {
                            if (x - currDepth + xx >= 0 && x - currDepth + xx < original.width() && y - currDepth + yy >= 0 && y - currDepth + yy < original.height()) {
                                pixels[pixelsSize] = (original(x - currDepth + xx, y - currDepth + yy, 0, c));
                                pixelsSize++;
                            }
                        }
                    }

                    sort(pixels, pixels + pixelsSize);
                    int zmed;
                    if (pixelsSize % 2 == 0) zmed = (pixels[pixelsSize / 2 - 1] + pixels[pixelsSize / 2]) / 2;
                    else zmed = pixels[pixelsSize / 2];
                    int zmin = pixels[0];
                    int zmax = pixels[pixelsSize - 1];

                    int A1 = zmed - zmin;
                    int A2 = zmed - zmax;

                    if (A1 > 0 && A2 < 0) {
                        int B1 = original(x, y, 0, c) - zmin;
                        int B2 = original(x, y, 0, c) - zmax;

                        if (B1 > 0 && B2 < 0) (*edited)(x, y, 0, c) = original(x, y, 0, c);
                        else (*edited)(x, y, 0, c) = zmed;

                        break;
                    } else {
                        currDepth++;
                        if(currDepth > maxDepth) {
                            (*edited)(x, y, 0, c) = original(x, y, 0, c);
                            break;
                        }
                    }
                }
            }
        }
    }
    return *edited;
}

CImg<int>& applyMinimumFilter(CImg<int> &original, int depth){
    if (depth < 1) {cout << "Wrong depth value. \nType --help to view information about available commands." << endl; exit(0);}
    CImg<int>* edited = new CImg<int>(original.width(), original.height(), 1, original.spectrum(), 0);
    int pixels[(depth*2+1)*(depth*2+1)];
    int pixelsSize = 0;
    for (int x = 0; x < original.width(); x++) {
        displayProgress(x, original.width()-1);
        for (int y = 0; y < original.height(); y++) {
            for (int c = 0; c < original.spectrum(); c++) {

                for (int xx = 0; xx < depth*2 + 1; xx++) {
                    for (int yy = 0; yy < depth*2 + 1; yy++) {
                        if (x - depth + xx >= 0 && x - depth + xx < original.width() && y - depth + yy >= 0 && y - depth + yy < original.height()) {
                            pixels[pixelsSize] = (original(x - depth + xx, y - depth + yy, 0, c));
                            pixelsSize++;
                        }
                    }
                }

                sort(pixels, pixels + pixelsSize);
                (*edited)(x, y, 0, c) = pixels[0];
                pixelsSize = 0;
            }
        }
    }
    return *edited;
}

CImg<int>& applyMaximumFilter(CImg<int> &original, int depth){
    if (depth < 1) {cout << "Wrong depth value. \nType --help to view information about available commands." << endl; exit(0);}
    CImg<int>* edited = new CImg<int>(original.width(), original.height(), 1, original.spectrum(), 0);
    int pixels[(depth*2+1)*(depth*2+1)];
    int pixelsSize = 0;
    for (int x = 0; x < original.width(); x++) {
        displayProgress(x, original.width()-1);
        for (int y = 0; y < original.height(); y++) {
            for (int c = 0; c < original.spectrum(); c++) {

                for (int xx = 0; xx < depth*2 + 1; xx++) {
                    for (int yy = 0; yy < depth*2 + 1; yy++) {
                        if (x - depth + xx >= 0 && x - depth + xx < original.width() && y - depth + yy >= 0 && y - depth + yy < original.height()) {
                            pixels[pixelsSize] = (original(x - depth + xx, y - depth + yy, 0, c));
                            pixelsSize++;
                        }
                    }
                }

                sort(pixels, pixels + pixelsSize);
                (*edited)(x, y, 0, c) = pixels[pixelsSize-1];
                pixelsSize = 0;
            }
        }
    }
    return *edited;
}

CImg<int>& applyMedianFilter(CImg<int> &original, int depth){
    if (depth < 1) {cout << "Wrong depth value. \nType --help to view information about available commands." << endl; exit(0);}
    CImg<int>* edited = new CImg<int>(original.width(), original.height(), 1, original.spectrum(), 0);
    int pixels[(depth*2+1)*(depth*2+1)];
    int pixelsSize = 0;
    for (int x = 0; x < original.width(); x++) {
        displayProgress(x, original.width()-1);
        for (int y = 0; y < original.height(); y++) {
            for (int c = 0; c < original.spectrum(); c++) {

                for (int xx = 0; xx < depth * 2 + 1; xx++) {
                    for (int yy = 0; yy < depth * 2 + 1; yy++) {
                        if (x - depth + xx >= 0 && x - depth + xx < original.width() && y - depth + yy >= 0 && y - depth + yy < original.height()) {
                            pixels[pixelsSize] = (original(x - depth + xx, y - depth + yy, 0, c));
                            pixelsSize++;
                        }
                    }
                }

                sort(pixels, pixels + pixelsSize);
                if (pixelsSize % 2 == 0) (*edited)(x, y, 0, c) = (pixels[pixelsSize / 2 - 1] + pixels[pixelsSize / 2]) / 2;
                else (*edited)(x, y, 0, c) = pixels[pixelsSize / 2];
                pixelsSize = 0;
            }
        }
    }
    return *edited;
}
