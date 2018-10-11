#ifndef BASIC_MANIPULATIONS
#define BASIC_MANIPULATIONS

#include "../../lib/CImg.templ"

using namespace std;
using namespace cimg_library;
CImg<int> changeBrightness(CImg<int>, char*);
CImg<int> changeContrast(CImg<int>, char*);
CImg<int> changeToNegative(CImg<int>);

#endif //IMAGE_MANIPULATOR_MANIPULATIONS_H


