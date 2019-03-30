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


    TEST_CASE("io") {
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
