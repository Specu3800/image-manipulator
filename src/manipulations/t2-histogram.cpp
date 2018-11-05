#include <iostream>
#include <cmath>
#include "t2-histogram.h"
#include "t0-other.h"


using namespace std;
using namespace cimg_library;

Histogram::Histogram(CImg<int> &name){
    this->sourceImage = &name;
    initialize();
    calculateHistogram();
}

Histogram::Histogram() {
    initialize();
}

Histogram::~Histogram() {
//    delete this->uniform;
//    delete this->cumulative;
//    delete this->probability;
}


void Histogram::calculateHistogram() {
    //uniform
    for (int x = 0; x < this->sourceImage->width(); x++){
        for (int y = 0; y < this->sourceImage->height(); y++) {
            for (int s = 0; s < this->sourceImage->spectrum(); s++) {
                //cout << "uni[" << s << "][" << (*this->sourceImage)(x, y, 0, s) << "]++          -    now has: " << uniform[s][(*this->sourceImage)(x, y, 0, s)] << "           it was for x,y: " << x << ", " << y << endl;
                //cout << "(*this->sourceImage)(x, y, 0, s) " << (*this->sourceImage)(x, y, 0, s) << endl;
                this->uniform[s][(*this->sourceImage)(x, y, 0, s)]++;
            }
        }
    }
    //cumulative
    for(int s = 0; s < 3; s++){
        cumulative[s][0] = uniform[s][0];
        for(int i = 1; i < 256; i++)
            cumulative[s][i] = cumulative[s][i-1] + uniform[s][i];
    }
    //probability
    for(int s = 0; s < 3; s++){
        for(int i = 0; i < 256; i++)
            probability[s][i] = ((double)(uniform[s][i]))/(sourceImage->width()*sourceImage->height());
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
            for (int s = 0; s < 3; s++) {
                (*graph)(x, y, 0, s) = 0;
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
            for (int s = 0; s < 3; s++) {
                (*graph)(x, y, 0, s) = 0;
                (*graph)(x+1, y, 0, s) = 0;
            }
        }
    }
    return graph;
}

void Histogram::initialize() {
    this->uniform = new int*[3];
    this->cumulative = new int*[3];
    this->probability = new double*[3];
    for (int s = 0; s < 3; s++) {
        this->uniform[s] = new int[256];
        this->cumulative[s] = new int[256];
        this->probability[s] = new double[256];
        for (int j = 0; j < 256; j++) {
            this->uniform[s][j] = 0;
            this->cumulative[s][j] = 0;
            this->probability[s][j] = 0;
        }
    }
}







