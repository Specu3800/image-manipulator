#ifndef BASIC
#define BASIC

#include "lib/CImg.templ"

using namespace std;
using namespace cimg_library;

CImg<int>& changeBrightness(CImg<int> &original, int value);
CImg<int>& changeContrast(CImg<int> &original, float value);
CImg<int>& changeContrast2(CImg<int> &original, float value);
CImg<int>& changeToNegative(CImg<int> &original);

#endif //BASIC


