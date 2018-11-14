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
    edited = original;
    for (int x = 1; x < original.width()-1; x++) {
        for (int y = 1; y < original.height()-1; y++) {
            for (int c = 0; c < original.spectrum(); c++) {

                bool fits = true;
                for (int i = 0; i < mask.size(); i++) {
                    //check if were not out of photo and chg x = 0 y = 0 width +1
                    //if all point fit color pixel
                    //if not break;
                    if(original(x+mask[i].x, y+mask[i].y, 0, c) == 0) {
                        fits = false;
                        break;
                    }
                }
                if(fits) edited(x, y, 0, c) = 255;
                else edited(x, y, 0, c) = 0;
//@@@@@@@@@@@@@@@22 chaeck it it is correct
            }
        }
    }
}

void applyDilation(CImg<int> &original, CImg<int> &edited, vector<Point> mask){ //add 0,0 if it has at least one commont point with mask
;
}


void applyDifference(CImg<int> &original, CImg<int> &edited, CImg<int> &mask){
;
}

void applyOpening(CImg<int> &original, CImg<int> &edited, CImg<int> &mask){ //if whole mask fits, all pixels are rewritten to edited, if not continue // it cuts this alone pixels // in inner border of an image
;
}

void applyClosing(CImg<int> &original, CImg<int> &edited, CImg<int> &mask){ //roll in outer border of an image // filfill alone pixels //
;
}

void applyHMTTransformation(CImg<int> &original, CImg<int> &edited, CImg<int> &mask){
;
}


void applyMorphologicalOperationI(CImg<int> &original, CImg<int> &edited){
    vector<Point> mask;
    mask.emplace_back(Point(0, 0));
    mask.emplace_back(Point(-1, 0));
    mask.emplace_back(Point(1, 0));
    mask.emplace_back(Point(0, -1));
    mask.emplace_back(Point(0, 1));
    applyErosion(original, edited, mask);
}

void applyMorphologicalOperationII(CImg<int> &original, CImg<int> &edited){
;
}

void applyMorphologicalOperationIII(CImg<int> &original, CImg<int> &edited){
;
}