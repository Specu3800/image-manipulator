#ifndef NOISE_REMOVAL_MANIPULATIONS
#define NOISE_REMOVAL_MANIPULATIONS

#include "../../lib/CImg.templ"

using namespace std;
using namespace cimg_library;

CImg<int> applyAdaptiveMedianFilter(CImg<int>);
CImg<int> applyMinimumFilter(CImg<int>);
CImg<int> applyMaximumFilter(CImg<int>);

#endif //NOISE_REMOVAL_MANIPULATIONS


