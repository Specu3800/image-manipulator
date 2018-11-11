#ifndef FILTERS
#define FILTERS

#include "../../lib/CImg.templ"
#include "t2-histogram.h"

using namespace std;
using namespace cimg_library;

void applyExponentialPDF(CImg<int> &original, CImg<int> &edited, char*, Histogram &histogram);
void applyLaplacianFilter(CImg<int> &original, CImg<int> &edited, char*, Histogram &histogram);
void applyLaplacianFilterOptimised(CImg<int> &original, CImg<int> &edited, char*, Histogram &histogram);
void applyRobertsOperatorFilter(CImg<int> &original, CImg<int> &edited, char*, Histogram &histogram);

#endif //FILTERS
