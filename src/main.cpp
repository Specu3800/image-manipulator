#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cmath>

#include "../lib/CImg.templ"

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

void displayHelp() {
    cout <<
    "###############################################################################\n"
    "#########################---   " << (char)27 << "[1m" << "Image Manipulator" << (char)27 << "[0m" << "   ---#########################\n"
    "###############################################################################\n"
    "#                                                                             #\n"
    "#                          Michał Suliborski  217863                          #\n"
    "#                          Arek Zasina        217868                          #\n"
    "#                                                                             #\n"
    "#                             Politechnika Łódzka                             #\n"
    "#                                 2018/2019                                   #\n"
    "#                                                                             #\n"
    "###############################################################################\n"
    "\n"
    << (char)27 << "[1m" << "USAGE:\n" << (char)27 << "[0m" <<
    "   image-manipulator --command [-argument=value [...]]\n"
    "\n"
    << (char)27 << "[1m" << "COMMANDS:\n" << (char)27 << "[0m" <<
    "   --brightness mod src dest\n"
    "       modifies brightess of image in src by a modificator(-255 <= mod <= 255)\n"
    "       value and saves image in dest\n"
    "\n"
    "   --contrast mod src dest\n"
    "       modifies contrast of image in src by a modificator(0 < mod <= infinity)\n"
    "       value and saves image in dest\n"
    "\n"
    "   --negative src dest\n"
    "      outputs negative of image in src to dest\n"
    "\n"
    "   --hflip src dest\n"
    "      outputs horizontally fliped image in src to dest\n"
    "\n"
    "   --vflip src dest\n"
    "      outputs vertically fliped image in src to dest\n"
    "\n"
    "   --dflip src dest\n"
    "      outputs diagonally fliped image in src to dest\n"
    "\n"
    "   --shrik fac src dest\n"
    "      outputs image in src shrinked by a factor of fac to dest\n"
    "\n"
    "   --enlarge fac src dest\n"
    "      outputs image in src enlarged by a factor of fac to dest\n"  //add bipolar interpolation
    "\n"
    "   --adaptive dep src dest\n"
    "      outputs image in src with adaptive filter with depth of dep \n"
    "      applied to dest\n"
    "\n"
    "   --min dep src dest\n"
    "      outputs image in src with minimum filter with depth of dep \n"
    "      applied to dest\n"
    "\n"
    "   --max dep src dest\n"
    "      outputs image in src with maximum filter with depth of dep \n"
    "      applied to dest\n"
    "\n"
    "   --mse clean noisy denoised\n"
    "      displays mean square error analysis between clean, \n"
    "      noisy and denoised images\n"
    "\n"
    "   --pmse clean noisy denoised\n"
    "      displays peak mean square error analysis between clean, \n"
    "      noisy and denoised images\n"
    "\n"
    "   --snr clean noisy denoised\n"
    "      displays signal to noise ratio analysis between clean, \n"
    "      noisy and denoised images\n"
    "\n"
    "   --psnr clean noisy denoised\n"
    "      displays peak signal to noise ratio analysis between clean, \n"
    "      noisy and denoised images\n"
    "\n"
    "   --md clean noisy denoised\n"
    "      displays maximum difference analysis between clean, \n"
    "      noisy and denoised images\n";
}





