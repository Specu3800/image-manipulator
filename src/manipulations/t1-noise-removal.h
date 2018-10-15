#ifndef NOISE_REMOVAL_MANIPULATIONS
#define NOISE_REMOVAL_MANIPULATIONS

#include "../../lib/CImg.templ"

using namespace std;
using namespace cimg_library;

void applyAdaptiveMedianFilter(CImg<int> &original, CImg<int> &edited, char*);
void applyMinimumFilter(CImg<int> &original, CImg<int> &edited, char*);
void applyMaximumFilter(CImg<int> &original, CImg<int> &edited, char*);

#endif //NOISE_REMOVAL_MANIPULATIONS


