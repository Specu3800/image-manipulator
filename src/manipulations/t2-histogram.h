#ifndef HISTOGRAM
#define HISTOGRAM

#include "../../lib/CImg.templ"
#include "t2-histogram.h"

using namespace std;
using namespace cimg_library;


class Histogram{
public:
    CImg<int>* sourceImage;

    int** uniform;
    int** cumulative;
    double** probability;

    bool isUniformCalculated;
    bool isCumulativeCalculated;

    Histogram();
    Histogram(CImg<int> &nazwa);

    void calculateHistogram(CImg<int> &name);

    CImg<int>* getUniformHistogramGraph(int);
    CImg<int>* getCumulativeHistogramGraph(int);

    void displayUniformHistogram(int);
    void displayCumulativeHistogram(int);

private:
    void initialize();
    void calculateHistogram();
    CImg<int>* getHistogramGraph(int, int**);
};




#endif //HISTOGRAM
