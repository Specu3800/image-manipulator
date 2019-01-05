#ifndef SEGMENTATION
#define SEGMENTATION

#include "lib/CImg.templ"
#include <vector>

using namespace std;
using namespace cimg_library;

CImg<int>& getDiscreteFourierTransformInSpatialDomain(CImg<int> &original);
//CImg<int>& getInverseFastFourierTransformInSpatialDomain(CImg<int> &original);

#endif //SEGMENTATION
