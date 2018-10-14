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
    float PMSE = getMeanSquareError(img1, img2);

    float max = (img1(0, 0, 0, 0) + img1(0, 0, 0, 1) + img1(0, 0, 0, 2))/3;
    for (int x = 0; x < img1.width(); x++)
        for (int y = 0; y < img1.height(); y++)
        {
            if ((img1(x, y, 0, 0) + img1(x, y, 0, 1) + img1(x, y, 0, 2))/3 > max ) max = (img1(x, y, 0, 0) + img1(x, y, 0, 1) + img1(x, y, 0, 2))/3;
        }
    max *= max;
        PMSE /= max;
    return PMSE;
}

float getSignalToNoiseRatio(CImg<int> img1, CImg<int> img2){
    float divider = getMeanSquareError(img1, img2) * img1.width() * img1.height();
    float numerator = 0;
    for (int x = 0; x < img1.width(); x++)
        for (int y = 0; y < img1.height(); y++)
        {
            float mean = (img1(x, y, 0, 0) + img1(x, y, 0, 1) + img1(x, y, 0, 2))/3;
            mean *= mean;
            numerator += mean;
        }
        numerator /= divider;

    return 10 * log10(numerator);
}

float getPeakSignalToNoiseRatio(CImg<int> img1, CImg<int> img2){

    float max = (img1(0, 0, 0, 0) + img1(0, 0, 0, 1) + img1(0, 0, 0, 2))/3;
    for (int x = 0; x < img1.width(); x++)
        for (int y = 0; y < img1.height(); y++)
            if ((img1(x, y, 0, 0) + img1(x, y, 0, 1) + img1(x, y, 0, 2))/3 > max ) max = (img1(x, y, 0, 0) + img1(x, y, 0, 1) + img1(x, y, 0, 2))/3;
    max *= max;
    float sum = 0;
    for (int x = 0; x < img1.width(); x++)
        for (int y = 0; y < img1.height(); y++)
            sum += max;

    float divider = getMeanSquareError(img1, img2) * img1.width() * img1.height();

    sum /= divider;

    return 10 * log10(sum);
}

float getMaximumDifference(CImg<int> img1, CImg<int> img2){
    float MD = 0;
    for (int x = 0; x < img1.width(); x++)
        for (int y = 0; y < img1.height(); y++)
        {
            if (abs((img1(0, 0, 0, 0) + img1(0, 0, 0, 1) + img1(0, 0, 0, 2))/3 - (img2(0, 0, 0, 0) + img2(0, 0, 0, 1) + img2(0, 0, 0, 2))/3) > MD) MD = abs((img1(0, 0, 0, 0) + img1(0, 0, 0, 1) + img1(0, 0, 0, 2))/3 - (img2(0, 0, 0, 0) + img2(0, 0, 0, 1) + img2(0, 0, 0, 2))/3);
        }

        return MD;
}


//Similarity measures are compared in the following way: firstly, 
// we compute their values between the
//
// original image and the image with noise;
//
// next, between the
//
// original image and the image subjected to noise removal
//
//
// (we compare the two obtained values). These measures
// are computed according to the following formulas (M, N - the dimensions 
// of the images, f - the first image, f with a hat - the second image, 
// and the maximum value is computed w.r.t. the whole image): 

float doAnalysis(CImg<int> clean, CImg<int> dirty, CImg<int> edited, char* type){

    float g1, g2;
    string name;

    if (type == string("--mse")) {
        g1 = getMeanSquareError(clean, dirty);
        g2 = getMeanSquareError(clean, edited);
        name = "Mean Square Error";
    } else if (type == string("--pmse")) {
        g1 = getPeakMeanSquareError(clean, dirty);
        g2 = getPeakMeanSquareError(clean, edited);
        name = "Peak Mean Square Error";
    } else if (type == string("--snr")) {
        g1 = getSignalToNoiseRatio(clean, dirty);
        g2 = getSignalToNoiseRatio(clean, edited);
        name = "Signal To Noise Ratio";
    } else if (type == string("--psnr")) {
        g1 = getPeakSignalToNoiseRatio(clean, dirty);
        g2 = getPeakSignalToNoiseRatio(clean, edited);
        name = "Peak Signal To Noise Ratio";
    } else if (type == string("--md")) {
        g1 = getMaximumDifference(clean, dirty);
        g2 = getMaximumDifference(clean, edited);
        name = "MaximumDifference";
    }

    cout << name << " of original image compered to image with noise equals: " << g1 << endl;
    cout << name << " of original image and the image subjected to noise removal equals: " << g2 << endl;
    cout << "The ratio between those two equals: " << g1 << "/" << g2 << " = " << g1/g2 << endl;

    return 0;
}
