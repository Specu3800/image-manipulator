#ifndef GEOMETRIC
#define GEOMETRIC

#include "lib/CImg.templ"

using namespace std;
using namespace cimg_library;

CImg<int>& doHorizontalFlip(CImg<int> &original);
CImg<int>& doVerticalFlip(CImg<int> &original);
CImg<int>& doDiagonalFlip(CImg<int> &original);
CImg<int>& shrinkBy(CImg<int> &original, float factor);
CImg<int>& enlargeBy(CImg<int> &original, float factor);

#endif //GEOMETRIC


