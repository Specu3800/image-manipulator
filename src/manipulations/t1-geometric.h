#ifndef GEOMETRIC
#define GEOMETRIC

#include "../../lib/CImg.templ"

using namespace std;
using namespace cimg_library;


void doHorizontalFlip(CImg<int> &original, CImg<int> &edited);
void doVerticalFlip(CImg<int> &original, CImg<int> &edited);
void doDiagonalFlip(CImg<int> &original, CImg<int> &edited);
void shrinkBy(CImg<int> &original, CImg<int> &edited, char*);
void enlargeBy(CImg<int> &original, CImg<int> &edited, char*);

#endif //GEOMETRIC


