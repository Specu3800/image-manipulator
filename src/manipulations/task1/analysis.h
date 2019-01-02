#ifndef ANALYSIS
#define ANALYSIS

#include "lib/CImg.templ"

using namespace std;
using namespace cimg_library;

float getMeanSquareError(CImg<int> &image1, CImg<int> &image2);
float getPeakMeanSquareError(CImg<int> &image1, CImg<int> &image2);
float getSignalToNoiseRatio(CImg<int> &image1, CImg<int> &image2);
float getPeakSignalToNoiseRatio(CImg<int> &image1, CImg<int> &image2);
float getMaximumDifference(CImg<int> &image1, CImg<int> &image2);

#endif //ANALYSIS


