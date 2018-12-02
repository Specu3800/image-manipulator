#ifndef SEGMENTATION
#define SEGMENTATION

#include "../../lib/CImg.templ"

using namespace std;
using namespace cimg_library;

struct Pixel;
struct Region;

CImg<int>& applySegmentation(CImg<int> &original, int intensity, int threshold);
bool linearThreshold(CImg<int> &original, int threshold, int x1, int y1, int x2, int y2);
bool euclideanThreshold(CImg<int> &original, int threshold, int x1, int y1, int x2, int y2);
void segmentationRecursive(CImg<int> &original, CImg<int> &edited, int x, int y, int threshold, int N, int M, bool alreadyInRegion[][512], Pixel seed, Region* region);

#endif //SEGMENTATION
