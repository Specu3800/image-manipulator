#include <cmath>
#include <vector>
#include <complex>
#include <cmath>
#include <iostream>

#include "fourier-transform.h"
#include "helpers.h"
#include "lib/CImg.templ"

using namespace std;
using namespace cimg_library;

vector<vector<complex<double>>>& applyDFT(CImg<int> &original){

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

    //getFourierImage(*output).display();

    vector<vector<complex<double>>> swaped = swapQuarters(*output);
    //getFourierImage(swaped).display();
    //final.display();

    return *output;
}


vector<vector<complex<double>>>& applyFFT(CImg<int> &original){
    auto* output = new vector<vector<complex<double>>>;

    return *output;
}

CImg<int>& applyIDFT(vector<vector<complex<double>>> &original){
    CImg<int>* output = new CImg<int>(original[0].size(), original.size(), 1, 1, 0);

    return *output;
}

CImg<int>& applyIFFT(vector<vector<complex<double>>> &original){
    CImg<int>* output = new CImg<int>(original[0].size(), original.size(), 1, 1, 0);

    return *output;
}


vector<vector<complex<double>>>& swapQuarters(vector<vector<complex<double>>> &original){
    auto* output = new vector<vector<complex<double>>>;

    cout << "duap0" << endl; cout.flush();

    for (int x = 0; x < original.size(); x++){
        for (int y = 0; y < original[0].size(); y++) {
            (*output)[x][y] = original[x][y];
        }
    }
    cout << "duap1" << endl; cout.flush();

    for (int x = 0; x < original.size()/2; x++){
        for (int y = 0; y < original[0].size()/2; y++) {
            swap((*output)[x][y], (*output)[original.size()/2 + x][original[0].size()/2 + y]);
            swap((*output)[original.size()/2 + x][y], (*output)[x][original[0].size()/2 + y]);
        }
    }

    cout << "duap2" << endl; cout.flush();
    return *output;
}

CImg<int>& getFourierImage(vector<vector<complex<double>>> &original){

    CImg<int>* output = new CImg<int>(original[0].size(), original.size(), 1, 3, 0);
    for (int x = 1; x < original[0].size() - 1; x++) {
        for (int y = 1; y < original.size() - 1; y++) {
            for (int c = 0; c < 3; c++) {
                (*output)(x, y, c) = normalize(log(abs((original)[y][x])) * 15.);
            }
        }
    }
//    int a = 0;
//    int b = 0;
//    for (int i = original[0].size() / 2; a < original[0].size(); i++){
//        for (int j = original.size() / 2; b < original.size(); j++){
//            for (int k = 0; k < 3; k++){
//                (*output)(i, j, 0, k) = log(abs((original)[b][a])) * 15.;
//                // auto max = max_element(std::begin(*output), std::end(*output));
//                //                auto min = min_element(std::begin(*output), std::end(*output));
//                //                cout << max))
//                //                final(i, j, 0, k) = (255)*(abs((*output)[b][a]) - min) / (max - min)
//            }
//            if (i == original[0].size() - 1) i = 0;
//            if (j == original.size() - 1) j = 0;
//            b++;
//        }
//        b = 0;
//        a++;
//    }
    return *output;
}