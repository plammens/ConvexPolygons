/// @file
/// RGB representation of colors.

#ifndef CONVEXPOLYGONS_RGBCOLOR_H
#define CONVEXPOLYGONS_RGBCOLOR_H

#include <initializer_list>  // for init list assignment


/**
 * RGB representation of colors.
 */
class RGBColor {
public:
    /**
     * Explicit constructor from red, green, and blue values.
     * @param r,g,b  red, green and blue values
     *
     * @pre  all values are in the interval \f$ [0, 1] \f$
     * @throws error::ValueError if any of the arguments is not in \f$ [0, 1] \f$
     */
    explicit
    RGBColor(double r = 0, double g = 0, double b = 0);

    /**
     * Assigns the color values in initList to the corresponding fields.
     * Assigns to `r`, `g`, `b`, in that order.
     * @param initList  initializer list with 3 doubles
     * @pre  initList has exactly 3 elements
     * @throws error::ValueError if initList.size() != 3
     */
    RGBColor &operator=(const std::initializer_list<double> &initList);


    //! @name Getters
    //! Getters for each of the color values.
    ///@{
    double R() const { return r; }
    double G() const { return g; }
    double B() const { return b; }
    ///@}


    //! @name Setters
    //! Setters for each of the color values
    ///@{
    void setR(double red);
    void setG(double green);
    void setB(double blue);
    ///@}


private:
    double r, g, b;

    static
    void checkRange(double val);
};



//-------- ASSOCIATED NONMEMBER FUNCTIONS --------//



//! @name Equality operators
//! Numerical component-wise equality test.
///@{

bool operator==(const RGBColor &lhs, const RGBColor &rhs);
bool operator!=(const RGBColor &lhs, const RGBColor &rhs);

///@}



#endif //CONVEXPOLYGONS_RGBCOLOR_H
