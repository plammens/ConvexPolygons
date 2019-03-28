/** @file
 * RGB representation of colors.
*/

#ifndef CONVEXPOLYGONS_RGBCOLOR_H
#define CONVEXPOLYGONS_RGBCOLOR_H

#include <initializer_list>  // for init list assignment


class RGBColor {
private:
    double r, g, b;

    static
    void checkRange(double val);

public:

    /**
     * Explicit constructor from red, green, and blue values.
     * @param r  red value in [0, 1]
     * @param g  green value in [0, 1]
     * @param b  blue value in [0, 1]
     */
    explicit
    RGBColor(double r = 0, double g = 0, double b = 0);

    RGBColor &operator=(const std::initializer_list<double> &initList);

    double R() const { return r; }
    double G() const { return g; }
    double B() const { return b; }
    void setR(double r);
    void setG(double green);
    void setB(double blue);
};


bool operator==(const RGBColor &lhs, const RGBColor &rhs);
bool operator!=(const RGBColor &lhs, const RGBColor &rhs);


#endif //CONVEXPOLYGONS_RGBCOLOR_H
