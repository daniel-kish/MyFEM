#ifndef AREA_H
#define AREA_H
#include <MyFEM.h>
#include <cmath>

// linear 1D area representation
class MyFEM::Area
{
    double a;
    double b;
public:
    Area(double x, double y) : a{x}, b{y}
    {}
    double origin() const {
        return a;
    }
    double end() const {
        return b;
    }
    double length() const {
        return fabs(b-a);
    }
};

#endif // AREA_H
