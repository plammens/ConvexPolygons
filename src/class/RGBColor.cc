#include "class/RGBColor.h"

#include "errors.h"
#include "details/numeric.h"


//-------- MEMBER FUNCTIONS --------//

RGBColor::RGBColor(double r, double g, double b) {
    setR(r);
    setG(g);
    setB(b);
}

RGBColor &RGBColor::operator=(const std::initializer_list<double> &initList) {
    if (initList.size() != 3) throw ValueError("color assignment needs exactly 3 arguments");
    auto it = initList.begin();
    setR(it[0]);
    setG(it[1]);
    setB(it[2]);
    return *this;
}


//---- Setters ----//

void RGBColor::setR(double red) {
    checkRange(red);
    r = red;
}

void RGBColor::setG(double green) {
    checkRange(green);
    this->g = green;
}

void RGBColor::setB(double blue) {
    checkRange(blue);
    this->b = blue;
}




//-------- STATIC FUNCTIONS --------//

void RGBColor::checkRange(double val) {
    if (val < 0 or val > 1) throw ValueError("color values should be in [0, 1]");
}



//-------- ASSOCIATED NONMEMBER FUNCTIONS --------//

//---- Equality operators ----//

bool operator==(const RGBColor &lhs, const RGBColor &rhs) {
    return numeric::equal(lhs.R(), rhs.R()) and
           numeric::equal(lhs.G(), rhs.G()) and
           numeric::equal(lhs.B(), rhs.B());
}


bool operator!=(const RGBColor &lhs, const RGBColor &rhs) {
    return not(rhs == lhs);
}
