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

CImg<int>& applyUnion(CImg<int> &image1, CImg<int> &image2){
    if(image1.width() == image2.width() && image1.height() == image2.height()){
        CImg<int>* edited = new CImg<int>(image1.width(), image1.height(), 1, image1.spectrum(), 0);
        for (int x = 0; x < image1.width(); x++) {
            for (int y = 0; y < image1.height(); y++) {
                for (int c = 0; c < image1.spectrum(); c++) {
                    if (image1(x, y, 0, c) == 255 || image2(x, y, 0, c) == 255)
                        (*edited)(x, y, 0, c) = 255;
                }
            }
        }
        return *edited;
    } else {
        cout << "Works only for same size images!" << endl;
        return image1;
    }
}

CImg<int>& applyIntersection(CImg<int> &image1, CImg<int> &image2){
    if(image1.width() == image2.width() && image1.height() == image2.height()){
        CImg<int>* edited = new CImg<int>(image1.width(), image1.height(), 1, image1.spectrum(), 0);
        for (int x = 0; x < image1.width(); x++) {
            for (int y = 0; y < image1.height(); y++) {
                for (int c = 0; c < image1.spectrum(); c++) {
                    if (image1(x, y, 0, c) == 255 && image2(x, y, 0, c) == 255)
                        (*edited)(x, y, 0, c) = 255;
                }
            }
        }
        return *edited;
    } else {
        cout << "Works only for same size images!" << endl;
        return image1;
    }
}

CImg<int>& applyDifference(CImg<int> &image1, CImg<int> &image2){
    if(image1.width() == image2.width() && image1.height() == image2.height()) {
        CImg<int>* edited = new CImg<int>(image1.width(), image1.height(), 1, image1.spectrum(), 0);
        for (int x = 0; x < image1.width(); x++) {
            for (int y = 0; y < image1.height(); y++) {
                for (int c = 0; c < image1.spectrum(); c++) {
                    if (image1(x, y, 0, c) == 255 && image2(x, y, 0, c) == 0)
                        (*edited)(x, y, 0, c) = 255;
                }
            }
        }
        return *edited;
    } else {
        cout << "Works only for same size images!" << endl;
        return image1;
    }
}

CImg<int>& applyErosion(CImg<int> &original, vector<Point> mask){ //delete 0,0 if whole mask cannot fit
    CImg<int>* edited = new CImg<int>(original.width(), original.height(), 1, original.spectrum(), 0);
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
                if(fits) (*edited)(x, y, 0, c) = 255;
                else (*edited)(x, y, 0, c) = 0;
            }
        }
    }
    return *edited;
}

CImg<int>& applyDilation(CImg<int> &original, vector<Point> mask){ //add 0,0 if it has at least one common point with mask
    CImg<int>* edited = new CImg<int>(original.width(), original.height(), 1, original.spectrum(), 0);
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
                if(hasCommonPoint) (*edited)(x, y, 0, c) = 255;
                else (*edited)(x, y, 0, c) = 0;
            }
        }
    }
    return *edited;
}

CImg<int>& applyOpening(CImg<int> &original, vector<Point> mask){ //if whole mask fits, all pixels are rewritten to edited, if not continue // it cuts this alone pixels // in inner border of an image
    CImg<int>* edited = new CImg<int>(original.width(), original.height(), 1, original.spectrum(), 0);
    *edited = applyErosion(original, mask);
    *edited = applyDilation(*edited, mask);
    return *edited;
}

CImg<int>& applyClosing(CImg<int> &original, vector<Point> mask){ //roll in outer border of an image // filfill alone pixels //
    CImg<int>* edited = new CImg<int>(original.width(), original.height(), 1, original.spectrum(), 0);
    *edited = applyDilation(original, mask);
    *edited = applyErosion(*edited, mask);
    return *edited;
}

CImg<int>& applyHMTTransformation(CImg<int> &original, vector<Point> mask){
    return original;
}


CImg<int>& applyMorphologicalOperationI(CImg<int> &original){
    vector<Point> mask;
    mask.emplace_back(Point(0, 0));
    mask.emplace_back(Point(-1, 0));
    mask.emplace_back(Point(1, 0));
    mask.emplace_back(Point(0, -1));
    mask.emplace_back(Point(0, 1));
    //later we should make a feature to chose any mask from templates in task description
    //and consider implementing morphologycal operations not on masks, but on CImg objects,
    //so we can apply it to any two images (but i dont know if it really is necessary)

    CImg<int>* edited = new CImg<int>(original.width(), original.height(), 1, original.spectrum(), 0);

    *edited = applyDilation(original, mask);
    *edited = applyDifference(*edited, original);

    return *edited;
}

CImg<int>& applyMorphologicalOperationII(CImg<int> &original){
    vector<Point> mask;
    mask.emplace_back(Point(0, 0));
    mask.emplace_back(Point(-1, 0));
    mask.emplace_back(Point(1, 0));
    mask.emplace_back(Point(0, -1));
    mask.emplace_back(Point(0, 1));
    //later we should make a feature to chose any mask from templates in task description
    //and consider implementing morphologycal operations not on masks, but on CImg objects,
    //so we can apply it to any two images (but i dont know if it really is necessary)

    CImg<int>* edited = new CImg<int>(original.width(), original.height(), 1, original.spectrum(), 0);

    *edited = applyErosion(original, mask);
    *edited = applyDifference(original, *edited);

    return *edited;
}

CImg<int>& applyMorphologicalOperationIII(CImg<int> &original){
    vector<Point> mask;
    mask.emplace_back(Point(0, 0));
    mask.emplace_back(Point(-1, 0));
    mask.emplace_back(Point(1, 0));
    mask.emplace_back(Point(0, -1));
    mask.emplace_back(Point(0, 1));
    //later we should make a feature to chose any mask from templates in task description
    //and consider implementing morphologycal operations not on masks, but on CImg objects,
    //so we can apply it to any two images (but i dont know if it really is necessary)

    CImg<int>* edited = new CImg<int>(original.width(), original.height(), 1, original.spectrum(), 0);

    *edited = applyDifference(applyDilation(original, mask), applyErosion(original, mask));

    return *edited;
}