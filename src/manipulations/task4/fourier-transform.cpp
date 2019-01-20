#include <cmath>
#include <vector>
#include <complex>
#include <cmath>
#include <iostream>
#include <algorithm>

#include "fourier-transform.h"
#include "helpers.h"
#include "lib/CImg.templ"

using namespace std;
using namespace cimg_library;

vector<vector<complex<double>>>& applyDFT(CImg<int> &original){
    auto* output = new vector<vector<complex<double>>>;
    vector<vector<complex<double>>> temp;

    for (int y = 0; y < original.height(); y++){
        vector<complex<double>> row;
        temp.push_back(row);
        for (int x = 0; x < original.width(); x++){
            complex<double> sum = (0.0, 0.0);
            for (int xx = 0; xx < original.width(); xx++){
                complex<double> comp(cos(2 * M_PI * xx * x / original.width()), -sin(2 * M_PI * xx * x / original.width()));
                sum += (double)(original(xx, y)) * comp;
            }
            temp[y].push_back(sum);
        }
    }

    for (int x = 0; x < original.width(); x++){
        vector<complex<double>> col;
        (*output).push_back(col);
        for (int y = 0; y < original.height(); y++){
            complex<double> sum = (0.0, 0.0);
            for (int yy = 0; yy < original.height(); yy++){
                complex<double> comp(cos(2 * M_PI * yy * y / original.height()), -sin(2 * M_PI * yy * y / original.height()));
                sum += temp[yy][x] * comp;
            }
            (*output)[x].push_back(sum);
        }
    }

    return *output;
}

CImg<int>& applyIDFT(vector<vector<complex<double>>> &original){
    auto* output = new CImg<int>(original[0].size(), original.size(), 1, 3, 0);
    vector<vector<complex<double>>> temp;

    for (int x = 0; x < (*output).width(); x++){
        vector<complex<double>> col;
        temp.push_back(col);
        for (int y = 0; y < (*output).height(); y++){
            complex<double> sum = (0.0, 0.0);
            for (int yy = 0; yy < (*output).height(); yy++){
                complex<double> comp(cos(2 * M_PI * yy * y / (*output).height()), sin(2 * M_PI * yy * y / (*output).height()));
                sum += original[yy][x] * comp;
            }
            temp[x].push_back(sum / (double)(*output).height());
        }
    }

    for (int y = 0; y < (*output).height(); y++){
        vector<complex<double>> row;
        temp.push_back(row);
        for (int x = 0; x < (*output).width(); x++){
            complex<double> sum = (0.0, 0.0);
            for (int xx = 0; xx < (*output).width(); xx++){
                complex<double> comp(cos(2 * M_PI * xx * x / (*output).width()), sin(2 * M_PI * xx * x / (*output).height()));
                sum += temp[xx][y] * comp;
            }
            for(int c = 0; c < 3; c++){
                (*output)(y, x, c) = normalize(abs(sum)/original.size());
            }
        }
    }

    return *output;
}

vector<complex<double>>& applyFFT1D(vector<complex<double>> &original) {
    if(original.size() == 1) return original;

    auto* output = new vector<complex<double>>(original.size());
    vector<complex<double>> even(original.size()/2);
    vector<complex<double>> odd(original.size()/2);

    for(int i = 0; i < original.size()/2; i++){
        even[i] = original[2*i];
        odd[i] = original[2*i + 1];
    }

    even = applyFFT1D(even);
    odd = applyFFT1D(odd);

    for (int i = 0; i < original.size()/2; i++){
        complex<double> comp(cos(2 * M_PI * i / (double)original.size()), -sin(2 * M_PI * i / (double)original.size()));
        (*output)[i] = even[i] + comp*odd[i];
        (*output)[i+original.size()/2] = even[i] - comp*odd[i];
    }
    return (*output);
}

vector<vector<complex<double>>>& applyFFT(CImg<int> &original){
    auto* output = new vector<vector<complex<double>>>(original.height());
    vector<vector<complex<double>>> temp(original.height());

    for (int y = 0; y < original.height(); y++) {
        vector<complex<double>> row(original.width());
        for (int x = 0; x < original.width(); x++) {
            row[x] = original(x, y);
        }
        temp[y] = applyFFT1D(row);
    }

    for (int x = 0; x < original.width(); x++){
        vector<complex<double>> col(original.height());
        for (int y = 0; y < original.height(); y++){
            col[y] = temp[y][x];
        }
        (*output)[x] = applyFFT1D(col);
    }

    return *output;
}

vector<complex<double>>& applyIFFT1D(vector<complex<double>> &original) {
    if(original.size() == 1) return original;

    auto* output = new vector<complex<double>>(original.size());
    vector<complex<double>> even(original.size()/2);
    vector<complex<double>> odd(original.size()/2);

    for(int i = 0; i < original.size()/2; i++){
        even[i] = original[2*i];
        odd[i] = original[2*i + 1];
    }

    even = applyIFFT1D(even);
    odd = applyIFFT1D(odd);

    for (int i = 0; i < original.size()/2; i++){
        complex<double> comp(cos(2 * M_PI * i / (double)original.size()), sin(2 * M_PI * i / (double)original.size()));
        (*output)[i] = even[i] + comp*odd[i];
        (*output)[i+original.size()/2] = (even[i] - comp*odd[i]);
    }
    return (*output);
}


CImg<int>& applyIFFT(vector<vector<complex<double>>> &original){
    auto* output = new CImg<int>(original[0].size(), original.size(), 1, 3, 0);
    vector<vector<complex<double>>> temp(original[0].size());

    for (int y = 0; y < original.size(); y++){
        vector<complex<double>> row(original[0].size());
        temp[y] = vector<complex<double>>(original[0].size());
        for (int x = 0; x < original[0].size(); x++){
            row[x] = original[x][y];
        }
        row = applyIFFT1D(row);
        for(int x = 0; x < original[0].size(); x++){
            temp[y][x] = row[x]/(double)original[0].size();
        }
    }

    for (int x = 0; x < original[0].size(); x++){
        vector<complex<double>> row(original.size());
        for (int y = 0; y < original.size(); y++){
            row[y] = temp[y][x];
        }
        row = applyIFFT1D(row);
        for (int y = 0; y < original.size(); y++){
            for (int s = 0; s < 3; s++){
                (*output)(x, y, s) = abs(row[y] / (double)original.size());
            }
        }
    }

    return *output;
}

vector<vector<complex<double>>>& swapQuarters(vector<vector<complex<double>>> &original){
    auto* output = new vector<vector<complex<double>>>;

    for (int x = 0; x < original.size(); x++){
        vector<complex<double>> column;
        for (int y = 0; y < original.size(); y++) {
            column.push_back(original[x][y]);
        }
        (*output).push_back(column); column.clear();
    }

    for (int x = 0; x < original.size()/2; x++){
        for (int y = 0; y < original[0].size()/2; y++) {
            swap((*output)[x][y], (*output)[original.size()/2 + x][original[0].size()/2 + y]);
            swap((*output)[original.size()/2 + x][y], (*output)[x][original[0].size()/2 + y]);
        }
    }

    return *output;
}


CImg<int>& getFourierImage(vector<vector<complex<double>>> &original){
    auto* output = new CImg<int>(original[0].size(), original.size(), 1, 3, 0);

    for (int x = 0; x < original[0].size(); x++) {
        for (int y = 0; y < original.size(); y++) {
            for (int c = 0; c < 3; c++) {
                (*output)(x, y, c) = normalize(log(abs(original[y][x])) * 15.0);
            }
        }
    }

    return *output;
}