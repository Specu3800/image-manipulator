#ifndef FILTERS
#define FILTERS

#include "../../lib/CImg.templ"
#include "t2-histogram.h"

using namespace std;
using namespace cimg_library;

CImg<int>& applyExponentialPDF(CImg<int> &original, int Gmin, int Gmax, Histogram &histogram);
CImg<int>& applyExponentialPDFSeparately(CImg<int> &original, int Gmin, int Gmax);
CImg<int>& applyLaplacianFilter(CImg<int> &original, int maskNumber);
CImg<int>& applyLaplacianFilterOptimised(CImg<int> &original);
CImg<int>& applyRobertsOperatorFilter(CImg<int> &original);
CImg<int>& applySobelOperatorFilter(CImg<int> &original);

#endif //FILTERS
