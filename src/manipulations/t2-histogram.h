#ifndef HISTOGRAM
#define HISTOGRAM

#include "../../lib/CImg.templ"
#include "t2-histogram.h"
#include <vector>

using namespace std;
using namespace cimg_library;


class Histogram{
public:
    CImg<int>* sourceImage;

    int* R;
    int* G;
    int* B;

    Histogram(CImg<int> &nazwa);
    Histogram();

    void createHistogram();

    CImg<int>* getHistogramGraph();
};




#endif //HISTOGRAM
