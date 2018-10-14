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

    CImg<int> editedImage(1,1,1,3,0); //x, y, z, rgb channels, rgb vals

    if (argc < 2 || argc > 5) {cout << "Wrong number of parameters.\nType --help to view the list of the available commands." << endl; exit(0);
    } else {
        if (argv[1] == string("--help")) displayHelp();

        else if (argv[1] == string("--brightness")) editedImage = CImg<int>(changeBrightness(CImg<int>(argv[3]), argv[2]));
        else if (argv[1] == string("--contrast")) editedImage = CImg<int>(changeContrast(CImg<int>(argv[3]), argv[2]));
        else if (argv[1] == string("--negative")) editedImage = CImg<int>(changeToNegative(CImg<int>(argv[3])));

        else if (argv[1] == string("--hflip")) editedImage = CImg<int>(doHorizontalFlip(CImg<int>(argv[3])));
        else if (argv[1] == string("--vflip")) editedImage = CImg<int>(doVerticalFlip(CImg<int>(argv[3])));
        else if (argv[1] == string("--dflip")) editedImage = CImg<int>(doDiagonalFlip(CImg<int>(argv[3])));
        else if (argv[1] == string("--shrink")) editedImage = CImg<int>(shrinkBy(CImg<int>(argv[3]), argv[2]));
        else if (argv[1] == string("--enlarge")) editedImage = CImg<int>(enlargeBy(CImg<int>(argv[3]), argv[2]));

        else if (argv[1] == string("--adaptive")) editedImage = CImg<int>(applyAdaptiveMedianFilter(CImg<int>(argv[3]), argv[2]));
        else if (argv[1] == string("--min")) editedImage = CImg<int>(applyMinimumFilter(CImg<int>(argv[3]), argv[2]));
        else if (argv[1] == string("--max")) editedImage = CImg<int>(applyMaximumFilter(CImg<int>(argv[3]), argv[2]));

        else if (argv[1] == string("--mse") || argv[1] == string("--pmse") || argv[1] == string("--snr") || argv[1] == string("--psnr") || argv[1] == string("--md"))
            doAnalysis(CImg<int>(argv[2]), CImg<int>(argv[3]), CImg<int>(argv[4]), argv[1]);

        else cout << "No maching command. \nType --help to view the list of the available commands.";
    }

    if(editedImage != CImg<int>(1,1,1,3,0)) {
        //CImg<int>(argv[3]).save("../out/original.bmp");
        editedImage.save(argv[argc-1]);
        CImg<int>(argv[3]).append(editedImage, 'x').display("COMPARATION");
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





