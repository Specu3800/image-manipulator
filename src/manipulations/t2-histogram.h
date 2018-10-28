#ifndef HISTOGRAM
#define HISTOGRAM

#include "../../lib/CImg.templ"
#include <vector>

using namespace std;
using namespace cimg_library;


class Histogram{
private:
    CImg<int>* sourceImage;
    int* R;
    int* G;
    int* B;
    void createHistogram();

public:
    Histogram(CImg<int> &nazwa);

};


void getHistogram(int* R, int* G, int* B);

#endif //HISTOGRAM
