// Interface for RGB colors

#ifndef CONVEXPOLYGONS_RGBCOLOR_H
#define CONVEXPOLYGONS_RGBCOLOR_H

#include <initializer_list>
#include <cassert>

using namespace std;


class RGBColor {
private:
    double r, g, b;

    static
    void checkRange(double val);

public:
    RGBColor(double r = 0, double g = 0, double b = 0);
    RGBColor &operator=(const initializer_list<double> &initList);

    double R() const { return r; }
    double G() const { return g; }
    double B() const { return b; }
    void setR(double r);
    void setG(double g);
    void setB(double b);
};


bool operator==(const RGBColor &lhs, const RGBColor &rhs);
bool operator!=(const RGBColor &lhs, const RGBColor &rhs);


#endif //CONVEXPOLYGONS_RGBCOLOR_H
