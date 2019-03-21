//
// Created by paolo on 3/15/19.
//

#include <class/RGBColor.h>
#include <boost/format.hpp>

#include "class/RGBColor.h"
#include "errors.h"
#include "utils.h"


RGBColor::RGBColor(double r, double g, double b) {
    checkRange(r, g, b);
    this->r = r;
    this->g = g;
    this->b = b;
}

RGBColor &RGBColor::operator=(const initializer_list<double> &initList) {
    assert(initList.size() == 3);  // TODO: remove assert
    auto it = initList.begin();
    checkRange(it[0], it[1], it[2]);
    r = it[0]; g = it[1]; b = it[2];
    return *this;
}

bool RGBColor::checkRange(double val) {
    return (val >= 0 and val <= 1);
}

void RGBColor::checkRange(double r, double g, double b) {
    if (not(checkRange(r) and checkRange(b) and checkRange(g)))
        throw ValueError((boost::format("{%.3f, %.3f, %.3f} is not a color") % r % g % b).str());
}
