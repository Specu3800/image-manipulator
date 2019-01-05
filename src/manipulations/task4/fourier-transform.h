#ifndef DISCRETE_FOURIER_TRANSFORM
#define DISCRETE_FOURIER_TRANSFORM

#include "lib/CImg.templ"
#include <vector>
#include <complex>


using namespace std;
using namespace cimg_library;

vector<vector<complex<double>>>& applyDFT(CImg<int> &original);
CImg<int>& applyIDFT(vector<vector<complex<double>>> &original);

vector<vector<complex<double>>>& applyFFT(CImg<int> &original);
CImg<int>& applyIFFT(vector<vector<complex<double>>> &original);

vector<vector<complex<double>>>& swapQuarters(vector<vector<complex<double>>> &original);

CImg<int>& getFourierImage(vector<vector<complex<double>>> &original);

#endif //DISCRETE_FOURIER_TRANSFORM
