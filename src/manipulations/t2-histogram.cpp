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


void Histogram::calculateHistogram() {
    //uniform
    for (int x = 0; x < this->sourceImage->width(); x++){
        for (int y = 0; y < this->sourceImage->height(); y++) {
            for (int s = 0; s < this->sourceImage->spectrum(); s++) {
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



CImg<int> *Histogram::getUniformHistogramGraph(int channel) {
    return getHistogramGraph(channel, uniform);
}

CImg<int>* Histogram::getCumulativeHistogramGraph(int channel) {
    return getHistogramGraph(channel, cumulative);
}

void Histogram::displayUniformHistogram(int channel){
    (*this->getUniformHistogramGraph(channel)).display("HISTOGRAM", false);
}
void Histogram::displayCumulativeHistogram(int channel){
    (*this->getCumulativeHistogramGraph(channel)).display("HISTOGRAM", false);
}


CImg<int> *Histogram::getHistogramGraph(int channel, int** values) {
    int** valuesCopy = values;

    int maxH = 0;
    int index = 0;
    for (int i = 0; i < 256; i++) {
        if (values[channel][i] > maxH) {
            maxH = values[channel][i];
            index = i;
        }
    }

    while(valuesCopy[channel][index] > 512){
        for (int i = 0; i < 256; i++) {
            valuesCopy[channel][i] /= 2;
        }
    }

    CImg<int>* graph = new CImg<int>(512, 512, 1, 3, 255);

    for (int x = 0; x < 512; x += 2) {
        for (int y = graph->height() - 1; y > graph->height() - values[channel][x/2] - 1; y--) {
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






