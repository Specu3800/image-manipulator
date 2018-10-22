#ifndef BASIC_MANIPULATIONS
#define BASIC_MANIPULATIONS

#include "../../lib/CImg.templ"

using namespace std;
using namespace cimg_library;

void changeBrightness(CImg<int> &original, CImg<int> &edited, char *value);
void changeContrast(CImg<int> &original, CImg<int> &edited, char *value);
void changeContrast2(CImg<int> &original, CImg<int> &edited, char *value);
void changeToNegative(CImg<int> &original, CImg<int> &edited);

#endif //BASIC_MANIPULATIONS


