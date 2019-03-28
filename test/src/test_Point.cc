#include <doctest.h>
#include <sstream>
#include "class/Point.h"
#include "geom.h"


TEST_SUITE("Point") {

    TEST_CASE("arithmetic") {
        CHECK(Point{1, 2} - Point{0, 0} == Vector2D{1, 2});
        CHECK(Point{0, 0} + Vector2D{3.14, -3.14} == Point{3.14, -3.14});
    }


    TEST_CASE("equality") {
        REQUIRE(Point{0, 0} == Point{0, 0});
        CHECK(Point{0, 0} == Point{-1e-13, 1e-13});
    }


    TEST_CASE("distance") {
        CHECK(distance({0, 0}, {0, 3}) == 3);
        CHECK(distance({0, 0}, {-3, 4}) == 5);
        CHECK(distance({0, 0}, {0, 0}) == 0);
    }


    TEST_CASE("comparisons") {
        SUBCASE("yCoord") {
            CHECK(PointComp::yCoord({0, 0}, {0, 1}));
            CHECK(not PointComp::yCoord({0, 1}, {0, 0}));
            CHECK(PointComp::yCoord({0, 0}, {1, 0}));
            CHECK(not PointComp::yCoord({0, 0}, {0, 0}));
        }

        SUBCASE("xAngle") {
            SUBCASE("ascending") {
                PointComp::xAngle comp({0, 0}, false);

                CHECK(not comp({-1, 0}, {1, 0}));
                CHECK(not comp({-1, 0}, {0, 1}));
                CHECK(comp({-1, 0}, {-2, 0}));
                CHECK(not comp({-1, 0}, {1, 0}));
                CHECK(not comp({0, 0}, {0, 0}));
            }
            SUBCASE("ascending") {
                PointComp::xAngle comp({0, 0}, true);

                CHECK(comp({-1, 0}, {1, 0}));
                CHECK(comp({-1, 0}, {0, 1}));
                CHECK(comp({-1, 0}, {-2, 0}));
                CHECK(comp({-1, 0}, {1, 0}));
                CHECK(not comp({0, 0}, {0, 0}));
            }
        }
    }


    TEST_CASE("turns") {
        SUBCASE("clockwise") {
            CHECK(isClockwiseTurn({0, 0}, {0, 1}, {1, 1}));
            CHECK(isClockwiseTurn({0, 1}, {1, 1}, {1, 0}));
            CHECK(not isClockwiseTurn({0, 0}, {0, 1}, {0, 2}));
            CHECK(not isClockwiseTurn({0, 0}, {0, 1}, {-1, 1}));
        }
        SUBCASE("counterclockwise") {
            CHECK(not isCounterClockwiseTurn({0, 0}, {0, 1}, {1, 1}));
            CHECK(not isCounterClockwiseTurn({0, 1}, {1, 1}, {1, 0}));
            CHECK(not isCounterClockwiseTurn({0, 0}, {0, 1}, {0, 2}));
            CHECK(isCounterClockwiseTurn({0, 0}, {0, 1}, {-1, 1}));
        }
    }


    TEST_CASE("barycenter") {
        Points points;

        CHECK(barycenter(points = {{0, 0}, {1, 1}}) == Point{0.5, 0.5});
        CHECK(barycenter(points = {{0, 0}, {0, 1}, {1, 1}, {1, 0}}) == Point{0.5, 0.5});
        CHECK(barycenter(points = {{0, 0}, {-1, 0}}) == Point{-0.5, 0});
    }


    TEST_CASE("IO") {
        Point P{0, 2.0005};

        SUBCASE("read") {
            std::istringstream iss("  0.123 \n -4.56");
            iss >> P;
            CHECK(P == Point{0.123, -4.56});
        }
        SUBCASE("write") {
            std::ostringstream oss;
            oss << P;
            CHECK(oss.str() == "0.000 2.001");
        }
    }

}
