//
// Created by mike on 11/10/18.
//


#ifndef IMAGE_MANIPULATOR_MANIPULATIONS_H
#define IMAGE_MANIPULATOR_MANIPULATIONS_H

#include "manipulations.h"
#include "CImg.templ"

using namespace std;
using namespace cimg_library;

CImg<int> changeBrightness(CImg<int>, char*, char*);
CImg<int> changeContrast(CImg<int>, char*, char*);
CImg<int> changeToNegative(CImg<int>, char*);

#endif //IMAGE_MANIPULATOR_MANIPULATIONS_H


