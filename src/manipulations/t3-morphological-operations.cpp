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


MorphMask getNormalMask(int number){

    MorphMask mask;

    switch (number){
        case 1:
            mask.hit.emplace_back(Point(0, 0));
            mask.hit.emplace_back(Point(1, 0)); break;
        case 2:
            mask.hit.emplace_back(Point(0, 0));
            mask.hit.emplace_back(Point(0, -1)); break;
        case 3:
            mask.hit.emplace_back(Point(0, 0));
            mask.hit.emplace_back(Point(-1, 0));
            mask.hit.emplace_back(Point(0, -1));
            mask.hit.emplace_back(Point(1, 0));
            mask.hit.emplace_back(Point(0, 1));
            mask.hit.emplace_back(Point(1, 1));
            mask.hit.emplace_back(Point(-1, -1));
            mask.hit.emplace_back(Point(1, -1));
            mask.hit.emplace_back(Point(-1, 1));
            break;
        case 4:
            mask.hit.emplace_back(Point(0, 0));
            mask.hit.emplace_back(Point(-1, 0));
            mask.hit.emplace_back(Point(0, -1));
            mask.hit.emplace_back(Point(1, 0));
            mask.hit.emplace_back(Point(0, 1));
            break;
        case 5:
            mask.hit.emplace_back(Point(0, 0));
            mask.hit.emplace_back(Point(1, 0));
            mask.hit.emplace_back(Point(0, -1));
            break;
        case 6:
            mask.hit.emplace_back(Point(1, 0));
            mask.hit.emplace_back(Point(0, -1));
            break;
        case 7:
            mask.hit.emplace_back(Point(0, 0));
            mask.hit.emplace_back(Point(-1, 0));
            mask.hit.emplace_back(Point(1, 0));
            break;
        case 8:
            mask.hit.emplace_back(Point(-1, 0));
            mask.hit.emplace_back(Point(1, 0));
            break;
        case 9:
            mask.hit.emplace_back(Point(0, 0));
            mask.hit.emplace_back(Point(-1, 0));
            mask.hit.emplace_back(Point(-1, -1));
            break;
        case 10:
            mask.hit.emplace_back(Point(0, 0));
            mask.hit.emplace_back(Point(0, 1));
            mask.hit.emplace_back(Point(1, 1));
            break;
        default: //mask 4
            mask.hit.emplace_back(Point(0, 0));
            mask.hit.emplace_back(Point(-1, 0));
            mask.hit.emplace_back(Point(0, -1));
            mask.hit.emplace_back(Point(1, 0));
            mask.hit.emplace_back(Point(0, 1));
            break;
    }
    return mask;
}

MorphMask getHMTMask(int number){

    MorphMask mask;

    switch (number){
        case 1:
            mask.hit.emplace_back(Point(-1, 1));
            mask.hit.emplace_back(Point(-1, 0));
            mask.hit.emplace_back(Point(-1, -1));
            mask.miss.emplace_back(Point(0, 0));
            break;
        case 2:
            mask.hit.emplace_back(Point(-1, -1));
            mask.hit.emplace_back(Point(0, -1));
            mask.hit.emplace_back(Point(1, -1));
            mask.miss.emplace_back(Point(0, 0));
            break;
        case 3:
            mask.hit.emplace_back(Point(1, 1));
            mask.hit.emplace_back(Point(1, 0));
            mask.hit.emplace_back(Point(1, -1));
            mask.miss.emplace_back(Point(0, 0));
            break;
        case 4:
            mask.hit.emplace_back(Point(-1, 1));
            mask.hit.emplace_back(Point(0, 1));
            mask.hit.emplace_back(Point(1, 1));
            mask.miss.emplace_back(Point(0, 0));
            break;
        case 5:
            mask.hit.emplace_back(Point(0, 0));
            mask.hit.emplace_back(Point(1, 1));
            mask.hit.emplace_back(Point(0, 1));
            mask.hit.emplace_back(Point(-1, 1));
            mask.miss.emplace_back(Point(-1, -1));
            mask.miss.emplace_back(Point(0, -1));
            mask.miss.emplace_back(Point(1, -1));
            break;
        default: //mask 5
            mask.hit.emplace_back(Point(0, 0));
            mask.hit.emplace_back(Point(1, 1));
            mask.hit.emplace_back(Point(0, 1));
            mask.hit.emplace_back(Point(-1, 1));
            mask.miss.emplace_back(Point(-1, -1));
            mask.miss.emplace_back(Point(0, -1));
            mask.miss.emplace_back(Point(1, -1));
            break;
    }
    return mask;
}

CImg<int>& applyUnion(CImg<int> &image1, CImg<int> &image2){
    if(image1.width() == image2.width() && image1.height() == image2.height()){
        CImg<int>* edited = new CImg<int>(image1.width(), image1.height(), 1, image1.spectrum(), 0);
        for (int x = 0; x < image1.width(); x++) {
            for (int y = 0; y < image1.height(); y++) {
                if (image1(x, y, 0, 0) == 255 || image2(x, y, 0, 0) == 255){
                    (*edited)(x, y, 0, 0) = 255;
                    (*edited)(x, y, 0, 1) = 255;
                    (*edited)(x, y, 0, 2) = 255;
                }
            }
        }
        return *edited;
    } else {
        cout << "Works only for same size images!" << endl;
        exit(0);
    }
}

CImg<int>& applyIntersection(CImg<int> &image1, CImg<int> &image2){
    if(image1.width() == image2.width() && image1.height() == image2.height()){
        CImg<int>* edited = new CImg<int>(image1.width(), image1.height(), 1, image1.spectrum(), 0);
        for (int x = 0; x < image1.width(); x++) {
            for (int y = 0; y < image1.height(); y++) {
                if (image1(x, y, 0, 0) == 255 && image2(x, y, 0, 0) == 255) {
                    (*edited)(x, y, 0, 0) = 255;
                    (*edited)(x, y, 0, 1) = 255;
                    (*edited)(x, y, 0, 2) = 255;
                }
            }
        }
        return *edited;
    } else {
        cout << "Works only for same size images!" << endl;
        exit(0);
    }
}

CImg<int>& applyDifference(CImg<int> &image1, CImg<int> &image2){
    if(image1.width() == image2.width() && image1.height() == image2.height()) {
        CImg<int>* edited = new CImg<int>(image1.width(), image1.height(), 1, image1.spectrum(), 0);
        for (int x = 0; x < image1.width(); x++) {
            for (int y = 0; y < image1.height(); y++) {
                if (image1(x, y, 0, 0) == 255 && image2(x, y, 0, 0) == 0){
                    (*edited)(x, y, 0, 0) = 255;
                    (*edited)(x, y, 0, 1) = 255;
                    (*edited)(x, y, 0, 2) = 255;
                }
            }
        }
        return *edited;
    } else {
        cout << "Works only for same size images!" << endl;
        exit(0);
    }
}

CImg<int>& applyErosion(CImg<int> &original, MorphMask mask){ //0,0 is 1 if whole mask cannot fit
    CImg<int>* edited = new CImg<int>(original.width(), original.height(), 1, original.spectrum(), 0);
    for (int x = 0; x < original.width(); x++) {
        for (int y = 0; y < original.height(); y++) {
            bool fits = true;
            for (int i = 0; i < mask.hit.size(); i++) {
                if (x+mask.hit[i].x >= 0 && x+mask.hit[i].x < original.width() && y+mask.hit[i].y >= 0 && y+mask.hit[i].y < original.height()) {
                    if (original(x + mask.hit[i].x, y + mask.hit[i].y, 0, 0) == 0) {
                        fits = false;
                        break;
                    }
                } else {
                    fits = false;
                    break;
                }
            }
            if(fits) {
                (*edited)(x, y, 0, 0) = 255;
                (*edited)(x, y, 0, 1) = 255;
                (*edited)(x, y, 0, 2) = 255;
            }
        }
    }
    return *edited;
}

CImg<int>& applyDilation(CImg<int> &original, MorphMask mask){ //add 0,0 if it has at least one common point with mask
    CImg<int>* edited = new CImg<int>(original.width(), original.height(), 1, original.spectrum(), 0);
    for (int x = 0; x < original.width(); x++) {
        for (int y = 0; y < original.height(); y++) {
            bool hasCommonPoint = false;
            for (int i = 0; i < mask.hit.size(); i++) {
                if (x+mask.hit[i].x >= 0 && x+mask.hit[i].x < original.width() && y+mask.hit[i].y >= 0 && y+mask.hit[i].y < original.height()){
                    if(original(x+mask.hit[i].x, y+mask.hit[i].y, 0, 0) == 255) {
                        hasCommonPoint = true;
                        break;
                    }
                }
            }
            if(hasCommonPoint) {
                (*edited)(x, y, 0, 0) = 255;
                (*edited)(x, y, 0, 1) = 255;
                (*edited)(x, y, 0, 2) = 255;
            }
        }
    }
    return *edited;
}

CImg<int>& applyOpening(CImg<int> &original, MorphMask mask){ //if whole mask fits, all pixels are rewritten to edited, if not continue // it cuts this alone pixels // in inner border of an image
    CImg<int>* edited = new CImg<int>(original.width(), original.height(), 1, original.spectrum(), 0);
    *edited = applyErosion(original, mask);
    *edited = applyDilation(*edited, mask);
    return *edited;
}

CImg<int>& applyClosing(CImg<int> &original, MorphMask mask){ //roll in outer border of an image // filfill alone pixels //
    CImg<int>* edited = new CImg<int>(original.width(), original.height(), 1, original.spectrum(), 0);
    *edited = applyDilation(original, mask);
    *edited = applyErosion(*edited, mask);
    return *edited;
}

CImg<int>& applyHMT(CImg<int> &original, MorphMask mask){ //hit points must fit, miss point must not fit :)
    CImg<int>* edited = new CImg<int>(original.width(), original.height(), 1, original.spectrum(), 0);
    for (int x = 0; x < original.width(); x++) {
        for (int y = 0; y < original.height(); y++) {
            bool maskFits = true;
            for (int i = 0; i < mask.hit.size(); i++) {
                if (!maskFits) break;
                if (x + mask.hit[i].x >= 0 && x + mask.hit[i].x < original.width() && y + mask.hit[i].y >= 0 &&
                    y + mask.hit[i].y < original.height()) {
                    if (original(x + mask.hit[i].x, y + mask.hit[i].y, 0, 0) == 0) maskFits = false;
                } else maskFits = false;
            }
            for (int i = 0; i < mask.miss.size(); i++) {
                if (!maskFits) break;
                if (x + mask.miss[i].x >= 0 && x + mask.miss[i].x < original.width() && y + mask.miss[i].y >= 0 &&
                    y + mask.miss[i].y < original.height()) {
                    if (original(x + mask.miss[i].x, y + mask.miss[i].y, 0, 0) == 255) maskFits = false;
                } else maskFits = false;
            }
            if(maskFits) {
                (*edited)(x, y, 0, 0) = 255;
                (*edited)(x, y, 0, 1) = 255;
                (*edited)(x, y, 0, 2) = 255;
            }
        }
    }
    return *edited;
}


CImg<int>& applyOuterBorder(CImg<int> &original, int maskNumber){

    CImg<int>* edited = new CImg<int>(original.width(), original.height(), 1, original.spectrum(), 0);

    MorphMask mask = getNormalMask(maskNumber);

    *edited = applyDilation(original, mask);
    *edited = applyDifference(*edited, original);

    return *edited;
}

CImg<int>& applyInnerBorder(CImg<int> &original, int maskNumber){
    CImg<int>* edited = new CImg<int>(original.width(), original.height(), 1, original.spectrum(), 0);

    MorphMask mask = getNormalMask(maskNumber);

    *edited = applyErosion(original, mask);
    *edited = applyDifference(original, *edited);

    return *edited;
}

CImg<int>& applyInnerOuterBorder(CImg<int> &original, int maskNumber){

    CImg<int>* edited = new CImg<int>(original.width(), original.height(), 1, original.spectrum(), 0);

    MorphMask mask = getNormalMask(maskNumber);

    *edited = applyDifference(applyDilation(original, mask), applyErosion(original, mask));

    return *edited;
}
