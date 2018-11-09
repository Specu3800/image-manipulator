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
    ((*histogram.getUniformHistogramGraph(0, false)).append(*newHistogram.getUniformHistogramGraph(0, false), 'x', 1))
    .display("HISTOGRAM", false); //show difference in histogram
}
const int mask[3][3] = {-1, -1, -1, -1, 8, -1, -1, -1, -1};
//const int mask[3][3] = {0, -1, 0, -1, 4, -1, 0, -1, 0};
//const int mask[3][3] = {1, -2, 1, -2, 4, -2, 1, -2, 1};



void applyLaplacianFilter(CImg<int> &original, CImg<int> &edited, char*, Histogram &histogram){

    for (int channel = 0; channel < 3; channel++)
    {
        for (int x = 1; x < original.width() - 1; x++)
        {
            for (int y = 1; y < original.height() - 1; y++)
            {
                int p = 0;
                int q = 0;
                int pixelValue = 0;

                for (int i = x - 1; i < x + 2; i++)
                {
                    p = 0;
                    for (int j = y - 1; j < y + 2; j++)
                    {

                        pixelValue += original(i, j, 0, channel) * mask[p][q];
                        //cout << "!!" << pixelValue;
                        p++;
                    }
                    q++;
                }
                if (pixelValue > 255) pixelValue = 255;
                if (pixelValue < 0) pixelValue = 0;

               // cout << x << " " << y << " " << pixelValue << endl;
                edited(x, y, 0, channel) = pixelValue;

            }
        }


    }


}

void applyRobertsOperatorFilter(CImg<int> &original, CImg<int> &edited, char*, Histogram &histogram){

    for (int channel = 0; channel < 3; channel++)
    {
        for (int x = 1; x < original.width() - 1; x++)
        {
            for (int y = 1; y < original.height() - 1; y++)
            {
               edited(x, y, 0, channel) = abs(original(x, y, 0, channel) - original(x + 1, y + 1, 0, channel)) + abs(original(x, y + 1, 0, channel) - original(x + 1, y, 0, channel));

            }
        }


    }

}