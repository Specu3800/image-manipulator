#include <iostream>
#include "../../lib/CImg.templ"
#include "t2-characteristics.h"

using namespace std;
using namespace cimg_library;


float getMean(Histogram &histogram, float &result){
    float sum = 0;

    for (int m = 0; m < 256; m++) {
        sum += m * histogram.uniform[0][m];
    }

    float MEAN = (1.0 /histogram.sourceImageP) * sum;
    result = MEAN;
    return MEAN;
}

float getVariance(Histogram &histogram, float &result){
    float sum = 0;

    for (int m = 0; m < 256; m++) {
        sum += pow((m-getMean(histogram, result)), 2) * histogram.uniform[0][m];
    }

    float VARIANCE = (1.0/histogram.sourceImageP) * sum;
    result = VARIANCE;
    return VARIANCE;
}

float getStandardDeviation(Histogram &histogram, float &result){
    float STANDARD_DEVIATION = sqrt(getVariance(histogram, result));
    result = STANDARD_DEVIATION;
    return STANDARD_DEVIATION;
}

float getVariationCoefficientI(Histogram &histogram, float &result){
    float VARIATION_COEFFICIENT_I = getStandardDeviation(histogram, result) / getMean(histogram, result);
    result = VARIATION_COEFFICIENT_I;
    return VARIATION_COEFFICIENT_I;
}

float getVariationCoefficientII(Histogram &histogram, float &result){
    float sum = 0;

    for (int m = 0; m < 256; m++) {
        sum += pow(histogram.uniform[0][m], 2);
    }

    float VARIATION_COEFFICIENT_II = pow(1.0/histogram.sourceImageP, 2) * sum;
    result = VARIATION_COEFFICIENT_II;
    return VARIATION_COEFFICIENT_II;
}

float getAsymmetryCoefficient(Histogram &histogram, float &result){
    float sum = 0;

    for (int m = 0; m < 256; m++) {
        sum += pow(m - getMean(histogram, result), 3) * histogram.uniform[0][m];
    }

    float ASYMETRY_COEFFICIENT = (1.0/pow(getStandardDeviation(histogram, result), 3)) *
        (1.0 /histogram.sourceImageP) * sum;
    result = ASYMETRY_COEFFICIENT;
    return ASYMETRY_COEFFICIENT;
}

float getFlatteningCoefficient(Histogram &histogram, float &result){
    float sum = 0;

    for (int m = 0; m < 256; m++) {
        sum += pow(m - getMean(histogram, result), 4) * histogram.uniform[0][m] - 3;
    }

    float FLATTENING_COEFFICIENT = (1.0/pow(getStandardDeviation(histogram, result), 4)) *
            (1.0/histogram.sourceImageP) * sum;
    result = FLATTENING_COEFFICIENT;
    return FLATTENING_COEFFICIENT;
}

float getInformationSourceEntropy(Histogram &histogram, float &result){
    float sum = 0;

    for (int m = 0; m < 256; m++) {
        cout << histogram.uniform[0][m] * log2(histogram.probability[0][m]) << endl;
        sum += histogram.uniform[0][m] * log2(histogram.probability[0][m]);
    }

    float INFORMATION_SOURCE_ENTROPY = (-1.0/histogram.sourceImageP) * sum;
    result = INFORMATION_SOURCE_ENTROPY;
    return INFORMATION_SOURCE_ENTROPY;
}
