#include "const.h"
#include <cmath>
#include "Highscore.h"

float getAngle(int x1, int y1, int x2, int y2);
void calcSlope(int x1, int y1, int x2, int y2, float *dx, float *dy);
int getDistance(int x1, int y1, int x2, int y2);
bool compareHighscore(Highscore a, Highscore b);
