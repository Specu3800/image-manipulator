#ifndef OTHER
#define OTHER

#include "../../lib/CImg.templ"

using namespace std;
using namespace cimg_library;

CImg<int>& applyBilinearInterpolation(CImg<int> &image);

void displayProgress(int x, int max);

bool fileExists(char* name);

int normalized(int value);

void displayHelp();
void displayVersion();

#endif //OTHER


