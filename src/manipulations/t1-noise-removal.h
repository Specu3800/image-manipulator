#ifndef NOISE_REMOVAL_MANIPULATIONS
#define NOISE_REMOVAL_MANIPULATIONS

#include "../../lib/CImg.templ"

using namespace std;
using namespace cimg_library;

CImg<int> applyAdaptiveMedianFilter(CImg<int>, char*);
CImg<int> applyMinimumFilter(CImg<int>, char*);
CImg<int> applyMaximumFilter(CImg<int>, char*);

#endif //NOISE_REMOVAL_MANIPULATIONS


