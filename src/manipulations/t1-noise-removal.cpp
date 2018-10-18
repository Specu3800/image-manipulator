#include <iostream>
#include <vector>
#include <algorithm>
#include "../../lib/CImg.templ"
#include "t1-noise-removal.h"
#include "t0-other.h"

using namespace std;
using namespace cimg_library;

void applyAdaptiveMedianFilter(CImg<int> &original, CImg<int> &edited, char* maxD){
    int maxDepth = atoi(maxD);
    if (maxDepth < 1) {cout << "Wrong depth value. \nType --help to view information about available commands." << endl; exit(0);}
    vector<int> pixels;
    int currDepth;
    for (int x = 0; x < original.width(); x++) {
        displayProgress(x, original.width()-1);
        for (int y = 0; y < original.height(); y++) {
            for (int s = 0; s < original.spectrum(); s++) {

                currDepth = 1;
                while(true) {

                    for (int xx = 0; xx < currDepth * 2 + 1; xx++) {
                        for (int yy = 0; yy < currDepth * 2 + 1; yy++) {
                            if (x - currDepth + xx >= 0 && x - currDepth + xx < original.width() && y - currDepth + yy >= 0 && y - currDepth + yy < original.height()) {
                                pixels.push_back(original(x - currDepth + xx, y - currDepth + yy, 0, s));
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
                        int B1 = original(x, y, 0, s) - zmin;
                        int B2 = original(x, y, 0, s) - zmax;

                        if (B1 > 0 && B2 < 0) edited(x, y, 0, s) = original(x, y, 0, s);
                        else edited(x, y, 0, s) = zmed;

                        break;
                    } else {
                        currDepth++;
                        if(currDepth > maxDepth) {
                            edited(x, y, 0, s) = original(x, y, 0, s);
                            break;
                        }
                    }
                }
                pixels.clear();
            }
        }
    }
}

void applyMinimumFilter(CImg<int> &original, CImg<int> &edited, char* d){
    int depth = atoi(d);
    if (depth < 1) {cout << "Wrong depth value. \nType --help to view information about available commands." << endl; exit(0);}
    vector<int> pixels;
    for (int x = 0; x < original.width(); x++) {
        displayProgress(x, original.width()-1);
        for (int y = 0; y < original.height(); y++) {
            for (int s = 0; s < original.spectrum(); s++) {

                for (int xx = 0; xx < depth*2 + 1; xx++) {
                    for (int yy = 0; yy < depth*2 + 1; yy++) {
                        if (x - depth + xx >= 0 && x - depth + xx < original.width() && y - depth + yy >= 0 && y - depth + yy < original.height()) {
                            pixels.push_back(original(x - depth + xx, y - depth + yy, 0, s));
                        }
                    }
                }

                sort(pixels.begin(), pixels.end());
                edited(x, y, 0, s) = pixels[0];
                pixels.clear();
            }
        }
    }
}

void applyMaximumFilter(CImg<int> &original, CImg<int> &edited, char* d){
    int depth = atoi(d);
    if (depth < 1) {cout << "Wrong depth value. \nType --help to view information about available commands." << endl; exit(0);}
    vector<int> pixels;
    for (int x = 0; x < original.width(); x++) {
        displayProgress(x, original.width()-1);
        for (int y = 0; y < original.height(); y++) {
            for (int s = 0; s < original.spectrum(); s++) {

                for (int xx = 0; xx < depth*2 + 1; xx++) {
                    for (int yy = 0; yy < depth*2 + 1; yy++) {
                        if (x - depth + xx >= 0 && x - depth + xx < original.width() && y - depth + yy >= 0 && y - depth + yy < original.height()) {
                            pixels.push_back(original(x - depth + xx, y - depth + yy, 0, s));
                        }
                    }
                }

                sort(pixels.begin(), pixels.end());
                edited(x, y, 0, s) = pixels[pixels.size()-1];
                pixels.clear();
            }
        }
    }
}
void applyMedianFilter(CImg<int> &original, CImg<int> &edited, char* d){
    int depth = atoi(d);
    if (depth < 1) {cout << "Wrong depth value. \nType --help to view information about available commands." << endl; exit(0);}
    vector<int> pixels;
    for (int x = 0; x < original.width(); x++) {
        displayProgress(x, original.width()-1);
        for (int y = 0; y < original.height(); y++) {
            for (int s = 0; s < original.spectrum(); s++) {

                for (int xx = 0; xx < depth * 2 + 1; xx++) {
                    for (int yy = 0; yy < depth * 2 + 1; yy++) {
                        if (x - depth + xx >= 0 && x - depth + xx < original.width() && y - depth + yy >= 0 && y - depth + yy < original.height()) {
                            pixels.push_back(original(x - depth + xx, y - depth + yy, 0, s));
                        }
                    }
                }

                sort(pixels.begin(), pixels.end());
                if (pixels.size() % 2 == 0) edited(x, y, 0, s) = (pixels[pixels.size() / 2 - 1] + pixels[pixels.size() / 2]) / 2;
                else edited(x, y, 0, s) = pixels[pixels.size() / 2];
                pixels.clear();
            }
        }
    }
}
