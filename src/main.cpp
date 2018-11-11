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
#include "manipulations/t1-noise-removal.h"
#include "manipulations/t1-analysis.h"
#include "manipulations/t2-histogram.h"
#include "manipulations/t2-characteristics.h"
#include "manipulations/t2-filters.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char* argv[]) {

    vector<string> variant1 = {"--brightness", "--contrast", "--contrast2", "--negative",
                               "--hflip", "--vflip", "--dflip", "--shrink", "--enlarge",
                               "--adaptive", "--median", "--min", "--max",
                               "--hexponent", "--slaplace", "--slaplaceopt", "--orobertsii"};
    vector<string> variant2 = {"--mse", "--pmse", "--snr", "--psnr", "--md"};
    vector<string> variant3 = {"--cmean", "--cvariance", "--cstdev", "--cvarcoi", "--cvarcoii", "--casyco", "--cflaco", "--centropy"};

    CImg<int> image1;
    CImg<int> image2;

    float analysis = -1;

    Histogram image1Histogram;
    //Histogram image2Histogram;


    if (argc < 2 || argc > 5) {cout << "Wrong number of parameters.\nType --help to view the list of the available commands." << endl;}

    else if (argv[1] == string("--help")) displayHelp();

    else if (find(variant1.begin(), variant1.end(), argv[1]) != variant1.end()){

        if (fileExists(argv[argc - 2])) image1 = CImg<int>(argv[argc - 2]);
        image2 = CImg<int>(image1.width(), image1.height(), 1, 3, 0);
        image1Histogram = Histogram(image1);

        if (argv[1] == string("--brightness")) changeBrightness(image1, image2, argv[2]);
        else if (argv[1] == string("--contrast")) changeContrast(image1, image2, argv[2]);
        else if (argv[1] == string("--contrast2")) changeContrast2(image1, image2, argv[2]);
        else if (argv[1] == string("--negative")) changeToNegative(image1, image2);

        else if (argv[1] == string("--hflip")) doHorizontalFlip(image1, image2);
        else if (argv[1] == string("--vflip")) doVerticalFlip(image1, image2);
        else if (argv[1] == string("--dflip")) doDiagonalFlip(image1, image2);
        else if (argv[1] == string("--shrink")) shrinkBy(image1, image2, argv[2]);
        else if (argv[1] == string("--enlarge")) enlargeBy(image1, image2, argv[2]);

        else if (argv[1] == string("--adaptive")) applyAdaptiveMedianFilter(image1, image2, argv[2]);
        else if (argv[1] == string("--median")) applyMedianFilter(image1, image2, argv[2]);
        else if (argv[1] == string("--min")) applyMinimumFilter(image1, image2, argv[2]);
        else if (argv[1] == string("--max")) applyMaximumFilter(image1, image2, argv[2]);

        else if (argv[1] == string("--hexponent")) applyExponentialPDF(image1, image2, argv[2], image1Histogram);
        else if (argv[1] == string("--slaplace")) applyLaplacianFilter(image1, image2, argv[2], image1Histogram);
        else if (argv[1] == string("--slaplaceopt")) applyLaplacianFilterOptimised(image1, image2, image1Histogram);
        else if (argv[1] == string("--orobertsii")) applyRobertsOperatorFilter(image1, image2, image1Histogram);

        image1.save("original.bmp");
        image2.save("edited.bmp");
        image2.save(argv[argc - 1]); //save edited img in destination
        image1.append(image2, 'x').display("COMPARATION", false); //display

    } else if (find(variant2.begin(), variant2.end(), argv[1]) != variant2.end()){

        if (fileExists(argv[argc - 2])) image1 = CImg<int>(argv[argc - 2]);
        if (fileExists(argv[argc - 1])) image2 = CImg<int>(argv[argc - 1]);

        if (argv[1] == string("--mse")) getMeanSquareError(image1, image2, analysis);
        else if (argv[1] == string("--pmse")) getPeakMeanSquareError(image1, image2, analysis);
        else if (argv[1] == string("--snr")) getSignalToNoiseRatio(image1, image2, analysis);
        else if (argv[1] == string("--psnr")) getPeakSignalToNoiseRatio(image1, image2, analysis);
        else if (argv[1] == string("--md")) getMaximumDifference(image1, image2, analysis);

        cout << "Analysis result for those two images equils: " << analysis << endl;

    } else if (argv[1] == string("--histogram")) {

        if (fileExists(argv[argc - 1])) image1 = CImg<int>(argv[argc - 1]);
        image1Histogram = Histogram(image1);
        image1Histogram.displayUniformValues(atoi(argv[2]));
        image1Histogram.displayUniformHistogram(atoi(argv[2]), true);
        image1Histogram.displayCumulativeHistogram(atoi(argv[2]), true);

    } else if (find(variant3.begin(), variant3.end(), argv[1]) != variant3.end()) {

        if (fileExists(argv[argc - 1])) image1 = CImg<int>(argv[argc - 1]);
        image2 = CImg<int>(image1.width(), image1.height(), 1, 3, 0);
        image1Histogram = Histogram(image1);

        if (argv[1] == string("--cmean")) getMean(image1Histogram, analysis);
        else if (argv[1] == string("--cvariance")) getVariance(image1Histogram, analysis);
        else if (argv[1] == string("--cstdev")) getStandardDeviation(image1Histogram, analysis);
        else if (argv[1] == string("--cvarcoi")) getVariationCoefficientI(image1Histogram, analysis);
        else if (argv[1] == string("--cvarcoii")) getVariationCoefficientII(image1Histogram, analysis);
        else if (argv[1] == string("--casyco")) getAsymmetryCoefficient(image1Histogram, analysis);
        else if (argv[1] == string("--cflaco")) getFlatteningCoefficient(image1Histogram, analysis);
        else if (argv[1] == string("--centropy")) getInformationSourceEntropy(image1Histogram, analysis);

        if (analysis != -1) cout << "Analysis result for this image equils: " << analysis << endl;

    } else {
        cout << "No maching command. \nType --help to view the list of the available commands.";
    }

    return 0;
}







