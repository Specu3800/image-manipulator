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
    CImg<int> originalImage("../img/noise-color-24bit/impulse-noise/lenac_impulse3.bmp"), editedImage(1,1,1,3,0); //x, y, z, rgb channels, rgb vals
    float analysisResult = -1;
    originalImage.save("../out/original.bmp");


    if (argc < 2 || argc > 5) {cout << "Wrong number of parameters.\nType --help to view the list of the available commands." << endl; exit(0);
    } else {
        if (argv[1] == string("--help")) displayHelp();

        else if (argv[1] == string("--brightness")) editedImage = CImg<int>(changeBrightness(originalImage, argv[2]));
        else if (argv[1] == string("--contrast")) editedImage = CImg<int>(changeContrast(originalImage, argv[2]));
        else if (argv[1] == string("--negative")) editedImage = CImg<int>(changeToNegative(originalImage));

        else if (argv[1] == string("--hflip")) editedImage = CImg<int>(doHorizontalFlip(originalImage));
        else if (argv[1] == string("--vflip")) editedImage = CImg<int>(doVerticalFlip(originalImage));
        else if (argv[1] == string("--dflip")) editedImage = CImg<int>(doDiagonalFlip(originalImage));
        else if (argv[1] == string("--shrink")) editedImage = CImg<int>(shrinkBy(originalImage, argv[2]));
        else if (argv[1] == string("--enlarge")) editedImage = CImg<int>(enlargeBy(originalImage, argv[2]));

        else if (argv[1] == string("--adaptive")) editedImage = CImg<int>(applyAdaptiveMedianFilter(originalImage, argv[2]));
        else if (argv[1] == string("--min")) editedImage = CImg<int>(applyMinimumFilter(originalImage));
        else if (argv[1] == string("--max")) editedImage = CImg<int>(applyMaximumFilter(originalImage));

        else if (argv[1] == string("--mse")) analysisResult = getMeanSquareError(originalImage, originalImage);       //paraemters to change
        else if (argv[1] == string("--pmse")) analysisResult = getPeakMeanSquareError(originalImage, originalImage);
        else if (argv[1] == string("--snr")) analysisResult = getSignalToNoiseRatio(originalImage, originalImage);
        else if (argv[1] == string("--psnr")) analysisResult = getPeakSignalToNoiseRatio(originalImage, originalImage);
        else if (argv[1] == string("--md")) analysisResult = getMaximumDifference(originalImage, originalImage);

        else cout << "No maching command. \nType --help to view the list of the available commands.";
    }

    if(editedImage != CImg<int>(1,1,1,3,0)) {
        //editedImage.save(argv[argc-1]);
        editedImage.save("edited.bmp");
        originalImage.append(editedImage, 'x').display("edited.bmp");}

    if(analysisResult != -1) {
        cout << "Analysis result is: " << analysisResult << endl;}

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
    "   --shrik src dest\n"
    "      outputs image in src shrinked by a factor of 2 to dest\n"
    "\n"
    "   --enlarge src dest\n"
    "      outputs image in src enlarged by a factor of 2 to dest\n"  //add bipolar interpolation
    "\n"
    "   --adaptive src dest\n"
    "      outputs image in src with adaptive filter applied to dest\n"
    "\n"
    "   --min src dest\n"
    "      outputs image in src with minimum filter applied to dest\n"
    "\n"
    "   --max src dest\n"
    "      outputs image in src with maximum filter applied to dest\n"
    "\n"
    "   --mse src1 src2\n"
    "      displays mean square error between images in src1 and src2\n"
    "\n"
    "   --pmse src1 src2\n"
    "      displays peak mean square error between images in src1 and src2\n"
    "\n"
    "   --snr src1 src2\n"
    "      displays signal to noise ratio between images in src1 and src2\n"
    "\n"
    "   --psnr src1 src2\n"
    "      displays peak signal to noise ratio between images in src1 and src2\n"
    "\n"
    "   --md src1 src2\n"
    "      displays maximum difference between images in src1 and src2\n";
}





