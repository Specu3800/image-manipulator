#ifndef ANALYSIS_MANIPULATIONS
#define ANALYSIS_MANIPULATIONS

#include "../../lib/CImg.templ"

using namespace std;
using namespace cimg_library;

float getMeanSquareError(CImg<int> &image1, CImg<int> &image2, float &result);
float getPeakMeanSquareError(CImg<int> &image1, CImg<int> &image2, float &result);
float getSignalToNoiseRatio(CImg<int> &image1, CImg<int> &image2, float &result);
float getPeakSignalToNoiseRatio(CImg<int> &image1, CImg<int> &image2, float &result);
float getMaximumDifference(CImg<int> &image1, CImg<int> &image2, float &result);

#endif //ANALYSIS_MANIPULATIONS


