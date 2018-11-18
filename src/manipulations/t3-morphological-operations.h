#ifndef MORPHOLOGICAL_OPERATIONS
#define MORPHOLOGICAL_OPERATIONS

#include "../../lib/CImg.templ"

using namespace std;
using namespace cimg_library;

class Point{
public:
    int x, y;
    Point(int x, int y);
};

CImg<int>& applyUnion(CImg<int> &image1, CImg<int> &image2);
CImg<int>& applyIntersection(CImg<int> &image1, CImg<int> &image2);
CImg<int>& applyDifference(CImg<int> &image1, CImg<int> &image2);

CImg<int>& applyErosion(CImg<int> &original, vector<Point> mask);
CImg<int>& applyDilation(CImg<int> &original, vector<Point> mask);
CImg<int>& applyOpening(CImg<int> &original, vector<Point> mask);
CImg<int>& applyClosing(CImg<int> &original, vector<Point> mask);
CImg<int>& applyHMTTransformation(CImg<int> &original, vector<Point> mask);

CImg<int>& applyMorphologicalOperationI(CImg<int> &original);
CImg<int>& applyMorphologicalOperationII(CImg<int> &original);
CImg<int>& applyMorphologicalOperationIII(CImg<int> &original);


#endif //MORPHOLOGICAL_OPERATIONS
