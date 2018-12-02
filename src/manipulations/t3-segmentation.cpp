#include "../../lib/CImg.templ"
#include "t3-segmentation.h"
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;
using namespace cimg_library;


Pixel::Pixel(){};
Pixel::Pixel(int x, int y)
{
    this -> x = x;
    this -> y = y;
}

CImg<int>& applySegmentation(CImg<int> &original, int x, int y, int threshold){
    CImg<int>* edited = new CImg<int>(original.width(), original.height(), 1, original.spectrum(), 0);

    bool** alreadyInRegion;
    alreadyInRegion = new bool*[original.width()];
    for (int i = 0; i < original.width(); i++)
        alreadyInRegion[i] = new bool[original.height()];


    for (int x = 0; x < original.width(); x++)
        for (int y = 0; y < original.height(); y++)
            alreadyInRegion[x][y] = false;

        //vector<SegmentRegion> regions;

//    SegmentRegion* newRegion = new SegmentRegion();
//    newRegion -> seed = Pixel(x, y);
    Pixel seed(x, y);
//    newRegion -> pixels.push_back(newRegion -> seed);

    alreadyInRegion[x][y] = true;
    segmentationRecursive(original, *edited, x + 1, y, threshold, alreadyInRegion, seed);
    segmentationRecursive(original, *edited, x - 1, y, threshold, alreadyInRegion, seed);
    segmentationRecursive(original, *edited, x, y + 1, threshold, alreadyInRegion, seed);
    segmentationRecursive(original, *edited, x, y - 1, threshold, alreadyInRegion, seed);
    //regions.push_back(*newRegion);


    return *edited;
}
void segmentationRecursive(CImg<int> &original, CImg<int> &edited, int x, int y, int threshold, bool** alreadyInRegion, Pixel seed){
    if (x < 0 || x > original.width() - 1 || y < 0 || y > original.height() - 1) return;
    if (alreadyInRegion[x][y]) return;

    if (!euclideanThreshold(original, threshold, x, y, seed.x, seed.y)) return;

    edited(x, y, 0, 0) = 255;
    edited(x, y, 0, 1) = 255;
    edited(x, y, 0, 2) = 255;
    //region->pixels.push_back(Pixel(x, y));
    alreadyInRegion[x][y] = true;

    segmentationRecursive(original, edited, x + 1, y, threshold, alreadyInRegion, seed);
    segmentationRecursive(original, edited, x - 1, y, threshold, alreadyInRegion, seed);
    segmentationRecursive(original, edited, x, y + 1, threshold, alreadyInRegion, seed);
    segmentationRecursive(original, edited, x, y - 1, threshold, alreadyInRegion, seed);
}

bool linearThreshold(CImg<int> &original, int threshold, int x1, int y1, int x2, int y2)
{
    int intensity1 = (original(x1, y1, 0, 0) + original(x1, y1, 0, 1) + original(x1, y1, 0, 2) ) / 3;
    int intensity2 = (original(x2, y2, 0, 0) + original(x2, y2, 0, 1) + original(x2, y2, 0, 2) ) / 3;

    return abs(intensity1 - intensity2 < threshold) != 0;
}
bool euclideanThreshold(CImg<int> &original, int threshold, int x1, int y1, int x2, int y2)
{
    int distance = sqrt(
            (original(x2, y2, 0, 0) - original(x1, y1, 0, 0)) * (original(x2, y2, 0, 0) - original(x1, y1, 0, 0)) +
            (original(x2, y2, 0, 1) - original(x1, y1, 0, 1)) * (original(x2, y2, 0, 1) - original(x1, y1, 0, 1)) +
            (original(x2, y2, 0, 2) - original(x1, y1, 0, 2)) * (original(x2, y2, 0, 2) - original(x1, y1, 0, 2))
            );
    return distance < threshold;
}
