#include <iostream>
#include <vector>
#include <algorithm>
#include "../../lib/CImg.templ"
#include "t0-other.h"
#include "t2-filters.h"
#include "t2-histogram.h"

using namespace std;
using namespace cimg_library;


void applyExponentialPDF(CImg<int> &original, CImg<int> &edited, char *a, Histogram &histogram){
    //run with: --hexponent 0.009 ../img/grey/lena.bmp edited.bmp
    float alpha = atof(a);
    Histogram improvedHistogram;
    for (int s = 0; s < 3; s++) {
        //find gmin as the smalles intensivity different than 0
        int gmin = 0;
        for (int i = 0; i < 256; i++) {
            if (histogram.cumulative[s][i] > 0) {
                gmin = i;
                break;
            }
        }

        //alpha = 0.009; //set custom alpha, different than parameter

        for (int i = 0; i < 256; i++) { //apply histogram modification
            improvedHistogram.uniform[s][i] = gmin - 1.0/alpha *
                    log(1.0 - (1.0/(original.width()*original.height())) * histogram.cumulative[s][i]);
        }

        for (int x = 0; x < original.width(); x++) { //apply to image
            for (int y = 0; y < original.height(); y++) {
                edited(x, y, 0, s) = normalized(improvedHistogram.uniform[s][original(x, y, 0, s)]);
            }
        }
    }
    histogram.displayUniformHistogram(0); //show difference in histogram
    Histogram d = Histogram(edited);
    d.displayUniformHistogram(0);
}

void applyLaplacianFilter(CImg<int> &original, CImg<int> &edited, char*, Histogram &histogram){

}

void applyRobertsOperatorFilter(CImg<int> &original, CImg<int> &edited, char*, Histogram &histogram){

}