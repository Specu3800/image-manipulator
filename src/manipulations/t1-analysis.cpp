#include <iostream>
#include "../../lib/CImg.templ"
#include "t1-analysis.h"

using namespace std;
using namespace cimg_library;

float getMeanSquareError(CImg<int> &img1, CImg<int> &img2){

    float MSE = 0;
    float R = 0;
    float G = 0;
    float B = 0;

    for (int x = 0; x < img1.width(); x++) {
        for(int y = 0; y < img1.height(); y++) {
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

    cout << "Mean Square Error for those two images equils: " << MSE << endl;
    exit(0);
}

float getPeakMeanSquareError(CImg<int> &img1, CImg<int> &img2) {
    float PMSE = getMeanSquareError(img1, img2);

    float max = (img1(0, 0, 0, 0) + img1(0, 0, 0, 1) + img1(0, 0, 0, 2)) / 3;
    for (int x = 0; x < img1.width(); x++){
        for (int y = 0; y < img1.height(); y++) {
            if ((img1(x, y, 0, 0) + img1(x, y, 0, 1) + img1(x, y, 0, 2)) / 3 > max)
                max = (img1(x, y, 0, 0) + img1(x, y, 0, 1) + img1(x, y, 0, 2)) / 3;
        }
    }
    max *= max;
    PMSE /= max;

    cout << "Peak Mean Square Error for those two images equils: " << PMSE << endl;
    exit(0);
}

float getSignalToNoiseRatio(CImg<int> &img1, CImg<int> &img2){
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

    cout << "Signal To Noise Ratio for those two images equils: " << 10 * log10(numerator) << endl;
    exit(0);
}

float getPeakSignalToNoiseRatio(CImg<int> &img1, CImg<int> &img2){

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

    cout << "Peak Signal To Noise Ratio for those two images equils: " << 10 * log10(sum) << endl;
    exit(0);
}

float getMaximumDifference(CImg<int> &img1, CImg<int> &img2){
    float MD = 0;
    for (int x = 0; x < img1.width(); x++){
        for (int y = 0; y < img1.height(); y++) {
            if (abs((img1(0, 0, 0, 0) + img1(0, 0, 0, 1) + img1(0, 0, 0, 2))/3 - (img2(0, 0, 0, 0) + img2(0, 0, 0, 1) + img2(0, 0, 0, 2))/3) > MD)
                MD = abs((img1(0, 0, 0, 0) + img1(0, 0, 0, 1) + img1(0, 0, 0, 2))/3 - (img2(0, 0, 0, 0) + img2(0, 0, 0, 1) + img2(0, 0, 0, 2))/3);
        }
    }

    cout << "MaximumDifference for those two images equils: " << MD << endl;
    exit(0);
}
