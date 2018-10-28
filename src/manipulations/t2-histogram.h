#ifndef HISTOGRAM
#define HISTOGRAM

#include "../../lib/CImg.templ"
#include <vector>

using namespace std;
using namespace cimg_library;

void getHistogram(CImg<int> &image, int* R, int* G, int* B);
CImg<int>* getHistogramGraph(int* R, int* G, int* B);

void applyExponentialPDF(CImg<int> &original, CImg<int> &edited);



#endif //HISTOGRAM
