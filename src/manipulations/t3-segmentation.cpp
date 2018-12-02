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

CImg<int>& applySegmentation(CImg<int> &original, int intensity, int threshold){
    CImg<int>* edited = new CImg<int>(original.width(), original.height(), 1, original.spectrum(), 0);
    bool alreadyInRegion[512][512];
    for (int x = 1; x < original.width(); x++)
        for (int y = 1; y < original.height(); y++)
            alreadyInRegion[x][y] = false;

    vector<SegmentRegion> regions;
    for(int x = 1; x < original.width() - 1; x++)
        for(int y = 1; y < original.height() - 1; y++)
        {
            int meanIntensity = (original(x, y, 0, 0) + original(x, y, 0, 1) + original(x, y, 0, 2))/3;
            if ( abs(intensity - meanIntensity) < threshold && !alreadyInRegion[x][y] )
            {
                SegmentRegion* newRegion = new SegmentRegion();
                newRegion -> seed = Pixel(x, y);
                newRegion -> pixels.push_back(newRegion -> seed);
                cout <<"Znalazlo seed: " << newRegion -> seed.x << " " << newRegion -> seed.y << endl;
                alreadyInRegion[x][y] = true;
                segmentationRecursive(original, *edited, x + 1, y, threshold, original.width(), original.height(), alreadyInRegion, newRegion -> seed, newRegion);
                segmentationRecursive(original, *edited, x - 1, y, threshold, original.width(), original.height(), alreadyInRegion, newRegion -> seed, newRegion);
                segmentationRecursive(original, *edited, x, y + 1, threshold, original.width(), original.height(), alreadyInRegion, newRegion -> seed, newRegion);
                segmentationRecursive(original, *edited, x, y - 1, threshold, original.width(), original.height(), alreadyInRegion, newRegion -> seed, newRegion);
                regions.push_back(*newRegion);
            }
        }

    return *edited;
}
void segmentationRecursive(CImg<int> &original, CImg<int> &edited, int x, int y, int threshold, int N, int M, bool alreadyInRegion[][512], Pixel seed, SegmentRegion* region){

    if (x < 1 || x > original.width() || y < 1 || y > original.height()) return;
    if (alreadyInRegion[x][y]) return;

    if (!euclideanThreshold(original, threshold, x, y, seed.x, seed.y)) return;

    edited(x, y, 0, 0) = 255;
    edited(x, y, 0, 1) = 255;
    edited(x, y, 0, 2) = 255;
    region->pixels.push_back(Pixel(x, y));
    alreadyInRegion[x][y] = true;

    segmentationRecursive(original, edited, x + 1, y, threshold, original.width(), original.height(), alreadyInRegion, region -> seed, region);
    segmentationRecursive(original, edited, x - 1, y, threshold, original.width(), original.height(), alreadyInRegion, region -> seed, region);
    segmentationRecursive(original, edited, x, y + 1, threshold, original.width(), original.height(), alreadyInRegion, region -> seed, region);
    segmentationRecursive(original, edited, x, y - 1, threshold, original.width(), original.height(), alreadyInRegion, region -> seed, region);


    return;
}

bool linearThreshold(CImg<int> &original, int threshold, int x1, int y1, int x2, int y2)
{
    int intensity1 = (original(x1, y1, 0, 0) + original(x1, y1, 0, 1) + original(x1, y1, 0, 2) ) / 3;
    int intensity2 = (original(x2, y2, 0, 0) + original(x2, y2, 0, 1) + original(x2, y2, 0, 2) ) / 3;

    if (abs(intensity1 - intensity2 < threshold)) return true;
    return false;
}
bool euclideanThreshold(CImg<int> &original, int threshold, int x1, int y1, int x2, int y2)
{
    int distance = sqrt(  (original(x2, y2, 0, 0) - original(x1, y1, 0, 0)) * (original(x2, y2, 0, 0) - original(x1, y1, 0, 0)) + (original(x2, y2, 0, 1) - original(x1, y1, 0, 1)) * (original(x2, y2, 0, 1) - original(x1, y1, 0, 1)) + (original(x2, y2, 0, 2) - original(x1, y1, 0, 2)) * (original(x2, y2, 0, 2) - original(x1, y1, 0, 2)) );
    if (distance < threshold) return true;
    return false;
}
