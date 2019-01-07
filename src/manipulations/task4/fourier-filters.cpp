#include <cmath>
#include <vector>
#include <complex>
#include <cmath>
#include <iostream>

#include "fourier-filters.h"
#include "lib/CImg.templ"

using namespace std;
using namespace cimg_library;

vector<vector<complex<double>>>& applyLowpassFilter(vector<vector<complex<double>>> &original, int threshold){
    auto* edited = new vector<vector<complex<double>>>;
    *edited = original;

    for (int x = 1; x < original.size(); x++)
    {
        for (int y = 1; y < original[1].size(); y++)
        {
            double d = sqrt( pow(x - original.size() / 2.0 , 2.0) + pow(y - original[1].size() / 2.0, 2.0)   );
            if (d > threshold)
            {
                edited -> at(y).at(x) = (0.0, 0.0);
            }
        }
    }

    return *edited;
}

vector<vector<complex<double>>>& applyHighpassFilter(vector<vector<complex<double>>> &original, int threshold){
    auto* edited = new vector<vector<complex<double>>>;
    *edited = original;
    for (int x = 0; x < original.size(); x++)
    {
        for (int y = 0; y < original[1].size(); y++)
        {
            double d = sqrt( pow(x - original.size() / 2.0 , 2.0) + pow(y - original[0].size() / 2.0, 2.0)   );
            if (d <= threshold)
            {
                edited -> at(y).at(x) = (0.0, 0.0);
            }
        }
    }
    return *edited;
}

vector<vector<complex<double>>>& applyBandpassFilter(vector<vector<complex<double>>> &original, int threshold, int width){
    auto* edited = new vector<vector<complex<double>>>;
    *edited = original;
    for (int x = 0; x < original.size(); x++)
    {
        for (int y = 0; y < original[0].size(); y++)
        {
            double d = sqrt( pow(x - edited -> size() / 2.0 , 2.0) + pow(y - edited[0].size() / 2.0, 2.0)   );
            if ((threshold - width / 2.0 > d) || (threshold + width / 2.0 < d) )
            {
                edited -> at(y).at(x) = (0.0, 0.0);
            }
        }
    }
    return *edited;
}

vector<vector<complex<double>>>& applyBandcutFilter(vector<vector<complex<double>>> &original, int threshold, int width){
    auto* edited = new vector<vector<complex<double>>>;
    *edited = original;
    for (int x = 0; x < original.size(); x++)
    {
        for (int y = 0; y < original[0].size(); y++)
        {
            double d = sqrt( pow(x - original.size() / 2.0 , 2.0) + pow(y - original[0].size() / 2.0, 2.0)   );
            if ((threshold - width / 2.0 <= d) && (threshold + width / 2.0 >= d) )
            {
                edited -> at(y).at(x) = (0.0, 0.0);
            }
        }
    }

    return *edited;
}

vector<vector<complex<double>>>& applyHighpassFilterWithEdgeDirection(vector<vector<complex<double>>> &original, CImg<int> &mask){
    auto* edited = new vector<vector<complex<double>>>;
    *edited = original;
    for (int x = 0; x < original.size(); x++)
    {
        for (int y = 0; y < original[0].size(); y++)
        {
            if ( mask(y, x) == 0)
            {
                edited -> at(y).at(x) = (0.0, 0.0);
            }
        }
    }

    return *edited;
}

vector<vector<complex<double>>>& applyPhaseModifyingFilter(vector<vector<complex<double>>> &original, int l, int k, double j){
    auto* edited = new vector<vector<complex<double>>>;
    *edited = original;
    for (int x = 0; x < original.size(); x++)
    {
        for (int y = 0; y < original[0].size(); y++)
        {

            double re = cos( j * ((x * k * -2.0 * M_PI) / original.size() + (y*l*-2.0*M_PI)/original[0].size() + (k+l)*M_PI ));
            double im = sin( j * ((x * k * -2.0 * M_PI) / original.size() + (y*l*-2.0*M_PI)/original[0].size() + (k+l)*M_PI ));
            complex<double> p(re, im);
            (*edited).at(y).at(x) = original.at(y).at(x) * p;
            //cout <<"x: " <<  x << " y: " << y << " newVal: " << (*edited).at(y).at(x) << " oldVal: " << original.at(y).at(x) << " re: " << re << " im: " << im << " p: " << p  << endl;
        }
    }


    return *edited;
}

