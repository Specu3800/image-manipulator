#include <iostream>
#include "../../lib/CImg.templ"
#include "t0-other.h"

using namespace std;
using namespace cimg_library;

//
//void applyBilinearInterpolation(CImg<int> &edited){
//    for (int x = 0; x < edited.width(); x++) {
//        for (int y = 0; y < edited.height(); y++) {
//
//            if(x-1 < 0 || x + 1 >= edited.width() || y-1 < 0 || y + 1 >= edited.height()) continue; //not for borders
//            if(edited(x, y, 0, 0) != 0 || edited(x, y, 0, 1) != 0 || edited(x, y, 0, 2) != 0) continue; //apply only on black pixels
//
//            for (int c = 0; c < 3; c++) {
//                if  (edited(x-1, y-1, 0, 0) != 0 && edited(x-1, y-1, 0, 1) != 0 && edited(x-1, y-1, 0, 2) != 0) {
//                    if (edited(x + 1, y - 1, 0, 0) != 0 && edited(x + 1, y - 1, 0, 1) != 0 && edited(x + 1, y - 1, 0, 2) != 0)
//                        edited(x, y - 1, 0, c) = 0.5 * edited(x - 1, y - 1, 0, c) + 0.5 * edited(x + 1, y - 1, 0, c);
//                    if (edited(x - 1, y + 1, 0, 0) != 0 && edited(x - 1, y + 1, 0, 1) != 0 && edited(x - 1, y + 1, 0, 2) != 0)
//                        edited(x - 1, y, 0, c) = 0.5 * edited(x - 1, y + 1, 0, c) + 0.5 * edited(x - 1, y - 1, 0, c);
//                }
//                if  (edited(x+1, y+1, 0, 0) != 0 && edited(x+1, y+1, 0, 1) != 0 && edited(x+1, y+1, 0, 2) != 0) {
//                    if (edited(x + 1, y - 1, 0, 0) != 0 && edited(x + 1, y - 1, 0, 1) != 0 && edited(x + 1, y - 1, 0, 2) != 0)
//                        edited(x+1, y, 0, c) = 0.5*edited(x+1, y-1, 0, c) + 0.5*edited(x+1, y+1, 0, c);
//                    if (edited(x - 1, y + 1, 0, 0) != 0 && edited(x - 1, y + 1, 0, 1) != 0 && edited(x - 1, y + 1, 0, 2) != 0)
//                        edited(x, y+1, 0, c) = 0.5*edited(x-1, y+1, 0, c) + 0.5*edited(x+1, y+1, 0, c);
//                }
//                edited(x, y, 0, c) = 0.5*edited(x, y-1, 0, c) + 0.5*edited(x, y+1, 0, c);
//            }
//        }
//    }
//}



void interpole(CImg<int> &edited, int x, int y){

    //if(x-1 < 0 || x + 1 >= edited.width() || y-1 < 0 || y + 1 >= edited.height()) continue; //not for borders
    if(edited(x, y, 0, 0) != 0 || edited(x, y, 0, 1) != 0 || edited(x, y, 0, 2) != 0) return; //apply only on black pixels

    bool K1, K2, K3, K4;
    bool U1, U2, U3, U4;

    if (x - 1 >= 0 && y - 1 >= 0) K1 = (edited(x - 1, y - 1, 0, 0) != 0 && edited(x - 1, y - 1, 0, 1) != 0 && edited(x - 1, y - 1, 0, 2) != 0); else K1 = false;
    if (x + 1 < edited.width() && y - 1 >= 0) K2 = (edited(x + 1, y - 1, 0, 0) != 0 && edited(x + 1, y - 1, 0, 1) != 0 && edited(x + 1, y - 1, 0, 2) != 0); else K2 = false;
    if (x - 1 >= 0 && y + 1 > edited.height()) K3 = (edited(x - 1, y + 1, 0, 0) != 0 && edited(x - 1, y + 1, 0, 1) != 0 && edited(x - 1, y + 1, 0, 2) != 0); else K3 = false;
    if (x + 1 < edited.width() && y + 1 > edited.height()) K4 = (edited(x + 1, y + 1, 0, 0) != 0 && edited(x + 1, y + 1, 0, 1) != 0 && edited(x + 1, y + 1, 0, 2) != 0); else K4 = false;

    if (y - 1 >= 0) U1 = (edited(x, y - 1, 0, 0) != 0 && edited(x, y - 1, 0, 1) != 0 && edited(x, y - 1, 0, 2) != 0); else U1 = false;
    if (x + 1 < edited.width()) U2 = (edited(x + 1, y, 0, 0) != 0 && edited(x + 1, y, 0, 1) != 0 && edited(x + 1, y, 0, 2) != 0); else U2 = false;
    if (y + 1 < edited.height()) U3 = (edited(x, y + 1, 0, 0) != 0 && edited(x, y + 1, 0, 1) != 0 && edited(x, y + 1, 0, 2) != 0); else U3 = false;
    if (x - 1 >= 0) U4 = (edited(x - 1, y, 0, 0) != 0 && edited(x - 1, y, 0, 1) != 0 && edited(x - 1, y, 0, 2) != 0); else U4 = false;

//    if (x == 1 && y == 1){
//        if(K1) cout << "K1 true" << endl; else cout << "K1 false" << endl;
//        if(K2) cout << "K2 true" << endl; else cout << "K2 false" << endl;
//        if(K3) cout << "K3 true" << endl; else cout << "K3 false" << endl;
//        if(K4) cout << "K4 true" << endl; else cout << "K4 false" << endl;
//        if(U1) cout << "U1 true" << endl; else cout << "U1 false" << endl;
//        if(U2) cout << "U2 true" << endl; else cout << "U2 false" << endl;
//        if(U3) cout << "U3 true" << endl; else cout << "U3 false" << endl;
//        if(U4) cout << "U4 true" << endl; else cout << "U4 false" << endl;
//    }

    for (int c = 0; c < 3; c++) {
//                if (x == 1 && y == 0) cout << edited(x + 1, y, 0, c) << endl;

        if (K1 && K2 && K3 && K4) {
            edited(x, y, 0, c) = 0.25*(edited(x - 1, y - 1, 0, c) + edited(x + 1, y - 1, 0, c) + edited(x - 1, y + 1, 0, c) + edited(x + 1, y + 1, 0, c));
            continue;
        } else {
            if (U1 && U3) {
                edited(x, y, 0, c) = 0.5*(edited(x, y - 1, 0, c) + edited(x, y + 1, 0, c));
                continue;
            }
            else if (U2 && U4) {
                edited(x, y, 0, c) = 0.5*(edited(x - 1, y, 0, c) + edited(x + 1, y, 0, c));
                continue;
            }
        }
    }


}


void applyBilinearInterpolation(CImg<int> &edited){
    for (int x = 0; x < edited.width(); x++) {
        for (int y = 0; y < edited.height(); y++) {

            //if(x-1 < 0 || x + 1 >= edited.width() || y-1 < 0 || y + 1 >= edited.height()) continue; //not for borders
            if(edited(x, y, 0, 0) != 0 || edited(x, y, 0, 1) != 0 || edited(x, y, 0, 2) != 0) continue; //apply only on black pixels

            bool K1, K2, K3, K4;
            bool U1, U2, U3, U4;

            if (x - 1 >= 0 && y - 1 >= 0) K1 = (edited(x - 1, y - 1, 0, 0) != 0 && edited(x - 1, y - 1, 0, 1) != 0 && edited(x - 1, y - 1, 0, 2) != 0); else K1 = false;
            if (x + 1 < edited.width() && y - 1 >= 0) K2 = (edited(x + 1, y - 1, 0, 0) != 0 && edited(x + 1, y - 1, 0, 1) != 0 && edited(x + 1, y - 1, 0, 2) != 0); else K2 = false;
            if (x - 1 >= 0 && y + 1 > edited.height()) K3 = (edited(x - 1, y + 1, 0, 0) != 0 && edited(x - 1, y + 1, 0, 1) != 0 && edited(x - 1, y + 1, 0, 2) != 0); else K3 = false;
            if (x + 1 < edited.width() && y + 1 > edited.height()) K4 = (edited(x + 1, y + 1, 0, 0) != 0 && edited(x + 1, y + 1, 0, 1) != 0 && edited(x + 1, y + 1, 0, 2) != 0); else K4 = false;

            if (y - 1 >= 0) U1 = (edited(x, y - 1, 0, 0) != 0 && edited(x, y - 1, 0, 1) != 0 && edited(x, y - 1, 0, 2) != 0); else U1 = false;
            if (x + 1 < edited.width()) U2 = (edited(x + 1, y, 0, 0) != 0 && edited(x + 1, y, 0, 1) != 0 && edited(x + 1, y, 0, 2) != 0); else U2 = false;
            if (y + 1 < edited.height()) U3 = (edited(x, y + 1, 0, 0) != 0 && edited(x, y + 1, 0, 1) != 0 && edited(x, y + 1, 0, 2) != 0); else U3 = false;
            if (x - 1 >= 0) U4 = (edited(x - 1, y, 0, 0) != 0 && edited(x - 1, y, 0, 1) != 0 && edited(x - 1, y, 0, 2) != 0); else U4 = false;

            if (x == 1 && y == 1){
                if (x + 1 < edited.width()) interpole(edited, x+1, y);
                if(K1) cout << "K1 true" << endl; else cout << "K1 false" << endl;
                if(K2) cout << "K2 true" << endl; else cout << "K2 false" << endl;
                if(K3) cout << "K3 true" << endl; else cout << "K3 false" << endl;
                if(K4) cout << "K4 true" << endl; else cout << "K4 false" << endl;
                if(U1) cout << "U1 true" << endl; else cout << "U1 false" << endl;
                if(U2) cout << "U2 true" << endl; else cout << "U2 false" << endl;
                if(U3) cout << "U3 true" << endl; else cout << "U3 false" << endl;
                if(U4) cout << "U4 true" << endl; else cout << "U4 false" << endl;
            }

            for (int c = 0; c < 3; c++) {
//                if (x == 1 && y == 0) cout << edited(x + 1, y, 0, c) << endl;

                if (K1 && K2 && K3 && K4) {
                    edited(x, y, 0, c) = 0.25*(edited(x - 1, y - 1, 0, c) + edited(x + 1, y - 1, 0, c) + edited(x - 1, y + 1, 0, c) + edited(x + 1, y + 1, 0, c));
                } else {
                    if (U1 && U3) {
                        edited(x, y, 0, c) = 0.5*(edited(x, y - 1, 0, c) + edited(x, y + 1, 0, c));
                    }
                    else if (U2 && U4) {
                        edited(x, y, 0, c) = 0.5*(edited(x - 1, y, 0, c) + edited(x + 1, y, 0, c));
                    }
                }
            }


        }
    }
}




/*
 *             */


/*
 *
 * __x-1___x___x+1_
 *
 * | K1 | U1 | K2 |   y-1
 * ________________
 * | U4 | XX | U2 |   y
 * ________________
 * | K3 | U3 | K4 |   y+1
 *
 *
 * */


