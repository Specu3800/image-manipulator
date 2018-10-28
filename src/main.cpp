#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <fstream>

#include "../lib/CImg.templ"

#include "manipulations/t0-other.h"
#include "manipulations/t1-basic.h"
#include "manipulations/t1-geometric.h"
#include "manipulations/t1-noise-removal.h"
#include "manipulations/t1-analysis.h"
#include "manipulations/t2-histogram.h"
#include "manipulations/t2-characteristics.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char* argv[]) {

    int whatDoWeDo = 0; // 0-nothing, 1-display and save image, 2-analysis

    CImg<int> image1;
    CImg<int> image2;
    float analysis;

    Histogram* image1Histogram;
    Histogram* image2Histogram;

    if (argc < 2 || argc > 5) {cout << "Wrong number of parameters.\nType --help to view the list of the available commands." << endl;}
    else if (argv[1] == string("--help")) displayHelp();
    else if (argv[1] == string("--hexponent")) {
        image1 = CImg<int>(argv[argc-2]);
        image2 = CImg<int>(image1.width(), image1.height(), 1, 3, 0);
        image1Histogram = new Histogram(image1);
        (*image1Histogram->getHistogramGraph()).display("beniz");
//        applyExponentialPDF(image1, image2, *image1Histogram);
//        image1.append(image2, 'x').display("COMPARATION", 0); //display
    }

    else {
        ifstream in1(argv[argc-2]);
        if (!in1.good()) {
            cout << argv[argc-2] << " does not exist, try again." << endl; exit(0);
        }

        whatDoWeDo = 1; //edit image
        image1 = CImg<int>(argv[argc-2]);
        image2 = CImg<int>(image1.width(), image1.height(), 1, 3, 0);

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
        else if (argv[1] == string("--min")) applyMinimumFilter(image1, image2, argv[2]);



        else {
            ifstream in2(argv[argc-1]);
            if (!in2.good()) {
                cout << argv[argc-1] << " does not exist, try again." << endl; exit(0);
            }
            image2 = CImg<int>(argv[argc-1]);
            whatDoWeDo = 2;
            if      (argv[1] == string("--mse")) getMeanSquareError(image1, image2, analysis);
            else if (argv[1] == string("--pmse")) getPeakMeanSquareError(image1, image2, analysis);
            else if (argv[1] == string("--snr")) getSignalToNoiseRatio(image1, image2, analysis);
            else if (argv[1] == string("--psnr")) getPeakSignalToNoiseRatio(image1, image2, analysis);
            else if (argv[1] == string("--md")) getMaximumDifference(image1, image2, analysis);

            else {
                cout << "No maching command. \nType --help to view the list of the available commands.";
                return 0;
            }
        }

        switch(whatDoWeDo){
            case 0:
                break;
            case 1:
                image1.save("original.bmp");
                image2.save("edited.bmp");
                image2.save(argv[argc - 1]); //save edited img in destination
                image1.append(image2, 'x').display("COMPARATION", 0); //display
                break;
            case 2:
                cout << "Analysis result for those two images equils: " << analysis << endl;
                break;
            default:
                break;
        }
    }
    return 0;
}







