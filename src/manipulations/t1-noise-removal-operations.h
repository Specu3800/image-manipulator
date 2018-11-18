#ifndef NOISE_REMOVAL_OPERATIONS
#define NOISE_REMOVAL_OPERATIONS

#include "../../lib/CImg.templ"

using namespace std;
using namespace cimg_library;

CImg<int>& applyAdaptiveMedianFilter(CImg<int> &original, int);
CImg<int>& applyMinimumFilter(CImg<int> &original, int);
CImg<int>& applyMaximumFilter(CImg<int> &original, int);
CImg<int>& applyMedianFilter(CImg<int> &original, int);

#endif //NOISE_REMOVAL_OPERATIONS


