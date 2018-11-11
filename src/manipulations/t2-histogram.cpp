#include <iostream>
#include <cmath>
#include "t2-histogram.h"
#include "t0-other.h"


using namespace std;
using namespace cimg_library;

Histogram::Histogram(CImg<int> &name){
    this->sourceImage = &name;
    this->sourceImageW = this->sourceImage->width();
    this->sourceImageH = this->sourceImage->height();
    this->sourceImageP = this->sourceImage->width() * this->sourceImage->height();
    initialize();
    calculateHistogram();
}

Histogram::Histogram() {
    initialize();
}

Histogram::~Histogram() {
}


void Histogram::calculateHistogram() {
    //uniform
    for (int x = 0; x < this->sourceImage->width(); x++){
        for (int y = 0; y < this->sourceImage->height(); y++) {
            for (int c = 0; c < this->sourceImage->spectrum(); c++) {
                this->uniform[c][(*this->sourceImage)(x, y, 0, c)]++;
            }
        }
    }
    //cumulative
    for(int c = 0; c < 3; c++){
        cumulative[c][0] = uniform[c][0];
        for(int i = 1; i < 256; i++)
            cumulative[c][i] = cumulative[c][i-1] + uniform[c][i];
    }
    //probability
    for(int c = 0; c < 3; c++){
        for(int i = 0; i < 256; i++)
            probability[c][i] = ((double)(uniform[c][i]))/(sourceImage->width()*sourceImage->height());
    }
}

void Histogram::calculateHistogram(CImg<int> &name) {
    this->sourceImage = &name;
    calculateHistogram();
}

CImg<int> *Histogram::getUniformHistogramGraph(int channel, bool scale) {


    if (scale) return getScaleHistogramGraph(channel, uniform);
    else return getHistogramGraph(channel, uniform);
}

CImg<int>* Histogram::getCumulativeHistogramGraph(int channel, bool scale) {
    if (scale) return getScaleHistogramGraph(channel, cumulative);
    else return getHistogramGraph(channel, cumulative);
}

void Histogram::displayUniformHistogram(int channel, bool scale){
    (*this->getUniformHistogramGraph(channel, scale)).display("HISTOGRAM", false);
}
void Histogram::displayCumulativeHistogram(int channel, bool scale){
    (*this->getCumulativeHistogramGraph(channel, scale)).display("HISTOGRAM", false);
}

void Histogram::displayUniformValues(int channel) {
    cout << "Values of histogram for channel " << channel << ":" << endl;
    for (int i = 0; i < 256; i++){
        cout << i << ": " << uniform[channel][i] << endl;
    }
}


CImg<int> *Histogram::getHistogramGraph(int channel, int** values) {
    int maxH = 0;
    for (int i = 0; i < 256; i++) {
        if (values[channel][i] > maxH) {
            maxH = values[channel][i];
        }
    }

    CImg<int>* graph = new CImg<int>(256 + 2, maxH, 1, 3, 255);

    for (int x = 1; x < 257 ; x++) {
        for (int y = graph->height() - 1; y > graph->height() - values[channel][x-1] - 1; y--) {
            for (int c = 0; c < 3; c++) {
                (*graph)(x, y, 0, c) = 0;
            }
        }
    }
    return graph;
}

CImg<int> *Histogram::getScaleHistogramGraph(int channel, int** values) {
    int* valuesCopy = new int[256];
    for (int i = 0; i < 256; i++) {
        valuesCopy[i] = values[channel][i];
    }

    int maxH = 0;
    int index = 0;
    for (int i = 0; i < 256; i++) {
        if (valuesCopy[i] > maxH) {
            maxH = valuesCopy[i];
            index = i;
        }
    }

    while(valuesCopy[index] > 256){
        for (int i = 0; i < 256; i++) {
            valuesCopy[i] /= 2;
        }
    }

    CImg<int>* graph = new CImg<int>(256, 256, 1, 3, 255);

    for (int x = 0; x < 256; x += 2) {
        for (int y = graph->height() - 1; y > graph->height() - valuesCopy[x] - 1; y--) {
            for (int c = 0; c < 3; c++) {
                (*graph)(x, y, 0, c) = 0;
                (*graph)(x+1, y, 0, c) = 0;
            }
        }
    }
    return graph;
}

void Histogram::initialize() {
    this->uniform = new int*[3];
    this->cumulative = new int*[3];
    this->probability = new double*[3];
    for (int c = 0; c < 3; c++) {
        this->uniform[c] = new int[256];
        this->cumulative[c] = new int[256];
        this->probability[c] = new double[256];
        for (int j = 0; j < 256; j++) {
            this->uniform[c][j] = 0;
            this->cumulative[c][j] = 0;
            this->probability[c][j] = 0;
        }
    }
}







