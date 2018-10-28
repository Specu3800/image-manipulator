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

Histogram::Histogram() {
    this->R = new int[256];
    this->G = new int[256];
    this->B = new int[256];
}


CImg<int>* Histogram::getHistogramGraph() {
    int graphWidth = 256;
    int separatorWidth = 3;
    int width = 8;
    int index = 0;

    CImg<int>* graph = new CImg<int>(width * graphWidth*3 + 2 * separatorWidth + 10, 5000, 1, 3, 255);

    for (int x = 0; x < graphWidth * width; x += width)
    {
        for (int r = 0; r < width; r++)
            for (int y = graph->height() - 1; y > graph->height() - R[index] - 1; y--)
            {
                (*graph)(x + r, y, 0, 1) = 0;
                (*graph)(x + r, y, 0, 2) = 0;
            }
        index++;
    }
    index = 0;
    for (int x = graphWidth * width; x < graphWidth * width + separatorWidth; x++)
        for (int y = 0; y < graph->height() - 1; y++)
        {
            (*graph)(x, y, 0, 1) = 0;
            (*graph)(x, y, 0, 2) = 0;
            (*graph)(x, y, 0, 0) = 0;
        }

    for (int x = graphWidth * width + separatorWidth; x < 2 *graphWidth * width + separatorWidth; x += width)
    {
        for (int y = graph->height() - 1; y > graph->height() - G[index] - 1; y--)
        {
            (*graph)(x, y, 0, 0) = 0;
            (*graph)(x, y, 0, 2) = 0;
        }
        index++;
    }
    index = 0;
    for (int x = 2*graphWidth * width + separatorWidth; x < 2*graphWidth * width + 2*separatorWidth; x += width)
        for (int y = 0; y < graph->height() - 1; y++)
        {
            (*graph)(x, y, 0, 1) = 0;
            (*graph)(x, y, 0, 2) = 0;
            (*graph)(x, y, 0, 0) = 0;
        }
    for (int x = 2*graphWidth * width + 2*separatorWidth; x < 3*graphWidth * width + 2*separatorWidth; x++)
    {
        for (int y = graph->height() - 1; y > graph->height() - B[index] -1; y--)
        {
            (*graph)(x, y, 0, 1) = 0;
            (*graph)(x, y, 0, 0) = 0;
        }
        index++;
    }


    return graph;
}


void applyExponentialPDF(CImg<int> &original, CImg<int> &edited, Histogram &histogram){
    //int depth = atoi(d);
    //if (depth < 1) {cout << "Wrong depth value. \nType --help to view information about available commands." << endl; exit(0);}


    vector<int> pixels;
    for (int x = 0; x < original.width(); x++) {
        displayProgress(x, original.width()-1);
        for (int y = 0; y < original.height(); y++) {


            //r
            float gmin = 50;
            int alpha = 3;
            int HM = 9;
            int sumaHM = 0;
            edited(x, y, 0, 0) = gmin - (1.0/alpha) *
                    log(1 - 1/(original.width()*original.height()) * HM);

        }
    }
}

