#ifndef FOURIER_FILTERS
#define FOURIER_FILTERS

#include "lib/CImg.templ"
#include <vector>
#include <complex>

using namespace std;
using namespace cimg_library;

vector<vector<complex<double>>>& applyLowpassFilter(vector<vector<complex<double>>> &original, int threshold);
vector<vector<complex<double>>>& applyHighpassFilter(vector<vector<complex<double>>> &original, int threshold);
vector<vector<complex<double>>>& applyBandpassFilter(vector<vector<complex<double>>> &original, int threshold, int width);
vector<vector<complex<double>>>& applyBandcutFilter(vector<vector<complex<double>>> &original, int threshold, int width);
vector<vector<complex<double>>>& applyHighpassFilterWithEdgeDirection(vector<vector<complex<double>>> &original, double alpha, double beta, double radius);
vector<vector<complex<double>>>& applyPhaseModifyingFilter(vector<vector<complex<double>>> &original, int l, int k, double j);

#endif //FOURIER_FILTERS
