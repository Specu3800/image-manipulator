#include <iostream>
#include "../../lib/CImg.templ"
#include "t1-analysis.h"

using namespace std;
using namespace cimg_library;

float getMeanSquareError(CImg<int> &img1, CImg<int> &img2){

    float sum = 0;

    for (int x = 0; x < img1.width(); x++) {
        for(int y = 0; y < img1.height(); y++) {
            for (int c = 0; c < img1.spectrum(); c++) {
                sum += pow((img1(x, y, 0, c) - img2(x, y, 0, c)), 2);
            }
        }
    }

    float MSE = sum/(img1.width() * img1.height());
    return MSE;
}

float getPeakMeanSquareError(CImg<int> &img1, CImg<int> &img2) {

    float max = 0;

    for (int x = 0; x < img1.width(); x++){
        for (int y = 0; y < img1.height(); y++) {
            for (int c = 0; c < img1.spectrum(); c++) {
                if (img1(x, y, 0, c) > max)
                    max = img1(x, y, 0, c);
            }
        }
    }
    float PMSE = getMeanSquareError(img1, img2)/pow(max, 2);
    return PMSE;
}

float getSignalToNoiseRatio(CImg<int> &img1, CImg<int> &img2){

    float square = 0;

    for (int x = 0; x < img1.width(); x++){
        for (int y = 0; y < img1.height(); y++) {
            for (int c = 0; c < img1.spectrum(); c++) {
                square += pow(img1(x, y, 0, c), 2);
            }
        }
    }

    float SNR = 10 * log10(square/(getMeanSquareError(img1, img2) * img1.width() * img1.height()));
    return SNR;
}

float getPeakSignalToNoiseRatio(CImg<int> &img1, CImg<int> &img2){

    float max = 0;

    for (int x = 0; x < img1.width(); x++){
        for (int y = 0; y < img1.height(); y++){
                for (int c = 0; c < img1.spectrum(); c++) {
                    max += pow(img1(x, y, 0, c), 2);
            }
        }
    }

    float PSNR = 10 * log10(max/((getMeanSquareError(img1, img2)) * img1.width() * img1.height()));
    return PSNR;
}

float getMaximumDifference(CImg<int> &img1, CImg<int> &img2){

    float MD = 0;

    for (int x = 0; x < img1.width(); x++){
        for (int y = 0; y < img1.height(); y++) {
            for (int c = 0; c < img1.spectrum(); c++) {
                if (abs(img1(x, y, 0, c) - img2(x, y, 0, c)  > MD))
                    MD = abs(img1(x, y, 0, c) - img2(x, y, 0, c));
            }
        }
    }

    return MD;
}
