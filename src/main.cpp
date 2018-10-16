#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cmath>

#include "../lib/CImg.templ"

#include "manipulations/t0-other.h"
#include "manipulations/t1-basic.h"
#include "manipulations/t1-geometric.h"
#include "manipulations/t1-noise-removal.h"
#include "manipulations/t1-analysis.h"

using namespace std;
using namespace cimg_library;

void displayHelp();

int main(int argc, char* argv[]) {

    CImg<int> image1;
    CImg<int> image2;
    if (argc < 2 || argc > 5) {cout << "Wrong number of parameters.\nType --help to view the list of the available commands." << endl; exit(0); }
    else if (argv[1] == string("--help")) displayHelp();
    else {
        image1 = CImg<int>(argv[argc-2]);
        image2 = CImg<int>(image1.width(), image1.height(), 1, 3, 0);

        if (argv[1] == string("--brightness")) changeBrightness(image1, image2, argv[2]);
        else if (argv[1] == string("--contrast")) changeContrast(image1, image2, argv[2]);
        else if (argv[1] == string("--negative")) changeToNegative(image1, image2);

        else if (argv[1] == string("--hflip")) doHorizontalFlip(image1, image2);
        else if (argv[1] == string("--vflip")) doVerticalFlip(image1, image2);
        else if (argv[1] == string("--dflip")) doDiagonalFlip(image1, image2);
        else if (argv[1] == string("--shrink")) shrinkBy(image1, image2, argv[2]);
        else if (argv[1] == string("--enlarge")) enlargeBy(image1, image2, argv[2]);

        else if (argv[1] == string("--adaptive")) {applyAdaptiveMedianFilter(image1, image2, argv[2]);}
        else if (argv[1] == string("--median")) {applyMedianFilter(image1, image2, argv[2]);}
        else if (argv[1] == string("--min")) applyMinimumFilter(image1, image2, argv[2]);
        else if (argv[1] == string("--max")) applyMaximumFilter(image1, image2, argv[2]);

        else if (argv[1] == string("--mse")) getMeanSquareError(image1, image2);
        else if (argv[1] == string("--pmse")) getPeakMeanSquareError(image1, image2);
        else if (argv[1] == string("--snr")) getSignalToNoiseRatio(image1, image2);
        else if (argv[1] == string("--psnr")) getPeakSignalToNoiseRatio(image1, image2);
        else if (argv[1] == string("--md")) getMaximumDifference(image1, image2);

        else cout << "No maching command. \nType --help to view the list of the available commands.";

        image2.save(argv[argc-1]); //save edited img in destination
        image1.save("../out/original.bmp");
        image2.save("../out/edited.bmp");
        image1.append(image2, 'x').display("COMPARATION"); //display
    }
    return 0;
}







