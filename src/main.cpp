#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <fstream>
#include <vector>
#include <algorithm>
#include <time.h>

#include "../lib/CImg.templ"

#include "manipulations/t0-other.h"
#include "manipulations/t1-basic.h"
#include "manipulations/t1-geometric.h"
#include "manipulations/t1-noise-removal-operations.h"
#include "manipulations/t1-analysis.h"
#include "manipulations/t2-histogram.h"
#include "manipulations/t2-characteristics.h"
#include "manipulations/t2-filters.h"
#include "manipulations/t3-morphological-operations.h"
#include "manipulations/t3-segmentation.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char* argv[]) {

    vector<string> variant1 = {"--brightness", "--contrast", "--contrast2", "--negative",
                               "--hflip", "--vflip", "--dflip", "--shrink", "--enlarge",
                               "--adaptive", "--median", "--min", "--max",
                               "--hexponent", "--slaplace", "--slaplaceopt", "--orobertsii", "--osobel",
                               "--morphopi", "--morphopii", "--morphopiii",
                               "--segmentation",
                               "--labs"};
    vector<string> variant2 = {"--union", "--intersection", "--difference"};
    vector<string> variant3 = {"--mse", "--pmse", "--snr", "--psnr", "--md"};
    vector<string> variant4 = {"--cmean", "--cvariance", "--cstdev", "--cvarcoi", "--cvarcoii", "--casyco", "--cflaco", "--centropy"};

    CImg<int> image1;
    CImg<int> image2;
    CImg<int> image3;

    float analysis = -1;

    Histogram image1Histogram;


    if (argc < 2 || argc > 5) {cout << "Wrong number of parameters.\nType --help to view the list of the available commands." << endl;}

    else if (argv[1] == string("--help")) displayHelp();

    else if (argv[1] == string("--version")) displayVersion();

    else if (find(variant1.begin(), variant1.end(), argv[1]) != variant1.end()) {

        if (fileExists(argv[argc - 2])) image1 = CImg<int>(argv[argc - 2]);
        image1Histogram = Histogram(image1);

        if (argv[1] == string("--brightness")) image2 = changeBrightness(image1, atoi(argv[2]));
        else if (argv[1] == string("--contrast")) image2 = changeContrast(image1, atof(argv[2]));
        else if (argv[1] == string("--contrast2")) image2 = changeContrast2(image1, atof(argv[2]));
        else if (argv[1] == string("--negative")) image2 = changeToNegative(image1);

        else if (argv[1] == string("--hflip")) image2 = doHorizontalFlip(image1);
        else if (argv[1] == string("--vflip")) image2 = doVerticalFlip(image1);
        else if (argv[1] == string("--dflip")) image2 = doDiagonalFlip(image1);
        else if (argv[1] == string("--shrink")) image2 = shrinkBy(image1, atof(argv[2]));
        else if (argv[1] == string("--enlarge")) image2 = enlargeBy(image1, atof(argv[2]));

        else if (argv[1] == string("--adaptive")) image2 = applyAdaptiveMedianFilter(image1, atoi(argv[2]));
        else if (argv[1] == string("--median")) image2 = applyMedianFilter(image1, atoi(argv[2]));
        else if (argv[1] == string("--min")) image2 = applyMinimumFilter(image1, atoi(argv[2]));
        else if (argv[1] == string("--max")) image2 = applyMaximumFilter(image1, atoi(argv[2]));

        else if (argv[1] == string("--hexponent")) image2 = applyExponentialPDF(image1, atoi(argv[2]), image1Histogram);
        else if (argv[1] == string("--slaplace")) image2 = applyLaplacianFilter(image1, atoi(argv[2]), image1Histogram);
        else if (argv[1] == string("--slaplaceopt")) image2 = applyLaplacianFilterOptimised(image1, image1Histogram);
        else if (argv[1] == string("--orobertsii")) image2 = applyRobertsOperatorFilter(image1, image1Histogram);
        else if (argv[1] == string("--osobel")) image2 = applySobelOperatorFilter(image1, image1Histogram);

        else if (argv[1] == string("--union")) image2 = applyUnion(image1, image2);
        else if (argv[1] == string("--intersection")) image2 = applyIntersection(image1, image2);
        else if (argv[1] == string("--difference")) image2 = applyDifference(image1, image2);

        else if (argv[1] == string("--morphopi")) image2 = applyMorphologicalOperationI(image1);
        else if (argv[1] == string("--morphopii")) image2 = applyMorphologicalOperationII(image1);
        else if (argv[1] == string("--morphopiii")) image2 = applyMorphologicalOperationIII(image1);

        else if (argv[1] == string("--segmentation")) image2 = applySegmentation(image1);

        else if (argv[1] == string("--labs")){
            image2 = applyExponentialPDF(image1, atoi(argv[2]), image1Histogram);
            image3 = applyExponentialPDFSeparately(image1, atoi(argv[2]), image1Histogram);
            image1.append(image2, 'x').append(image3, 'x').display("COMPARE", false);
        }

        image1.save("original.bmp");
        image2.save("edited.bmp");
        image2.save(argv[argc - 1]); //save edited img in destination
        image1.append(image2, 'x').display("COMPARATION", false); //display

    } else if (find(variant2.begin(), variant2.end(), argv[1]) != variant2.end()){

        if (fileExists(argv[argc - 3])) image1 = CImg<int>(argv[argc - 3]);
        if (fileExists(argv[argc - 2])) image2 = CImg<int>(argv[argc - 2]);

        if (argv[1] == string("--union")) image3 = applyUnion(image1, image2);
        else if (argv[1] == string("--intersection")) image3 = applyIntersection(image1, image2);
        else if (argv[1] == string("--difference")) image3 = applyDifference(image1, image2);

        image1.save("original.bmp");
        image2.save("edited.bmp");
        image2.save(argv[argc - 1]); //save edited img in destination
        image1.append(image2, 'x').append(image3, 'x').display("COMPARATION", false); //display

    } else if (find(variant3.begin(), variant3.end(), argv[1]) != variant3.end()){

        if (fileExists(argv[argc - 2])) image1 = CImg<int>(argv[argc - 2]);
        if (fileExists(argv[argc - 1])) image2 = CImg<int>(argv[argc - 1]);

        if (argv[1] == string("--mse")) analysis = getMeanSquareError(image1, image2);
        else if (argv[1] == string("--pmse")) analysis = getPeakMeanSquareError(image1, image2);
        else if (argv[1] == string("--snr")) analysis = getSignalToNoiseRatio(image1, image2);
        else if (argv[1] == string("--psnr")) analysis = getPeakSignalToNoiseRatio(image1, image2);
        else if (argv[1] == string("--md")) analysis = getMaximumDifference(image1, image2);

        cout << "Analysis result for those two images equils: " << analysis << endl;

    } else if (argv[1] == string("--histogram")) {

        if (fileExists(argv[argc - 1])) image1 = CImg<int>(argv[argc - 1]);

        image1Histogram = Histogram(image1);
        image1Histogram.displayUniformValues(atoi(argv[2]));
        image1Histogram.displayUniformHistogram(atoi(argv[2]), true);
        image1Histogram.displayCumulativeHistogram(atoi(argv[2]), true);

    } else if (find(variant4.begin(), variant4.end(), argv[1]) != variant4.end()) {

        if (fileExists(argv[argc - 1])) image1 = CImg<int>(argv[argc - 1]);
        image1Histogram = Histogram(image1);

        if (argv[1] == string("--cmean")) analysis = getMean(image1Histogram);
        else if (argv[1] == string("--cvariance")) analysis = getVariance(image1Histogram);
        else if (argv[1] == string("--cstdev")) analysis = getStandardDeviation(image1Histogram);
        else if (argv[1] == string("--cvarcoi")) analysis = getVariationCoefficientI(image1Histogram);
        else if (argv[1] == string("--cvarcoii")) analysis = getVariationCoefficientII(image1Histogram);
        else if (argv[1] == string("--casyco")) analysis = getAsymmetryCoefficient(image1Histogram);
        else if (argv[1] == string("--cflaco")) analysis = getFlatteningCoefficient(image1Histogram);
        else if (argv[1] == string("--centropy")) analysis = getInformationSourceEntropy(image1Histogram);

        if (analysis != -1) cout << "Analysis result for this image equils: " << analysis << endl;

    } else {
        cout << "No maching command. \nType --help to view the list of the available commands.";
    }

    return 0;
}







