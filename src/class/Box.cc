#include "class/Box.h"


Box::Box(const Point &SW, const Point &NW, const Point &NE, const Point &SE)
        : _SW(SW), _NW(NW), _NE(NE), _SE(SE) {}
