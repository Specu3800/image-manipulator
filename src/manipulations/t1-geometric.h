#ifndef GEOMETRIC_MANIPULATIONS
#define GEOMETRIC_MANIPULATIONS

#include "../../lib/CImg.templ"

using namespace std;
using namespace cimg_library;


CImg<int> doHorizontalFlip(CImg<int>);
CImg<int> doVerticalFlip(CImg<int>);
CImg<int> doDiagonalFlip(CImg<int>);
CImg<int> shrinkBy(CImg<int>, char*);
CImg<int> enlargeBy(CImg<int>, char*);
CImg<int> simpleEnlargeBy(CImg<int>, char*);

#endif //GEOMETRIC_MANIPULATIONS


