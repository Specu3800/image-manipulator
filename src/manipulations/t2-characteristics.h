#ifndef CHARACTERISTICS
#define CHARACTERISTICS

#include "../../lib/CImg.templ"
#include "../manipulations/t2-histogram.h"

using namespace std;
using namespace cimg_library;

float getMean(Histogram &histogram);
float getVariance(Histogram &histogram);
float getStandardDeviation(Histogram &histogram);
float getVariationCoefficientI(Histogram &histogram);
float getVariationCoefficientII(Histogram &histogram);
float getAsymmetryCoefficient(Histogram &histogram);
float getFlatteningCoefficient(Histogram &histogram);
float getInformationSourceEntropy(Histogram &histogram);

#endif //CHARACTERISTICS
