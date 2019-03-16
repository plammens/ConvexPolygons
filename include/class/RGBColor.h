#ifndef CONVEXPOLYGONSS_RGBCOLOR_H
#define CONVEXPOLYGONSS_RGBCOLOR_H

#include <initializer_list>
#include <cassert>

using namespace std;


class RGBColor {
private:
    double r, g, b;

    inline static
    bool checkRange(double val);

    inline static
    void checkRange(double r, double g, double b);

public:
    RGBColor(double r = 0, double g = 0, double b = 0);
    RGBColor &operator=(const initializer_list<double> &initList);
};


#endif //CONVEXPOLYGONSS_RGBCOLOR_H
