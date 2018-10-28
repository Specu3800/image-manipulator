#ifndef HISTOGRAM
#define HISTOGRAM

#include "../../lib/CImg.templ"
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

    void createHistogram();

    CImg<int>* getHistogramGraph();
};

void applyExponentialPDF(CImg<int> &original, CImg<int> &edited, Histogram *histogram);



#endif //HISTOGRAM
