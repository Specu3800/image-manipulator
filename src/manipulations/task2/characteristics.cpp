#include <iostream>
#include "lib/CImg.templ"
#include "characteristics.h"

using namespace std;
using namespace cimg_library;


float getMean(Histogram &histogram){
    float sum = 0;

    for (int m = 0; m < 256; m++) {
        sum += m * histogram.uniform[0][m];
    }

    float MEAN = (1.0 /histogram.sourceImageP) * sum;
    return MEAN;
}

float getVariance(Histogram &histogram){
    float sum = 0;

    for (int m = 0; m < 256; m++) {
        sum += pow((m-getMean(histogram)), 2) * histogram.uniform[0][m];
    }

    float VARIANCE = (1.0/histogram.sourceImageP) * sum;
    return VARIANCE;
}

float getStandardDeviation(Histogram &histogram){
    float STANDARD_DEVIATION = sqrt(getVariance(histogram));
    return STANDARD_DEVIATION;
}

float getVariationCoefficientI(Histogram &histogram){
    float VARIATION_COEFFICIENT_I = getStandardDeviation(histogram) / getMean(histogram);
    return VARIATION_COEFFICIENT_I;
}

float getVariationCoefficientII(Histogram &histogram){
    float sum = 0;

    for (int m = 0; m < 256; m++) {
        sum += pow(histogram.uniform[0][m], 2);
    }

    float VARIATION_COEFFICIENT_II = pow(1.0/histogram.sourceImageP, 2) * sum;
    return VARIATION_COEFFICIENT_II;
}

float getAsymmetryCoefficient(Histogram &histogram){
    float sum = 0;

    for (int m = 0; m < 256; m++) {
        sum += pow(m - getMean(histogram), 3) * histogram.uniform[0][m];
    }

    float ASYMETRY_COEFFICIENT = (1.0/pow(getStandardDeviation(histogram), 3)) *
        (1.0 /histogram.sourceImageP) * sum;
    return ASYMETRY_COEFFICIENT;
}

float getFlatteningCoefficient(Histogram &histogram){
    float sum = 0;

    for (int m = 0; m < 256; m++) {
        sum += pow(m - getMean(histogram), 4) * histogram.uniform[0][m];
    }

    float FLATTENING_COEFFICIENT = (1.0/pow(getStandardDeviation(histogram), 4)) *
            (1.0/histogram.sourceImageP) * sum - 3;
    return FLATTENING_COEFFICIENT;
}

float getInformationSourceEntropy(Histogram &histogram){
    float sum = 0;

    for (int m = 0; m < 256; m++) {
        if (histogram.uniform[0][m] != 0) sum += histogram.uniform[0][m] * log2(histogram.probability[0][m]);
    }

    float INFORMATION_SOURCE_ENTROPY = (-1.0/histogram.sourceImageP) * sum;
    return INFORMATION_SOURCE_ENTROPY;
}
