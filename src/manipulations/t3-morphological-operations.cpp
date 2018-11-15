#include <iostream>
#include <vector>
#include <algorithm>
#include "../../lib/CImg.templ"
#include "t0-other.h"
#include "t3-morphological-operations.h"

using namespace std;
using namespace cimg_library;

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

void applyErosion(CImg<int> &original, CImg<int> &edited, vector<Point> mask){ //delete 0,0 if whole mask cannot fit
    for (int x = 0; x < original.width(); x++) {
        for (int y = 0; y < original.height(); y++) {
            for (int c = 0; c < original.spectrum(); c++) {
                bool fits = true;
                for (int i = 0; i < mask.size(); i++) {
                    if (x+mask[i].x >= 0 && x+mask[i].x < original.width() && y+mask[i].y >= 0 && y+mask[i].y < original.height()) {
                        if (original(x + mask[i].x, y + mask[i].y, 0, c) == 0) {
                            fits = false;
                            break;
                        }
                    }
                }
                if(fits) edited(x, y, 0, c) = 255;
                else edited(x, y, 0, c) = 0;
            }
        }
    }
}

void applyDilation(CImg<int> &original, CImg<int> &edited, vector<Point> mask){ //add 0,0 if it has at least one common point with mask
    for (int x = 0; x < original.width(); x++) {
        for (int y = 0; y < original.height(); y++) {
            for (int c = 0; c < original.spectrum(); c++) {
                bool hasCommonPoint = false;
                for (int i = 0; i < mask.size(); i++) {
                    if (x+mask[i].x >= 0 && x+mask[i].x < original.width() && y+mask[i].y >= 0 && y+mask[i].y < original.height()){
                        if(original(x+mask[i].x, y+mask[i].y, 0, c) == 255) {
                            hasCommonPoint = true;
                            break;
                        }
                    }
                }
                if(hasCommonPoint) edited(x, y, 0, c) = 255;
                else edited(x, y, 0, c) = 0;
            }
        }
    }
}

void applyUnion(CImg<int> &original, CImg<int> &edited){
    if(original.width() == edited.width() && original.height() == edited.height()){
        for (int x = 0; x < original.width(); x++) {
            for (int y = 0; y < original.height(); y++) {
                for (int c = 0; c < original.spectrum(); c++) {
                    if (original(x, y, 0, c) == 255 && edited(x, y, 0, c) == 0)
                        edited(x, y, 0, c) = 255;
                }
            }
        }
    }
    else
        cout << "Works only for same size images!" <<endl;
}

void applyIntersection(CImg<int> &original, CImg<int> &edited){
    if(original.width() == edited.width() && original.height() == edited.height()){
        for (int x = 0; x < original.width(); x++) {
            for (int y = 0; y < original.height(); y++) {
                for (int c = 0; c < original.spectrum(); c++) {
                    if (original(x, y, 0, c) == 0 && edited(x, y, 0, c) == 255)
                        edited(x, y, 0, c) = 0;
                }
            }
        }
    }
    else
        cout << "Works only for same size images!" <<endl;
}

void applyDifference(CImg<int> &original, CImg<int> &edited){
    CImg<int> diff(original);
    for (int x = 0; x < edited.width(); x++) {
        for (int y = 0; y < edited.height(); y++) {
            for (int c = 0; c < edited.spectrum(); c++) {
                if (x >= 0 && x < original.width() && y >= 0 && y < original.height()){
                if (edited(x, y, 0, c) == 255 && diff(x, y, 0, c) == 255)
                    diff(x, y, 0, c) = 0;
                }
            }
        }
    }
    edited = diff;
}

void applyOpening(CImg<int> &original, CImg<int> &edited, vector<Point> mask){ //if whole mask fits, all pixels are rewritten to edited, if not continue // it cuts this alone pixels // in inner border of an image
    applyErosion(original, edited, mask);
    CImg<int> backup(original);
    original = edited;
    applyDilation(original, edited, mask);
    original = backup;
}

void applyClosing(CImg<int> &original, CImg<int> &edited, vector<Point> mask){ //roll in outer border of an image // filfill alone pixels //
    applyDilation(original, edited, mask);
    CImg<int> backup(original);
    original = edited;
    applyErosion(original, edited, mask);
    original = backup;
}

void applyHMTTransformation(CImg<int> &original, CImg<int> &edited, vector<Point> mask){
;
}


void applyMorphologicalOperationI(CImg<int> &original, CImg<int> &edited){
    vector<Point> mask;
    mask.emplace_back(Point(0, 0));
    mask.emplace_back(Point(-1, 0));
    mask.emplace_back(Point(1, 0));
    mask.emplace_back(Point(0, -1));
    mask.emplace_back(Point(0, 1));

    applyDilation(original, edited, mask);
    applyDifference(original, edited);
}

void applyMorphologicalOperationII(CImg<int> &original, CImg<int> &edited){
;
}

void applyMorphologicalOperationIII(CImg<int> &original, CImg<int> &edited){
;
}