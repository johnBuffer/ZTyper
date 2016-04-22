#include <cmath>

double dist2(double x1, double y1, double x2, double y2)
{
    double vx = x1-x2;
    double vy = y1-y2;

    return vx*vx+vy*vy;
}

double dist(double x1, double y1, double x2, double y2)
{
    return sqrt(dist2(x1, y1, x2, y2));
}
