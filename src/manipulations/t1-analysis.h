#ifndef ANALYSIS_MANIPULATIONS
#define ANALYSIS_MANIPULATIONS

#include "../../lib/CImg.templ"

using namespace std;
using namespace cimg_library;

float getMeanSquareError(CImg<int>, CImg<int>);
float getPeakMeanSquareError(CImg<int>, CImg<int>);
float getSignalToNoiseRatio(CImg<int>, CImg<int>);
float getPeakSignalToNoiseRatio(CImg<int>, CImg<int>);
float getMaximumDifference(CImg<int>, CImg<int>);

#endif //ANALYSIS_MANIPULATIONS


