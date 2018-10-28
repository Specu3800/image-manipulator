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
    void createHistogram()

public:
    Histogram(CImg<int> &nazwa){
        this -> R = new int[256];
        this -> G = new int[256];
        this -> B = new int[256];
        this -> sourceImage = nazwa;
        createHistogram();
    }

};


void getHistogram(int* R, int* G, int* B);

#endif //HISTOGRAM
