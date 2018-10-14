#ifndef OTHER_MANIPULATIONS
#define OTHER_MANIPULATIONS

#include "../../lib/CImg.templ"

using namespace std;
using namespace cimg_library;

CImg<int> applyBilinearInterpolation(CImg<int>);
CImg<int> applyBilinearInterpolationSimple(CImg<int>);

int getR(int);
int getG(int);
int getB(int);
int getColor(int, int, int);

#endif //OTHER_MANIPULATIONS


