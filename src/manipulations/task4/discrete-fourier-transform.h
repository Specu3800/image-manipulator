#ifndef DISCRETE_FOURIER_TRANSFORM
#define DISCRETE_FOURIER_TRANSFORM

#include "lib/CImg.templ"
#include <vector>
#include <complex>


using namespace std;
using namespace cimg_library;

void getDFT(CImg<int> &original);
//CImg<int>& getInverseFastFourierTransformInSpatialDomain(CImg<int> &original);

#endif //DISCRETE_FOURIER_TRANSFORM
