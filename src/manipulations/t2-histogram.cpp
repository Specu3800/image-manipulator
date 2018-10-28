//
// Created by mike on 28.10.18.
//

#include <iostream>
#include <cmath>
#include "t2-histogram.h"
#include "t0-other.h"


using namespace std;
using namespace cimg_library;

void getHistogram(CImg<int> &imagage, int* R, int* G, int* B){
    int hist[256];
    for (int i = 0; i < 256; i++)
        hist[i] = 0;
}
CImg<int>* getHistogramGraph(int* R, int* G, int* B){
    int hist[256];
    for (int i = 0; i < 256; i++)
        hist[i] = 0;
}

void applyExponentialPDF(CImg<int> &original, CImg<int> &edited){
    //int depth = atoi(d);
    //if (depth < 1) {cout << "Wrong depth value. \nType --help to view information about available commands." << endl; exit(0);}
    vector<int> pixels;
    for (int x = 0; x < original.width(); x++) {
        displayProgress(x, original.width()-1);
        for (int y = 0; y < original.height(); y++) {
            for (int s = 0; s < original.spectrum(); s++) {
                float gmin = 5;
                int alpha = 3;
                int HM = 300;
                edited(x, y, 0, s) = gmin - (1.0/alpha) *
                        log(1 - 1/(original.width()*original.height()) * HM);
            }
        }
    }
}

