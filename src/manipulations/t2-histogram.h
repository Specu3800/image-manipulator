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
    ~Histogram();

    void calculateHistogram(CImg<int> &name);

    CImg<int>* getUniformHistogramGraph(int, bool);
    CImg<int>* getCumulativeHistogramGraph(int, bool);

    void displayUniformHistogram(int, bool);
    void displayCumulativeHistogram(int, bool);
    void displayUniformValues(int);

private:
    void initialize();
    void calculateHistogram();
    CImg<int>* getHistogramGraph(int, int**);
    CImg<int>* getScaleHistogramGraph(int, int**);
};




#endif //HISTOGRAM
