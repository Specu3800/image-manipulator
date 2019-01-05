#include <cmath>
#include <vector>
#include <complex>
#include <cmath>
#include <iostream>

#include "discrete-fourier-transform.h"
#include "lib/CImg.templ"

using namespace std;
using namespace cimg_library;

void getDFT(CImg<int> &original){

    auto* output = new vector<vector<complex<double>>>;
    vector<vector<complex<double>>> temp;

    for (int y = 0; y < original.height(); y++){ //through each row
        vector<complex<double>> row;
        temp.push_back(row); //add empty row
        for (int x = 0; x < original.width(); x++){ //for every value of that row...
            complex<double> sum = (0.0, 0.0); //...get the sum...
            for (int xx = 0; xx < original.width(); xx++){ //...of every other number in that row...
                complex<double> comp(cos(2 * M_PI * xx * x / original.width()), -sin(2 * M_PI * xx * x / original.width())); //...put in this equation
                sum += (double)(original(xx, y)) * comp;
            }
            temp[y].push_back(sum); //and put it in temporary 2d array
        }
    }// so we have 2d array of comp nums and every number is calculated from numbers of its row


    for (int x = 0; x < original.width(); x++){ //now go through each column
        vector<complex<double>> col;
        (*output).push_back(col); //prepare space
        for (int y = 0; y < original.height(); y++){ //for every value of that column...
            complex<double> sum = (0.0, 0.0); //...get the sum...
            for (int yy = 0; yy < original.height(); yy++){
                complex<double> comp(cos(2 * M_PI * yy * y / original.height()), -sin(2 * M_PI * yy * y / original.height()));
                sum += temp[yy][x] * comp; //note we should swap coordinates
            }
            (*output)[x].push_back(sum);
        }
    }


    CImg<double> final = original;

    int a = 0;
    int b = 0;
    for (int i = original.width() / 2; a < original.width(); i++){
        for (int j = original.height() / 2; b < original.height(); j++){
            for (int k = 0; k < original.spectrum(); k++){
                final(i, j, 0, k) = log(abs((*output)[b][a])) * 15.;
            }
            if (i == original.width() - 1) i = 0;
            if (j == original.height() - 1) j = 0;
            b++;
        }
        b = 0;
        a++;
    }
    final.display();

//    return *output;
}

//vector<complex<double>>& getOneDimensionalDFT(CImg<int> &original){
//
//    auto* output = new vector<complex<double>>;
//    //vector<vector<complex<double>>> temp;
//
//    for (int x = 0; x < original.width(); x++){
//        complex<double> comp(cos(2 * M_PI * xx * x / original.width()), -sin(2 * M_PI * xx * x / original.width()));
//    }
//
//    return *output;
//}

//CImg<int>& getInverseFastFourierTransformInSpatialDomain(CImg<int> &original){
//    CImg<int>* edited = new CImg<int>(original.width(), original.height(), 1, original.spectrum(), 0);
//
//    return *edited;
//}