#include <iostream>
#include <vector>
#include <algorithm>
#include "../../lib/CImg.templ"
#include "t0-other.h"
#include "t2-filters.h"
#include "t2-histogram.h"

using namespace std;
using namespace cimg_library;


void applyExponentialPDF(CImg<int> &original, CImg<int> &edited, char *gm, Histogram &histogram){
    int gmin = atoi(gm);
    //if (depth < 1) {cout << "Wrong depth value. \nType --help to view information about available commands." << endl; exit(0);}

    vector<int> pixels;
    for (int x = 0; x < original.width(); x++) {
        displayProgress(x, original.width()-1);
        for (int y = 0; y < original.height(); y++) {
            for (int s = 0; s < original.spectrum(); s++) {


                //r
                int alpha = 1;
                int sumaHM = 0;
                for (int m = 0; m < original(x, y, 0, s); m++) {
                    sumaHM += histogram.R[m];
                }
                edited(x, y, 0, s) = gmin - (1.0/alpha) *
                                            log(1 - (1.0/(original.width()*original.height())) * sumaHM);
                //edited(x, y, 0, s) = 250;
            }
        }
    }
}

void applyLaplacianFilter(CImg<int> &original, CImg<int> &edited, char*, Histogram &histogram){

}

void applyRobertsOperatorFilter(CImg<int> &original, CImg<int> &edited, char*, Histogram &histogram){

}