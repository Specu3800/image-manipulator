#include <iostream>
#include "../../lib/CImg.templ"
#include "t0-other.h"

using namespace std;
using namespace cimg_library;

void applyBilinearInterpolation(CImg<int> &edited){
    for (int x = 0; x < edited.width(); x++) {
        for (int y = 0; y < edited.height(); y++) {

            if(x-1 < 0 || x + 1 >= edited.width() || y-1 < 0 || y + 1 >= edited.height()) continue; //not for borders
            if(edited(x, y, 0, 0) != 0 || edited(x, y, 0, 1) != 0 || edited(x, y, 0, 2) != 0) continue; //apply only on black pixels

            for (int c = 0; c < 3; c++) {
                if  (edited(x-1, y-1, 0, 0) != 0 && edited(x-1, y-1, 0, 1) != 0 && edited(x-1, y-1, 0, 2) != 0) {
                    if (edited(x + 1, y - 1, 0, 0) != 0 && edited(x + 1, y - 1, 0, 1) != 0 && edited(x + 1, y - 1, 0, 2) != 0)
                        edited(x, y - 1, 0, c) = 0.5 * edited(x - 1, y - 1, 0, c) + 0.5 * edited(x + 1, y - 1, 0, c);
                    if (edited(x - 1, y + 1, 0, 0) != 0 && edited(x - 1, y + 1, 0, 1) != 0 && edited(x - 1, y + 1, 0, 2) != 0)
                        edited(x - 1, y, 0, c) = 0.5 * edited(x - 1, y + 1, 0, c) + 0.5 * edited(x - 1, y - 1, 0, c);
                }
                if  (edited(x+1, y+1, 0, 0) != 0 && edited(x+1, y+1, 0, 1) != 0 && edited(x+1, y+1, 0, 2) != 0) {
                    if (edited(x + 1, y - 1, 0, 0) != 0 && edited(x + 1, y - 1, 0, 1) != 0 && edited(x + 1, y - 1, 0, 2) != 0)
                        edited(x+1, y, 0, c) = 0.5*edited(x+1, y-1, 0, c) + 0.5*edited(x+1, y+1, 0, c);
                    if (edited(x - 1, y + 1, 0, 0) != 0 && edited(x - 1, y + 1, 0, 1) != 0 && edited(x - 1, y + 1, 0, 2) != 0)
                        edited(x, y+1, 0, c) = 0.5*edited(x-1, y+1, 0, c) + 0.5*edited(x+1, y+1, 0, c);
                }
                edited(x, y, 0, c) = 0.5*edited(x, y-1, 0, c) + 0.5*edited(x, y+1, 0, c);
            }
        }
    }
}


