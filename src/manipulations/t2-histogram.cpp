//
// Created by mike on 28.10.18.
//

#include <iostream>
#include "t2-histogram.h"

using namespace std;
using namespace cimg_library;

void getHistogram(CImg<int> &image, int RGB){
    int hist[256];
    for (int i = 0; i < 256; i++)
        hist[i] = 0;

}
