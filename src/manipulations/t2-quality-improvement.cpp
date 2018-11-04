#include <iostream>
#include <vector>
#include <algorithm>
#include "../../lib/CImg.templ"
#include "t0-other.h"
#include "t2-quality-improvement.h"
#include "t2-histogram.h"

using namespace std;
using namespace cimg_library;

void applyExponentialPDF(CImg<int> &original, CImg<int> &edited, char *a, Histogram &histogram){
    //run with: --hexponent 0.009 ../img/grey/lena.bmp edited.bmp
    float alpha = atof(a);
    for (int s = 0; s < original.spectrum(); s++) {

        int gmin = 0; //find gmin as the smallest intensity different than 0
        for (int i = 0; i < 256; i++) {
            if (histogram.cumulative[s][i] > 0) {
                gmin = i;
                break;
            }
        }

        //alpha = 0.05; //set custom alpha, different than parameter
        //gmin = 10;

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
    ((*histogram.getUniformHistogramGraph(0, false)).append(*newHistogram.getUniformHistogramGraph(0, false), 'x', 1))
    .display("HISTOGRAM", false); //show difference in histogram
}

void applyLaplacianFilter(CImg<int> &original, CImg<int> &edited, char*, Histogram &histogram){

}

void applyRobertsOperatorFilter(CImg<int> &original, CImg<int> &edited, char*, Histogram &histogram){

}