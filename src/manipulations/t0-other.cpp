#include <iostream>
#include "../../lib/CImg.templ"
#include "t0-other.h"

using namespace std;
using namespace cimg_library;

void applyBilinearInterpolation(CImg<int> &edited){
    /*
     * __x-1___x___x+1_
     *
     * | K1 | U1 | K2 |   y-1
     * ________________
     * | U4 | XX | U2 |   y
     * ________________
     * | K3 | U3 | K4 |   y+1
     *
     * */
    for (int x = 0; x < edited.width(); x++) {
        for (int y = 0; y < edited.height(); y++) {

            //if(edited(x, y, 0, 0) != 0 || edited(x, y, 0, 1) != 0 || edited(x, y, 0, 2) != 0) continue; //apply only on black pixels //uncommented smooths the whole image

            bool K1, K2, K3, K4;
            bool U1, U2, U3, U4;

            if (x - 1 >= 0 && y - 1 >= 0) K1 = (edited(x - 1, y - 1, 0, 0) != 0 || edited(x - 1, y - 1, 0, 1) != 0 || edited(x - 1, y - 1, 0, 2) != 0); else K1 = false;
            if (x + 1 < edited.width() && y - 1 >= 0) K2 = (edited(x + 1, y - 1, 0, 0) != 0 || edited(x + 1, y - 1, 0, 1) != 0 || edited(x + 1, y - 1, 0, 2) != 0); else K2 = false;
            if (x - 1 >= 0 && y + 1 < edited.height()) K3 = (edited(x - 1, y + 1, 0, 0) != 0 || edited(x - 1, y + 1, 0, 1) != 0 || edited(x - 1, y + 1, 0, 2) != 0); else K3 = false;
            if (x + 1 < edited.width() && y + 1 < edited.height()) K4 = (edited(x + 1, y + 1, 0, 0) != 0 || edited(x + 1, y + 1, 0, 1) != 0 || edited(x + 1, y + 1, 0, 2) != 0); else K4 = false;

            if (y - 1 >= 0) U1 = (edited(x, y - 1, 0, 0) != 0 || edited(x, y - 1, 0, 1) != 0 || edited(x, y - 1, 0, 2) != 0); else U1 = false;
            if (x + 1 < edited.width()) U2 = (edited(x + 1, y, 0, 0) != 0 || edited(x + 1, y, 0, 1) != 0 || edited(x + 1, y, 0, 2) != 0); else U2 = false;
            if (y + 1 < edited.height()) U3 = (edited(x, y + 1, 0, 0) != 0 || edited(x, y + 1, 0, 1) != 0 || edited(x, y + 1, 0, 2) != 0); else U3 = false;
            if (x - 1 >= 0) U4 = (edited(x - 1, y, 0, 0) != 0 || edited(x - 1, y, 0, 1) != 0 || edited(x - 1, y, 0, 2) != 0); else U4 = false;

            for (int c = 0; c < 3; c++) {
                if (K1 && K2 && K3 && K4)
                    edited(x, y, 0, c) = 0.25*(edited(x - 1, y - 1, 0, c) + edited(x + 1, y - 1, 0, c) + edited(x - 1, y + 1, 0, c) + edited(x + 1, y + 1, 0, c));
                else if (U1 && U3)
                    edited(x, y, 0, c) = 0.5*(edited(x, y - 1, 0, c) + edited(x, y + 1, 0, c));
                else if (U2 && U4)
                    edited(x, y, 0, c) = 0.5*(edited(x - 1, y, 0, c) + edited(x + 1, y, 0, c));
            }
        }
    }
}

void displayProgress(int x, int max){
    float progress = ((x*100)/max) * 0.01;
    int barWidth = 70;

    cout << "[";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) cout << "=";
        else if (i == pos) cout << ">";
        else cout << " ";
    }
    cout << "] " << int(progress * 100.0) << " %\r";
    cout.flush();
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
         "   --median dep src dest\n"
         "      outputs image in src with median filter with depth of dep \n"
         "      applied to dest\n"
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





