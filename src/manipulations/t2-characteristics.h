#ifndef CHARACTERISTICS
#define CHARACTERISTICS

#include "../../lib/CImg.templ"

using namespace std;
using namespace cimg_library;

float getMean(CImg<int> &image1, float &result);
float getVariance(CImg<int> &image1, float &result);
float getStandardDeviation(CImg<int> &image, float &result);
float getVariationCoefficientI(CImg<int> &image, float &result);
float getVariationCoefficientII(CImg<int> &image, float &result);
float getAsymmetryCoefficient(CImg<int> &image, float &result);
float getFlatteningCoefficient(CImg<int> &image, float &result);
float getInformationSourceEntropy(CImg<int> &image, float &result);

#endif //CHARACTERISTICS
