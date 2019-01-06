#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <fstream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <chrono>

#include "../lib/CImg.templ"

#include "manipulations/helpers.h"
#include "src/manipulations/task1/basic.h"
#include "src/manipulations/task1/geometric.h"
#include "src/manipulations/task1/noise-removal-operations.h"
#include "src/manipulations/task1/analysis.h"
#include "src/manipulations/task2/histogram.h"
#include "src/manipulations/task2/characteristics.h"
#include "src/manipulations/task2/filters.h"
#include "src/manipulations/task3/morphological-operations.h"
#include "src/manipulations/task3/segmentation.h"
#include "src/manipulations/task4/fourier-transform.h"
#include "src/manipulations/task4/fourier-filters.h"

using namespace std;
using namespace cimg_library;
using namespace std::chrono;

int main(int argc, char* argv[]) {

    vector<string> variant1 = {"--brightness", "--contrast", "--contrast2", "--negative",
                               "--hflip", "--vflip", "--dflip", "--shrink", "--enlarge",
                               "--adaptive", "--median", "--min", "--max",
                               "--hexponent", "--hexponentsep", "--slaplace", "--slaplaceopt", "--orobertsii", "--osobel",
                               "--erosion", "--dilation", "--opening", "--closing", "--hmt",
                               "--oborder", "--iborder", "--ioborder", "--filling", "--removing",
                               "--segmentation"};
    vector<string> variant2 = {"--union", "--intersection", "--difference"};
    vector<string> variant3 = {"--mse", "--pmse", "--snr", "--psnr", "--md"};
    vector<string> variant4 = {"--cmean", "--cvariance", "--cstdev", "--cvarcoi", "--cvarcoii", "--casyco", "--cflaco", "--centropy"};
    vector<string> variant5 = {"--dft", "--idft", "--fft", "--ifft"};
    vector<string> variant6 = {"--lowpass", "--highpass", "--bandpass", "--bandcut", "--hpedge", "--pmod"};
    vector<string> variant7 = {"--labs"};

    CImg<int> image1;
    CImg<int> image2;
    CImg<int> image3;

    float analysis = -1;

    Histogram image1Histogram;


    if (argc < 2 || argc > 7) {cout << "Wrong number of parameters.\nType --help to view the list of the available commands." << endl;}

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

        else if (argv[1] == string("--hexponent")) image2 = applyExponentialPDF(image1, atoi(argv[2]), atoi(argv[3]), image1Histogram);
        else if (argv[1] == string("--hexponentsep")) image2 = applyExponentialPDFSeparately(image1, atoi(argv[2]), atoi(argv[3]));
        else if (argv[1] == string("--slaplace")) {
            high_resolution_clock::time_point t1 = high_resolution_clock::now();
            image2 = applyLaplacianFilter(image1, atoi(argv[2]));
            high_resolution_clock::time_point t2 = high_resolution_clock::now();
            cout << "Execution time: " << duration_cast<microseconds>( t2 - t1 ).count() << endl;
        }
        else if (argv[1] == string("--slaplaceopt")) {
            high_resolution_clock::time_point t1 = high_resolution_clock::now();
            image2 = applyLaplacianFilterOptimised(image1);
            high_resolution_clock::time_point t2 = high_resolution_clock::now();
            cout << "Execution time: " << duration_cast<microseconds>( t2 - t1 ).count() << endl;
        }
        else if (argv[1] == string("--orobertsii")) image2 = applyRobertsOperatorFilter(image1);
        else if (argv[1] == string("--osobel")) image2 = applySobelOperatorFilter(image1);

        else if (argv[1] == string("--union")) image2 = applyUnion(image1, image2);
        else if (argv[1] == string("--intersection")) image2 = applyIntersection(image1, image2);
        else if (argv[1] == string("--difference")) image2 = applyDifference(image1, image2);

        else if (argv[1] == string("--erosion")) image2 = applyErosion(image1, getNormalMask(atoi(argv[2])));
        else if (argv[1] == string("--dilation")) image2 = applyDilation(image1, getNormalMask(atoi(argv[2])));
        else if (argv[1] == string("--opening")) image2 = applyOpening(image1, getNormalMask(atoi(argv[2])));
        else if (argv[1] == string("--closing")) image2 = applyClosing(image1, getNormalMask(atoi(argv[2])));
        else if (argv[1] == string("--hmt")) image2 = applyHMT(image1, getHMTMask(atoi(argv[2])));
        else if (argv[1] == string("--segmentation")) image2 = applySegmentation(image1, atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
        else if (argv[1] == string("--oborder")) image2 = applyOuterBorder(image1, atoi(argv[2])); //M1
        else if (argv[1] == string("--iborder")) image2 = applyInnerBorder(image1, atoi(argv[2])); //M1
        else if (argv[1] == string("--ioborder")) image2 = applyInnerOuterBorder(image1, atoi(argv[2])); //M1
        else if (argv[1] == string("--filling")) image2 = applyFilling(image1, atoi(argv[2]), atoi(argv[3]), 4); //M2
        else if (argv[1] == string("--removing")) image2 = applyRemoving(image1, atoi(argv[2]), atoi(argv[3]), 3); //M3

        image1.save("original.bmp");
        image2.save("edited.bmp");
        image2.save(argv[argc - 1]); //save edited img in destination
        image1.append(image2, 'x').display("COMPARATION", false); //display
        //disp.display(image1.append(image2, 'x'));

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

    } else if (find(variant5.begin(), variant5.end(), argv[1]) != variant5.end()) {

        if (fileExists(argv[argc - 1])) image1 = CImg<int>(argv[argc - 1]);
        vector<vector<complex<double>>> fourier;

        if (argv[1] == string("--dft")) fourier = applyDFT(image1);
        else if (argv[1] == string("--idft")) fourier = applyFFT(image1);

        fourier = swapQuarters(fourier);
        image2 = getFourierImage(fourier);

        image1.save("original.bmp");
        image2.save("edited.bmp");
        image2.save(argv[argc - 1]); //save edited img in destination
        image1.append(image2, 'x').append(image3, 'x').display("COMPARATION", false); //display

    } else if (find(variant6.begin(), variant6.end(), argv[1]) != variant6.end()) {

        if (fileExists(argv[argc - 1])) image1 = CImg<int>(argv[argc - 2]);
        vector<vector<complex<double>>> fourier = applyFFT(image1);
        fourier = swapQuarters(fourier);

        if (argv[1] == string("--lowpass")) fourier = applyLowpassFilter(fourier, atoi(argv[2]));
        else if (argv[1] == string("--highpass")) fourier = applyHighpassFilter(fourier, atoi(argv[2]));
        else if (argv[1] == string("--bandpass")) fourier = applyBandpassFilter(fourier, atoi(argv[2]), atoi(argv[3]));
        else if (argv[1] == string("--bandcut")) fourier = applyBandcutFilter(fourier, atoi(argv[2]), atoi(argv[3]));
        else if (argv[1] == string("--hpedge")) fourier = applyHighpassFilterWithEdgeDirection(fourier, *(new CImg<int>(argv[2])));
        else if (argv[1] == string("--pmod")) fourier = applyPhaseModifyingFilter(fourier, atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));

        getFourierImage(fourier).display();

        fourier = swapQuarters(fourier);
        image2 = applyIDFT(fourier);

        image1.save("original.bmp");
        image2.save("edited.bmp");
        image2.save(argv[argc - 1]); //save edited img in destination
        image1.append(image2, 'x').append(image3, 'x').display("COMPARATION", false); //display

    } else if (find(variant7.begin(), variant7.end(), argv[1]) != variant7.end()) {
        if (argv[1] == string("--labs")) {
            /// HERE WE CAN WORK ON LABS
        }
    } else {
        cout << "No maching command. \nType --help to view the list of the available commands.";
    }

    return 0;
}


