#ifndef FOURIER_FILTERS
#define FOURIER_FILTERS

#include "lib/CImg.templ"
#include <vector>
#include <complex>

using namespace std;
using namespace cimg_library;

vector<vector<complex<double>>>& applyLowpassFilter(vector<vector<complex<double>>> &original);
vector<vector<complex<double>>>& applyHighpassFilter(vector<vector<complex<double>>> &original);
vector<vector<complex<double>>>& applyBandpassFilter(vector<vector<complex<double>>> &original);
vector<vector<complex<double>>>& applyBandcutFilter(vector<vector<complex<double>>> &original);
vector<vector<complex<double>>>& applyHighpassFilterWithEdgeDirection(vector<vector<complex<double>>> &original);
vector<vector<complex<double>>>& applyPhaseModifyingFilter(vector<vector<complex<double>>> &original);

#endif //FOURIER_FILTERS
