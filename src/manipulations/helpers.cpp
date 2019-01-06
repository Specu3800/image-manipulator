#include <iostream>
#include <fstream>
#include "../../lib/CImg.templ"
#include "helpers.h"

using namespace std;
using namespace cimg_library;

CImg<int>& applyBilinearInterpolation(CImg<int> &original){
    CImg<int>* edited = new CImg<int>(original);
    for (int x = 0; x < (*edited).width(); x++) {
        displayProgress(x, (*edited).width()-1);
        for (int y = 0; y < (*edited).height(); y++) {
            //if((*edited)(x, y, 0, 0) != 0 || (*edited)(x, y, 0, 1) != 0 || (*edited)(x, y, 0, 2) != 0) continue; //apply only on black pixels //uncommented smooths the whole image

            bool K1, K2, K3, K4;
            bool U1, U2, U3, U4;

            if (x - 1 >= 0 && y - 1 >= 0) K1 = ((*edited)(x - 1, y - 1, 0, 0) != 0 || (*edited)(x - 1, y - 1, 0, 1) != 0 || (*edited)(x - 1, y - 1, 0, 2) != 0); else K1 = false;
            if (x + 1 < (*edited).width() && y - 1 >= 0) K2 = ((*edited)(x + 1, y - 1, 0, 0) != 0 || (*edited)(x + 1, y - 1, 0, 1) != 0 || (*edited)(x + 1, y - 1, 0, 2) != 0); else K2 = false;
            if (x - 1 >= 0 && y + 1 < (*edited).height()) K3 = ((*edited)(x - 1, y + 1, 0, 0) != 0 || (*edited)(x - 1, y + 1, 0, 1) != 0 || (*edited)(x - 1, y + 1, 0, 2) != 0); else K3 = false;
            if (x + 1 < (*edited).width() && y + 1 < (*edited).height()) K4 = ((*edited)(x + 1, y + 1, 0, 0) != 0 || (*edited)(x + 1, y + 1, 0, 1) != 0 || (*edited)(x + 1, y + 1, 0, 2) != 0); else K4 = false;

            if (y - 1 >= 0) U1 = ((*edited)(x, y - 1, 0, 0) != 0 || (*edited)(x, y - 1, 0, 1) != 0 || (*edited)(x, y - 1, 0, 2) != 0); else U1 = false;
            if (x + 1 < (*edited).width()) U2 = ((*edited)(x + 1, y, 0, 0) != 0 || (*edited)(x + 1, y, 0, 1) != 0 || (*edited)(x + 1, y, 0, 2) != 0); else U2 = false;
            if (y + 1 < (*edited).height()) U3 = ((*edited)(x, y + 1, 0, 0) != 0 || (*edited)(x, y + 1, 0, 1) != 0 || (*edited)(x, y + 1, 0, 2) != 0); else U3 = false;
            if (x - 1 >= 0) U4 = ((*edited)(x - 1, y, 0, 0) != 0 || (*edited)(x - 1, y, 0, 1) != 0 || (*edited)(x - 1, y, 0, 2) != 0); else U4 = false;

            for (int c = 0; c < (*edited).spectrum(); c++) {
                if (U1 && U2 && U3 && U4)
                    (*edited)(x, y, c) = 0.25*((*edited)(x, y - 1, 0, c) + (*edited)(x, y + 1, 0, c) + (*edited)(x - 1, y, 0, c) + (*edited)(x + 1, y, 0, c));
                else if (K1 && K2 && K3 && K4)
                    (*edited)(x, y, c) = 0.25*((*edited)(x - 1, y - 1, 0, c) + (*edited)(x + 1, y - 1, 0, c) + (*edited)(x - 1, y + 1, 0, c) + (*edited)(x + 1, y + 1, 0, c));
                else if (U1 && U3)
                    (*edited)(x, y, c) = 0.5*((*edited)(x, y - 1, 0, c) + (*edited)(x, y + 1, 0, c));
                else if (U2 && U4)
                    (*edited)(x, y, c) = 0.5*((*edited)(x - 1, y, 0, c) + (*edited)(x + 1, y, 0, c));
            }
        }
    }
    return *edited;
    /*
     *         x-1   x   x+1
     *
     *       | K1 | U1 | K2 |   y-1
     *       ________________
     *       | U4 | XX | U2 |   y
     *       ________________
     *       | K3 | U3 | K4 |   y+1
     *
     * */
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

bool fileExists(char* name){
    ifstream fin(name);
    if (!fin.good()) {
        cout << name << " does not exist, try again." << endl;
        exit(0);
    }
    return true;
}

int normalize(int value){
    if (value < 0) return 0;
    else if (value > 255) return 255;
    else return value;
}

void displayHelp() {
    cout <<
        (char)27 << "[1m" << "USAGE:\n" << (char)27 << "[0m" <<
        "    image-manipulator --command [parameter] [source_file] [destination_file]\n"
        "                                OR\n"
        "    image-manipulator --command [source_file] [destination_file]\n"
        "                                OR\n"
        "    image-manipulator --command [source1_file] [source2_file] [destination_file]\n"
        "                                OR\n"
        "    image-manipulator --command [source1_file] [source2_file]\n"
        "                                OR\n"
        "    image-manipulator --command [source_file] \n"
        "\n"
        "\n"
        << (char)27 << "[1m" << "COMMANDS:" << (char)27 << "[0m\n"
        "\n"
        << (char)27 << "[1m" << "  BASIC:" << (char)27 << "[0m----------------------------------------------------------------------\n"
        "    --brightness parameter src dest\n"
        "        modifies brightess by parameter\n"
        "        (0 < parameter < 255) - increase brightness\n"
        "        (-255 < parameter < 0) - decrease brightness\n"
        "\n"
        "    --contrast parameter src dest \n"
        "        modifies contrast by parameter\n"
        "        (0 < parameter < 1) - decrease contrast\n"
        "        (1 < parameter <= infinity) - increase contrast\n"
        "\n"
        "    --negative src dest\n"
        "        outputs negative image\n"
        "\n"
        << (char)27 << "[1m" << "  GEOMETRIC:" << (char)27 << "[0m------------------------------------------------------------------\n"
        "    --hflip \n"
        "        outputs horizontally fliped image\n"
        "\n"
        "    --vflip src dest\n"
        "        outputs vertically fliped image \n"
        "\n"
        "    --dflip src dest\n"
        "        outputs diagonally fliped image\n"
        "\n"
        "    --shrik parameter src dest\n"
        "        outputs image shrinked by a parameter\n"
        "\n"
        "    --enlarge parameter dest\n"
        "        outputs image enlarged by a parameter\n"
        "\n"
        << (char)27 << "[1m" << "  NOISE-REMOVAL OPERATIONS:" << (char)27 << "[0m----------------------------------------------------\n"
        "    --median parameter src dest\n"
        "        applies median filter with depth of parameter \n"
        "        (1 < parameter < infinity)\n"
        "        max depth recommended: 3\n"
        "\n"
        "    --adaptive parameter src dest\n"
        "        applies adaptive median filter with depth of parameter \n"
        "        (1 < parameter < infinity)\n"
        "        max depth recommended: 5\n"
        "\n"
        "    --min parameter src dest\n"
        "        applies minimum filter with depth of parameter \n"
        "        (1 < parameter < infinity)\n"
        "        max depth recommended: 3\n"
        "\n"
        "    --max parameter src dest\n"
        "        applies maximum filter with depth of parameter \n"
        "        (1 < parameter < infinity)\n"
        "        max depth recommended: 3\n"
        "\n"
        << (char)27 << "[1m" << "  ANALYSIS:" << (char)27 << "[0m-------------------------------------------------------------------\n"
        "    --mse src1 src2 \n"
        "        displays mean square error analysis between two images\n"
        "\n"
        "    --pmse src1 src2 \n"
        "        displays peak mean square error analysis between two images\n"
        "\n"
        "    --snr src1 src2 \n"
        "        displays signal to noise ratio analysis between two images\n"
        "\n"
        "    --psnr src1 src2 \n"
        "        displays peak signal to noise ratio analysis between two images\n"
        "\n"
        "    --md src1 src2 \n"
        "        displays maximum difference analysis between two images\n"
        "\n"
        << (char)27 << "[1m" << "  HISTOGRAM:" << (char)27 << "[0m------------------------------------------------------------------\n"
        "    --histogram [optional: parameter] src \n"
        "        displays histogram of an images on channel parameter (default 0)\n"
        "\n"
        << (char)27 << "[1m" << "  FILTERS:" << (char)27 << "[0m--------------------------------------------------------------------\n"
        "    --hexponent parameter1 parameter2 src dest \n"
        "        applies exponential final probability density function on an image\n"
        "        which should enhance image quality and flatter its histogram\n"
        "        parameters - denotes gmin and gmax respectively\n"
        "\n"
        "    --hexponentsep parameter1 parameter2 src dest \n"
        "        applies exponential final probability density function on an image separately for each channel\n"
        "        which should enhance image quality and flatter its histogram\n"
        "        parameters - denotes gmin and gmax respectively\n"
        "\n"
        "    --slaplace parameter src dest \n"
        "        applies linear laplacian filter on an image\n"
        "        which should expose borders \n"
        "        (parameter: 1 / 2 / 3) - usage of differen mask\n"
        "\n"
        "    --slaplaceopt src dest \n"
        "        applies more optimized implementation of linear laplacian filter on an image\n"
        "        which should expose borders \n"
        "\n"
        "    --orobertsii src dest \n"
        "        applies non-linear Roberts operator filter on an image\n"
        "        which should expose borders \n"
        "\n"
        << (char)27 << "[1m" << "  IMAGE-CHARACTERISTICS:" << (char)27 << "[0m------------------------------------------------------\n"
        "    --cmean src\n"
        "        displays Mean of an images\n"
        "\n"
        "    --cvariance src\n"
        "        displays Variance of an images\n"
        "\n"
        "    --cstdev src\n"
        "        displays Standard Deviation of an images\n"
        "\n"
        "    --cvarcoi src\n"
        "        displays Variation Coefficient I of an images\n"
        "\n"
        "    --cvarcoii src\n"
        "        displays Variation Coefficient II of an images\n"
        "\n"
        "    --casyco src\n"
        "        displays Asymmetry Coefficient of an images\n"
        "\n"
        "    --cflaco src\n"
        "        displays Flattening Coefficient of an images\n"
        "\n"
        "    --centropy src\n"
        "        displays Information Source Entropy of an images\n"
        "\n"
        << (char)27 << "[1m" << "  MORPHOLOGICAL OPERATIONS: "<< (char)27 << "[0m----------------------------------------------------\n"
        "    --union src1 src2 dest\n"
        "        applies union on two images\n"
        "\n"
        "    --intersection src1 src2 dest\n"
        "        applies intersection on two images\n"
        "\n"
        "    --defference src1 src2 dest\n"
        "        applies defference on two images\n"
        "\n"
        "    --oborder parameter src dest\n"
        "        applies preset Morphological Operation I (outputs outer border)\n"
        "        parameter: 1 - 10 - mask variant\n"
        "\n"
        "    --iborder parameter src dest\n"
        "        applies preset Morphological Operation II (outputs inner border)\n"
        "        parameter: 1 - 10 - mask variant\n"
        "\n"
        "    --ioborder parameter src dest\n"
        "        applies preset Morphological Operation III (outputs outer and inner borders combined)\n"
        "        parameter: 1 - 10 - mask variant\n"
        "\n"
        << (char)27 << "[1m" << "  SEGMENTATION:" << (char)27 << "[0m---------------------------------------------------------------\n"
        "    --segmentation x y threshold src dest\n"
        "        outputs region that grows from seed at (x, y) and accepts to the region\n"
        "        pixels within given threshold\n"
        "\n"
        << (char)27 << "[1m" << "  FOURIER TRANSFORM:" << (char)27 << "[0m----------------------------------------------------------\n"
        "    --dft src dest\n"
        "        performs DFT\n"
        "    --fft src dest\n"
        "        performs FFT\n"
        "\n"
        << (char)27 << "[1m" << "  FOURIER FILTERS:" << (char)27 << "[0m------------------------------------------------------------\n"
        "    --lowpass threshold src dest\n"
        "        applies low-pass filter\n"
        "    --highpass threshold src dest\n"
        "        applies highpass filter\n"
        "    --bandpass threshold width src dest\n"
        "        applies  bandpass filter\n"
        "    --bandcut threshold width src dest\n"
        "        applies  bandpass filter\n"
        "    --hpedge maskPath src dest\n"
        "        applies  highpass filter with edge direction\n"
        "    --pmod l k j src dest\n"
        "        applies phase modifying filter\n"
        "\n";
}

void displayVersion() {
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
        "#                               Version: 3.0                                  #\n"
        "#                                                                             #\n"
        "###############################################################################\n"
        "\n";
}





