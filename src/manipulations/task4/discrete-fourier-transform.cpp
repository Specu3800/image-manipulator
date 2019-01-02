#include "discrete-fourier-transform.h"
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;
using namespace cimg_library;


CImg<int>& getFastFourierTransformInSpatialDomain(CImg<int> &original){
    CImg<int>* edited = new CImg<int>(original.width(), original.height(), 1, original.spectrum(), 0);

    return *edited;
}

CImg<int>& getInverseFastFourierTransformInSpatialDomain(CImg<int> &original){
    CImg<int>* edited = new CImg<int>(original.width(), original.height(), 1, original.spectrum(), 0);

    return *edited;
}
