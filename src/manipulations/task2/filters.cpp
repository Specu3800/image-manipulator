#include <iostream>
#include <vector>
#include <algorithm>
#include "lib/CImg.templ"
#include "helpers.h"
#include "filters.h"
#include "histogram.h"

using namespace std;
using namespace cimg_library;

CImg<int>& applyExponentialPDF(CImg<int> &original, int Gmin, int Gmax, Histogram &histogram){
    if (Gmax == 0) {cout << "Wrong Gmax value. \nType --help to view information about available commands." << endl; exit(0);}
    CImg<int>* edited = new CImg<int>(original.width(), original.height(), 1, original.spectrum(), 0);
    for (int c = 0; c < original.spectrum(); c++) {

        double alpha = (log(1 ) + log(1.0/(original.width()*original.height()))) / (Gmin - Gmax);

        int* improvedColors = new int[256];
        for (int m = 0; m < 256; m++) { //apply histogram modification
            improvedColors[m] = Gmin - 1.0/alpha *
                    log(1.0 - (1.0/(original.width()*original.height())) * histogram.cumulative[c][m]);
            improvedColors[m] = normalize(improvedColors[m]);
        }

        for (int x = 0; x < original.width(); x++) { //apply to image
            for (int y = 0; y < original.height(); y++) {
                (*edited)(x, y, c) = improvedColors[original(x, y, c)];
            }
        }
    }
//TO DISPLAY AND SAVE HISTOGRAM
//    Histogram newHistogram = Histogram(*edited);
    //newHistogram.displayUniformValues(0);
//    ((*histogram.getUniformHistogramGraph(0, true)).append(*newHistogram.getUniformHistogramGraph(0, true), 'x', 1)).display("HISTOGRAM", false); //show difference in histogram
//    histogram.getUniformHistogramGraph(0, true)->save("original_histogram.png");
//    newHistogram.getUniformHistogramGraph(0, true)->save("edited_histogram.png");

    return *edited;
}

CImg<int>& applyExponentialPDFSeparately(CImg<int> &original, int Gmin, int Gmax){
    CImg<int>* edited = new CImg<int>(original.width(), original.height(), 1, original.spectrum(), 0);
    CImg<int>* combined = new CImg<int>(original.width(), original.height(), 1, original.spectrum(), 0);
    for (int x = 0; x < original.width(); x++) { //apply to image
        for (int y = 0; y < original.height(); y++) {
            for (int c = 0; c < original.spectrum(); c++) {
                (*combined)(x, y, c) = (original(x, y, 0 , 0) + original(x, y, 0 , 1) + original(x, y, 0 , 2))/3;
            }
        }
    }

    Histogram combinedHistogram = Histogram(*combined);
    *edited = applyExponentialPDF(*combined, Gmin, Gmax, combinedHistogram);


    for (int x = 0; x < original.width(); x++) { //apply to image
        for (int y = 0; y < original.height(); y++) {
            double k = original(x, y, 0, 0) / ((*edited)(x, y, 0, 0)+0.00000001) ;
            for (int c = 0; c < original.spectrum(); c++) {
                (*edited)(x, y, c) = normalize(original(x, y, c) / k);
            }
        }
    }

    return *edited;
}

CImg<int>& applyLaplacianFilter(CImg<int> &original, int maskNumber){
    CImg<int>* edited = new CImg<int>(original.width(), original.height(), 1, original.spectrum(), 0);

    int filterMask1[3][3] = {-1, -1, -1, -1, 8, -1, -1, -1, -1};
    int filterMask2[3][3] = {0, -1, 0, -1, 4, -1, 0, -1, 0};
    int filterMask3[3][3] = {1, -2, 1, -2, 4, -2, 1, -2, 1};

    int filterMask[3][3];
    if(maskNumber == 1) {copy(&filterMask1[0][0], &filterMask1[0][0]+9, &filterMask[0][0]);}
    else if(maskNumber == 2){copy(&filterMask2[0][0], &filterMask2[0][0]+9, &filterMask[0][0]);}
    else if(maskNumber == 3){copy(&filterMask3[0][0], &filterMask3[0][0]+9, &filterMask[0][0]);}
    else {cout << "Wrong mask value. \nType --help to view information about available commands." << endl; exit(0);}

    for (int x = 1; x < original.width() - 1; x++)
    {
        for (int y = 1; y < original.height() - 1; y++)
        {
            for (int c = 0; c < original.spectrum(); c++)
            {
                int p = 0;
                int q = 0;
                int pixelValue = 0;

                for (int i = x - 1; i < x + 2; i++)
                {
                    p = 0;
                    for (int j = y - 1; j < y + 2; j++)
                    {
                        pixelValue += original(i, j, 0, c) * filterMask[p][q];
                        p++;
                    }
                    q++;
                }
                (*edited)(x, y, c) = normalize(pixelValue);
            }
        }
    }
    return *edited;
}

CImg<int>& applyLaplacianFilterOptimised(CImg<int> &original){

    int* tabFor1 = new int[256];
    int* tabFor8 = new int[256];
    for(int i = 0; i < 256; i++){
        tabFor1[i] = -i;
        tabFor8[i] = 8*i;
    }

    CImg<int>* edited = new CImg<int>(original.width(), original.height(), 1, original.spectrum(), 0);
    for (int x = 1; x < original.width() - 1; x++) {
        for (int y = 1; y < original.height() - 1; y++) {
            for (int c = 0; c < original.spectrum(); c++) {
                (*edited)(x, y, c) = normalize(
                        tabFor1[original(x - 1, y - 1, 0, c)] + tabFor1[original(x, y - 1, 0, c)] +
                        tabFor1[original(x + 1, y - 1, 0, c)] +
                        tabFor1[original(x - 1, y, 0, c)] + tabFor8[original(x, y, 0, c)] +
                        tabFor1[original(x + 1, y, 0, c)] +
                        tabFor1[original(x - 1, y + 1, 0, c)] + tabFor1[original(x, y + 1, 0, c)] +
                        tabFor1[original(x + 1, y + 1, 0, c)]
                );
            }
        }
    }
    return *edited;
}

CImg<int>& applyRobertsOperatorFilter(CImg<int> &original){
    CImg<int>* edited = new CImg<int>(original.width(), original.height(), 1, original.spectrum(), 0);
    for (int x = 1; x < original.width() - 1; x++)
    {
        for (int y = 1; y < original.height() - 1; y++)
        {
            for (int c = 0; c < original.spectrum(); c++)
            {
               (*edited)(x, y, c) = normalize(abs(original(x, y, c) - original(x + 1, y + 1, 0, c)) +
                                              abs(original(x, y + 1, 0, c) - original(x + 1, y, 0, c)));
            }
        }
    }
    return *edited;
}

CImg<int>& applySobelOperatorFilter(CImg<int> &original){
    CImg<int>* edited = new CImg<int>(original.width(), original.height(), 1, original.spectrum(), 0);
    for (int x = 1; x < original.width() - 1; x++)
    {
        for (int y = 1; y < original.height() - 1; y++)
        {
            for (int c = 0; c < original.spectrum(); c++)
            {
                float xx = original(x + 1, y - 1, 0, c) + 2*original(x + 1, y, 0, c) + original(x + 1, y + 1, 0, c) - original(x - 1, y - 1, 0, c) - 2*original(x - 1, y, 0, c) - original(x - 1, y + 1, 0, c);
                float yy = original(x - 1, y - 1, 0, c) + 2*original(x, y - 1, 0, c) + original(x + 1, y - 1, 0, c) - original(x - 1, y + 1, 0, c) - 2*original(x, y + 1, 0, c) - original(x + 1, y + 1, 0, c);
                xx *= xx;
                yy *= yy;
                (*edited)(x, y, c) = normalize(sqrt(xx + yy));
            }
        }
    }
    return *edited;
}
