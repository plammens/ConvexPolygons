#include "../include/ConvexPolygon.h"
#include "../include/utils.h"

ConvexPolygon::ConvexPolygon(Points P) {
    min(P, Point::yComp);
}
