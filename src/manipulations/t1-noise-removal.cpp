#include <iostream>
#include <vector>
#include <algorithm>
#include "../../lib/CImg.templ"
#include "t1-noise-removal.h"

using namespace std;
using namespace cimg_library;


CImg<int> applyAdaptiveMedianFilter(CImg<int> img, char* maxD){
    int maxDepth = atoi(maxD);
    vector<int> pixels;
    int currDepth;
    for (int x = 0; x < img.width(); x++) {
        for (int y = 0; y < img.height(); y++) {
            for (int j = 0; j < 3; j++) {

                currDepth = 3;
                while(true) {

                    if(currDepth > maxDepth) break;

                    int shift = (currDepth-1)/2;
                    for (int x2 = 0; x2 < currDepth; x2++) {
                        for (int y2 = 0; y2 < currDepth; y2++) {
                            if (x - shift + x2 >= 0 && x - shift + x2 < img.width() && y - shift + y2 >= 0 && y - shift + y2 < img.height()) {
                                pixels.push_back(img(x - shift + x2, y - shift + y2, 0, j));
                            }
                        }
                    }
                    sort(pixels.begin(), pixels.end());
                    if (img(x, y, 0, j) == pixels[(pixels.size()-1) / 2]){
                        pixels.clear();
                        currDepth += 2;
                        continue;
                    } else {
                        img(x, y, 0, j) = pixels[(pixels.size()-1) / 2];
                        pixels.clear();
                        break;}
                }
            }
        }
    }
    return img;
}

CImg<int> applyMinimumFilter(CImg<int> img, char* d){
    CImg<int> copyImg = img;
    int depth = atoi(d);
    depth = 1;
    vector<int> pixelTable;
    for (int x = 0; x < img.width(); x++)
        for (int y = 0 ; y < img.height(); y++) {
            cout << "x: " << x << " y: " << y << endl;
            for (int j = 0; j < 3; j++) {
                for (int xx = 0; xx < depth * 2 + 1; xx++)
                    for (int yy = 0; yy < depth * 2 + 1; yy++) {
                        if (x - depth + xx > 0 && y - depth + yy > 0 & x - depth + xx < img.width() &&
                            y - depth + yy < img.height()) {
                            pixelTable.push_back(img(x - depth + xx, y - depth + yy, 0, j));
                        }
                    }
                copyImg(x, y, 0, j) = distance(begin(pixelTable), min_element(begin(pixelTable), end(pixelTable)));
                    pixelTable.clear();
            }
        }

    return copyImg;
}

CImg<int> applyMaximumFilter(CImg<int> img){
    return img;
}
