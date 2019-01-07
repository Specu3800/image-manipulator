#include <cmath>
#include <vector>
#include <iostream>

#include "lib/CImg.templ"
#include "segmentation.h"

using namespace std;
using namespace cimg_library;


Pixel::Pixel(){};
Pixel::Pixel(int x, int y){
    this -> x = x;
    this -> y = y;
}


CImg<int>& applySegmentationIterative(CImg<int> &original, int x, int y, int threshold){
    CImg<int>* edited = new CImg<int>(original.width(), original.height(), 1, original.spectrum(), 0);

    bool **considered = new bool *[original.width()];
    vector<Pixel> region;
    Pixel seed(x, y);

    for (int i = 0; i < original.width(); i++){
        considered[i] = new bool[original.height()];
        for (int j = 0; j < original.height(); j++){
            considered[i][j] = false;
        }
    }

    region.push_back(Pixel(x, y));

    do {
        int x = region[region.size() - 1].x;
        int y = region[region.size() - 1].y;
        region.pop_back();

        if (x - 1 > 0){
            if (euclideanThreshold(original, threshold, x - 1, y, seed.x, seed.y) && !considered[x - 1][y]){
                (*edited)(x - 1, y, 0, 0) = 255;
                (*edited)(x - 1, y, 0, 1) = 255;
                (*edited)(x - 1, y, 0, 2) = 255;
                region.push_back(Pixel(x - 1, y));
                considered[x - 1][y] = true;
            }
        }

        if (y + 1 < original.height() - 1){
            if (euclideanThreshold(original, threshold, x, y + 1, seed.x, seed.y) && !considered[x][y + 1]){
                (*edited)(x, y + 1, 0, 0) = 255;
                (*edited)(x, y + 1, 0, 1) = 255;
                (*edited)(x, y + 1, 0, 2) = 255;
                region.push_back(Pixel(x, y + 1));
                considered[x][y + 1] = true;
            }
        }

        if (y - 1 > 0){
            if (euclideanThreshold(original, threshold, x, y - 1, seed.x, seed.y) && !considered[x][y - 1]){
                (*edited)(x, y - 1, 0, 0) = 255;
                (*edited)(x, y - 1, 0, 1) = 255;
                (*edited)(x, y - 1, 0, 2) = 255;
                region.push_back(Pixel(x, y - 1));
                considered[x][y - 1] = true;
            }
        }

        if (x + 1 < original.width() - 1){
            if (euclideanThreshold(original, threshold, x + 1, y, seed.x, seed.y) && !considered[x + 1][y]){
                (*edited)(x + 1, y, 0, 0) = 255;
                (*edited)(x + 1, y, 0, 1) = 255;
                (*edited)(x + 1, y, 0, 2) = 255;
                region.push_back(Pixel(x + 1, y));
                considered[x + 1][y] = true;
            }
        }

    } while (region.size() > 0);

    return *edited;
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

    Pixel seed(x, y);

    alreadyInRegion[x][y] = true;
    segmentationRecursive(original, *edited, x + 1, y, threshold, alreadyInRegion, seed);
    segmentationRecursive(original, *edited, x - 1, y, threshold, alreadyInRegion, seed);
    segmentationRecursive(original, *edited, x, y + 1, threshold, alreadyInRegion, seed);
    segmentationRecursive(original, *edited, x, y - 1, threshold, alreadyInRegion, seed);

    return *edited;
}
void segmentationRecursive(CImg<int> &original, CImg<int> &edited, int x, int y, int threshold, bool** alreadyInRegion, Pixel seed){
    if (x < 0 || x > original.width() - 1 || y < 0 || y > original.height() - 1) return;
    if (alreadyInRegion[x][y]) return;

    if (!euclideanThreshold(original, threshold, x, y, seed.x, seed.y)) return;

    edited(x, y, 0, 0) = 255;
    edited(x, y, 0, 1) = 255;
    edited(x, y, 0, 2) = 255;

    alreadyInRegion[x][y] = true;

    segmentationRecursive(original, edited, x + 1, y, threshold, alreadyInRegion, seed);
    segmentationRecursive(original, edited, x - 1, y, threshold, alreadyInRegion, seed);
    segmentationRecursive(original, edited, x, y + 1, threshold, alreadyInRegion, seed);
    segmentationRecursive(original, edited, x, y - 1, threshold, alreadyInRegion, seed);
}

bool linearThreshold(CImg<int> &original, int threshold, int x1, int y1, int x2, int y2){
    int intensity1 = (original(x1, y1, 0, 0) + original(x1, y1, 0, 1) + original(x1, y1, 0, 2) ) / 3;
    int intensity2 = (original(x2, y2, 0, 0) + original(x2, y2, 0, 1) + original(x2, y2, 0, 2) ) / 3;

    return abs(intensity1 - intensity2 < threshold) != 0;
}

bool euclideanThreshold(CImg<int> &original, int threshold, int x1, int y1, int x2, int y2){
    int distance = sqrt(
            (original(x2, y2, 0, 0) - original(x1, y1, 0, 0)) * (original(x2, y2, 0, 0) - original(x1, y1, 0, 0)) +
            (original(x2, y2, 0, 1) - original(x1, y1, 0, 1)) * (original(x2, y2, 0, 1) - original(x1, y1, 0, 1)) +
            (original(x2, y2, 0, 2) - original(x1, y1, 0, 2)) * (original(x2, y2, 0, 2) - original(x1, y1, 0, 2))
            );
    return distance < threshold;
}
