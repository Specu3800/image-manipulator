#ifndef CHARACTERISTICS
#define CHARACTERISTICS

#include "../../lib/CImg.templ"
#include "../manipulations/t2-histogram.h"

using namespace std;
using namespace cimg_library;

float getMean(Histogram &histogram, float &result);
float getVariance(Histogram &histogram, float &result);
float getStandardDeviation(Histogram &histogram, float &result);
float getVariationCoefficientI(Histogram &histogram, float &result);
float getVariationCoefficientII(Histogram &histogram, float &result);
float getAsymmetryCoefficient(Histogram &histogram, float &result);
float getFlatteningCoefficient(Histogram &histogram, float &result);
float getInformationSourceEntropy(Histogram &histogram, float &result);

#endif //CHARACTERISTICS
