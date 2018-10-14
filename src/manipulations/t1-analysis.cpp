#include <iostream>
#include "../../lib/CImg.templ"
#include "t1-analysis.h"

using namespace std;
using namespace cimg_library;

float getMeanSquareError(CImg<int> img1, CImg<int> img2){

    float MSE = 0;
    float R = 0;
    float G = 0;
    float B = 0;

    for (int x = 0; x < img1.width(); x++)
    {
        for(int y = 0; y < img1.height(); y++)
        {
            float square = img1(x, y, 0, 0) - img2(x, y, 0, 0);
            square *= square;
            R += square;

            square = img1(x, y, 0, 1) - img2(x, y, 0, 1);
            square *= square;
            G += square;

            square = img1(x, y, 0, 2) - img2(x, y, 0, 2);
            square *= square;
            B += square;


        }
    }
    MSE = (R + G + B)/3;

    MSE = MSE/(img1.width() * img1.height());
    cout << "Mean Square Error for given images equals: " << MSE << ". " << endl;

    return MSE;
}

float getPeakMeanSquareError(CImg<int> img1, CImg<int> img2){
    return 0;
}

float getSignalToNoiseRatio(CImg<int> img1, CImg<int> img2){
    return 0;
}

float getPeakSignalToNoiseRatio(CImg<int> img1, CImg<int> img2){
    return 0;
}

float getMaximumDifference(CImg<int> img1, CImg<int> img2){
    return 0;
}
