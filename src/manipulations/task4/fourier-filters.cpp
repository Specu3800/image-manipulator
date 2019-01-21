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
    for (const auto &i : original) (*edited).push_back(i);

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
    for (const auto &i : original) (*edited).push_back(i);

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
    for (const auto &i : original) (*edited).push_back(i);

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
    for (const auto &i : original) (*edited).push_back(i);

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

vector<vector<complex<double>>>& applyHighpassFilterWithEdgeDirection(vector<vector<complex<double>>> &original, double alpha, double beta, double radius){
    auto* edited = new vector<vector<complex<double>>>;
    for (const auto &i : original) (*edited).push_back(i);

    alpha = (-alpha)/(180.0/M_PI);
    beta = (-beta)/(180.0/M_PI);
    int xcentr = original.size()/2;
    int ycentr = original[0].size()/2;
    cout << alpha << " " << beta << endl;
    for (int x = 0; x < original.size(); x++)
    {
        for (int y = 0; y < original[0].size(); y++)
        {

            if (((((double)(x - xcentr)/(double)(y - ycentr)) < tan(alpha+beta)) || (((double)(x - xcentr)/(double)(y - ycentr)) > tan(alpha-beta))) || sqrt(pow(x - xcentr, 2) + pow(y - ycentr, 2)) < radius)
            {
                edited -> at(y).at(x) = (0.0, 0.0);
            }
        }
    }

    return *edited;
}

vector<vector<complex<double>>>& applyPhaseModifyingFilter(vector<vector<complex<double>>> &original, int l, int k, double j){
    auto* edited = new vector<vector<complex<double>>>;
    for (const auto &i : original) (*edited).push_back(i);

    for (int x = 0; x < original.size(); x++)
    {
        for (int y = 0; y < original[0].size(); y++)
        {
            double re = cos( j * ((x * k * -2.0 * M_PI) / original.size() + (y*l*-2.0*M_PI)/original[0].size() + (k+l)*M_PI ));
            double im = sin( j * ((x * k * -2.0 * M_PI) / original.size() + (y*l*-2.0*M_PI)/original[0].size() + (k+l)*M_PI ));
            complex<double> p(re, im);
            (*edited).at(y).at(x) = original.at(y).at(x) * p;
        }
    }

    return *edited;
}

