#include <iostream>
#include "../../lib/CImg.templ"
#include "t1-analysis.h"

using namespace std;
using namespace cimg_library;

float getMeanSquareError(CImg<int> &img1, CImg<int> &img2, float &result){

    float sum = 0;

    for (int x = 0; x < img1.width(); x++) {
        for(int y = 0; y < img1.height(); y++) {
            for (int s = 0; s < img1.spectrum(); s++) {
                sum += pow((img1(x, y, 0, s) - img2(x, y, 0, s)), 2);
            }
        }
    }

    float MSE = sum/(img1.width() * img1.height());
    result = MSE;
    return MSE;
}

float getPeakMeanSquareError(CImg<int> &img1, CImg<int> &img2, float &result) {

    float max = 0;

    for (int x = 0; x < img1.width(); x++){
        for (int y = 0; y < img1.height(); y++) {
            for (int s = 0; s < img1.spectrum(); s++) {
                if (img1(x, y, 0, s) > max)
                    max = img1(x, y, 0, s);
            }
        }
    }
    float PMSE = getMeanSquareError(img1, img2, result)/pow(max, 2);
    result = PMSE;
    return PMSE;
}

float getSignalToNoiseRatio(CImg<int> &img1, CImg<int> &img2, float &result){

    float square = 0;

    for (int x = 0; x < img1.width(); x++){
        for (int y = 0; y < img1.height(); y++) {
            for (int s = 0; s < img1.spectrum(); s++) {
                square += pow(img1(x, y, 0, s), 2);
            }
        }
    }

    float SNR = 10 * log10(square/(getMeanSquareError(img1, img2, result) * img1.width() * img1.height()));
    result = SNR;
    return SNR;
}

float getPeakSignalToNoiseRatio(CImg<int> &img1, CImg<int> &img2, float &result){

    float max = 0;

    for (int x = 0; x < img1.width(); x++){
        for (int y = 0; y < img1.height(); y++){
                for (int s = 0; s < img1.spectrum(); s++) {
                    max += pow(img1(x, y, 0, s), 2);
            }
        }
    }

    float PSNR = 10 * log10(max/((getMeanSquareError(img1, img2, result)) * img1.width() * img1.height()));
    result = PSNR;
    return PSNR;
}

float getMaximumDifference(CImg<int> &img1, CImg<int> &img2, float &result){

    float MD = 0;

    for (int x = 0; x < img1.width(); x++){
        for (int y = 0; y < img1.height(); y++) {
            for (int s = 0; s < img1.spectrum(); s++) {
                if (abs(img1(x, y, 0, s) - img2(x, y, 0, s)  > MD))
                    MD = abs(img1(x, y, 0, s) - img2(x, y, 0, s));
            }
        }
    }

    result = MD;
    return MD;
}
