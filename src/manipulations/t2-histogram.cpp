//
// Created by mike on 28.10.18.
//

#include <iostream>
#include <cmath>
#include "t2-histogram.h"
#include "t0-other.h"


using namespace std;
using namespace cimg_library;

void getHistogram(CImg<int> &image, int* R, int* G, int* B){
    for (int i = 0; i < 256; i++) {
        R[i] = 0;
        G[i] = 0;
        B[i] = 0;
    }
    for (int x = 0; x < image.width(); x++){
        for (int y = 0; y < image.height(); y++)
        {
            R[image(x, y, 0, 0)]++;
            G[image(x, y, 0, 1)]++;
            B[image(x, y, 0, 2)]++;
        }
    }


}
CImg<int>* getHistogramGraph(int* R, int* G, int* B, int RGB){
    CImg<int>* graph = new CImg<int>(256, 256, 1, 3, 255);
    int* channel;
    switch (RGB){
        case 0:
            channel = R;
            break;
        case 1:
            channel = G;
            break;
        case 2:
            channel = B;
            break;
        default:
            return;
            break;
    }

    for (int x = 0; x < graph.width(); x++)
    {
        for (int y = 0; y < channel[x]; y++)
        {
            graph(x, y, 0, RGB) = 0;
        }
    }


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

