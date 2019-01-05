#include <cmath>
#include <vector>
#include <complex>
#include <iostream>

#include "discrete-fourier-transform.h"

using namespace std;
using namespace cimg_library;


CImg<int>& getDiscreteFourierTransformInSpatialDomain(CImg<int> &original){
    CImg<int>* edited = new CImg<int>(original.width(), original.height(), 1, original.spectrum(), 0);

    vector<vector<complex<double>>> N;

    complex<double> a;
    complex<double> sum;

    for (int r = 0; r < original.height(); r++){
        vector<complex<double>> row;
        for (int x = 0; x < original.width(); x++){
            for (int y = 0; y < original.height(); y++){
                complex<double> temp(cos(2 * M_PI * x * y / original.width()), -sin(2 * M_PI * x * y / original.width()));
                //sum += image(x, y) * temp;
            }
        }
    }

    return *edited;
}

//CImg<int>& getInverseFastFourierTransformInSpatialDomain(CImg<int> &original){
//    CImg<int>* edited = new CImg<int>(original.width(), original.height(), 1, original.spectrum(), 0);
//
//    return *edited;
//}
