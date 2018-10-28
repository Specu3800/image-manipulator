//
// Created by mike on 28.10.18.
//

#include <iostream>
#include <cmath>
#include "t2-histogram.h"
#include "t0-other.h"


using namespace std;
using namespace cimg_library;

void Histogram::createHistogram() {
    for (int i = 0; i < 256; i++) {
        this->R[i] = 0;
        this->G[i] = 0;
        this->B[i] = 0;
    }

    for (int x = 0; x < this->sourceImage->width(); x++){
        for (int y = 0; y < this->sourceImage->height(); y++)
        {
            this->R[(*this->sourceImage)(x, y, 0, 0)]++;
            this->G[(*this->sourceImage)(x, y, 0, 1)]++;
            this->B[(*this->sourceImage)(x, y, 0, 2)]++;
        }
    }
}

Histogram::Histogram(CImg<int> &nazwa){
    this->R = new int[256];
    this->G = new int[256];
    this->B = new int[256];
    this->sourceImage = &nazwa;
    createHistogram();
}

CImg<int>* Histogram::getHistogramGraph(int *R, int *G, int *B, int RGB) {
    CImg<int>* graph = new CImg<int>(256, 3000, 1, 3, 255);
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
            return nullptr;
    }

    for (int x = 0; x < graph->width(); x++)
    {
        for (int y = graph->height() - 1; y > graph->height() - channel[x] -1; y--)
        {
            (*graph)(x, y, 0, 0) = 0;
            (*graph)(x, y, 0, 1) = 0;
            (*graph)(x, y, 0, 2) = 0;
        }
    }

    for (int x = 0; x < graph->width(); x++)
    {
        (*graph)(x, graph->height() - channel[x] - 1, 0, 0) = 0;
    }

    return graph;
}



void applyExponentialPDF(CImg<int> &original, CImg<int> &edited){
    //int depth = atoi(d);
    //if (depth < 1) {cout << "Wrong depth value. \nType --help to view information about available commands." << endl; exit(0);}
    vector<int> pixels;
    for (int x = 0; x < original.width(); x++) {
        displayProgress(x, original.width()-1);
        for (int y = 0; y < original.height(); y++) {
            //r
            float gmin = 5;
            int alpha = 3;
            int HM = 9;
            int sumaHM = 0;

            for (int m = 0; m < original(x, y, 0, 0); m++){
                //sumaHM += R[]
            }



            edited(x, y, 0, 0) = gmin - (1.0/alpha) *
                    log(1 - 1/(original.width()*original.height()) * HM);

        }
    }
}

