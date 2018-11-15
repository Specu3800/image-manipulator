#ifndef MORPHOLOGICAL_OPERATIONS
#define MORPHOLOGICAL_OPERATIONS

#include <vector>
#include "../../lib/CImg.templ"
#include "t2-histogram.h"

using namespace std;
using namespace cimg_library;

class Point{
public:
    int x, y;
    Point(int x, int y);
};

void applyDilation(CImg<int> &original, CImg<int> &edited, vector<Point> mask);
void applyErosion(CImg<int> &original, CImg<int> &edited, vector<Point> mask);
void applyUnion(CImg<int> &original, CImg<int> &edited);
void applyIntersection(CImg<int> &original, CImg<int> &edited);
void applyDifference(CImg<int> &original, CImg<int> &edited);
void applyOpening(CImg<int> &original, CImg<int> &edited, vector<Point> mask);
void applyClosing(CImg<int> &original, CImg<int> &edited, vector<Point> mask);
void applyHMTTransformation(CImg<int> &original, CImg<int> &edited, vector<Point> mask);

void applyMorphologicalOperationI(CImg<int> &original, CImg<int> &edited);
void applyMorphologicalOperationII(CImg<int> &original, CImg<int> &edited);
void applyMorphologicalOperationIII(CImg<int> &original, CImg<int> &edited);


#endif //MORPHOLOGICAL_OPERATIONS
