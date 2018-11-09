#include <iostream>
#include <vector>
#include <algorithm>
#include "../../lib/CImg.templ"
#include "t0-other.h"
#include "t2-quality-improvement.h"
#include "t2-histogram.h"

using namespace std;
using namespace cimg_library;

void applyExponentialPDF(CImg<int> &original, CImg<int> &edited, char *gm, Histogram &histogram){
    float gmin = atof(gm);
    for (int s = 0; s < original.spectrum(); s++) {

        float alpha = 0.015; //set custom alpha, different than parameter

        int* improvedColors = new int[256];
        for (int i = 0; i < 256; i++) { //apply histogram modification
            improvedColors[i] = gmin - 1.0/alpha *
                    log(1.0 - (1.0/(original.width()*original.height())) * histogram.cumulative[s][i]);
            improvedColors[i] = normalized(improvedColors[i]);
        }

        for (int x = 0; x < original.width(); x++) { //apply to image
            for (int y = 0; y < original.height(); y++) {
                edited(x, y, 0, s) = improvedColors[original(x, y, 0, s)];
            }
        }
    }

    Histogram newHistogram = Histogram(edited);
    newHistogram.displayUniformValues(0);
    ((*histogram.getUniformHistogramGraph(0, true)).append(*newHistogram.getUniformHistogramGraph(0, true), 'x', 1)).display("HISTOGRAM", false); //show difference in histogram
}

void applyLaplacianFilter(CImg<int> &original, CImg<int> &edited, char*, Histogram &histogram){

}

void applyRobertsOperatorFilter(CImg<int> &original, CImg<int> &edited, char*, Histogram &histogram){

}