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
                currDepth = 1;
                while(true) {
                    if(currDepth > maxDepth) break;
                    for (int xx = 0; xx < currDepth*2 + 1; xx++) {
                        for (int yy = 0; yy < currDepth*2 + 1; yy++) {
                            if (x - currDepth + xx >= 0 && x - currDepth + xx < img.width() && y - currDepth + yy >= 0 && y - currDepth + yy < img.height()) {
                                pixels.push_back(img(x - currDepth + xx, y - currDepth + yy, 0, j));
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

CImg<int> applyMinimumFilter(CImg<int> img, char* maxD){
    CImg<int> newImg(img.width(), img.height(), 1, 3, 0);
    int maxDepth = atoi(maxD);
    vector<int> pixels;
    for (int x = 0; x < img.width(); x++) {
        for (int y = 0; y < img.height(); y++) {
            for (int j = 0; j < 3; j++) {

                for (int xx = 0; xx < maxDepth*2 + 1; xx++) {
                    for (int yy = 0; yy < maxDepth*2 + 1; yy++) {
                        if (x - maxDepth + xx >= 0 && x - maxDepth + xx < img.width() && y - maxDepth + yy >= 0 && y - maxDepth + yy < img.height()) {
                            pixels.push_back(img(x - maxDepth + xx, y - maxDepth + yy, 0, j));
                        }
                    }
                }
                newImg(x, y, 0, j) = distance(begin(pixels), min_element(begin(pixels), end(pixels)));
                sort(pixels.begin(), pixels.end());
                newImg(x, y, 0, j) = pixels[0];
                pixels.clear();
            }
        }
    }
    return newImg;
}

CImg<int> applyMaximumFilter(CImg<int> img, char* maxD){
    CImg<int> newImg(img.width(), img.height(), 1, 3, 0);
    int maxDepth = atoi(maxD);
    vector<int> pixels;
    for (int x = 0; x < img.width(); x++) {
        for (int y = 0; y < img.height(); y++) {
            for (int j = 0; j < 3; j++) {

                for (int xx = 0; xx < maxDepth*2 + 1; xx++) {
                    for (int yy = 0; yy < maxDepth*2 + 1; yy++) {
                        if (x - maxDepth + xx >= 0 && x - maxDepth + xx < img.width() && y - maxDepth + yy >= 0 && y - maxDepth + yy < img.height()) {
                            pixels.push_back(img(x - maxDepth + xx, y - maxDepth + yy, 0, j));
                        }
                    }
                }
                newImg(x, y, 0, j) = distance(begin(pixels), max_element(begin(pixels), end(pixels)));
                sort(pixels.begin(), pixels.end());
                newImg(x, y, 0, j) = pixels[0];
                pixels.clear();
            }
        }
    }
    return newImg;
}
