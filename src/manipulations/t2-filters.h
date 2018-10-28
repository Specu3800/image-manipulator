#ifndef FILTERS
#define FILTERS

#include "../../lib/CImg.templ"

using namespace std;
using namespace cimg_library;

void applyLaplacianFilter(CImg<int> &original, CImg<int> &edited, char*);
void applyRobertsOperatorFilter(CImg<int> &original, CImg<int> &edited, char*);

#endif //FILTERS
