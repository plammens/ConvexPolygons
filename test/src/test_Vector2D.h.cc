#include <doctest.h>
#include <cmath>
#include "class/Vector2D.h"


TEST_SUITE("Vector2D") {

    TEST_CASE("Vector2D norm") {
        Vector2D vec = {-1, 2};

        CHECK(vec.sqrNorm() == 5);
        CHECK(vec.norm() == std::sqrt(5));
    }

    TEST_CASE("Vector2D.isNull()") {
        CHECK(Vector2D{0, 0}.isNull());
        CHECK(not Vector2D{1e-12, 1e-12}.isNull());
        CHECK(Vector2D{1e-13, 1e-13}.isNull());
    }


    TEST_CASE("Vector2D arithmetic") {
        CHECK(Vector2D{-1, 3.14} + Vector2D{2, 3} == Vector2D{1, 6.14});
        CHECK(-1.5*Vector2D{-1, -3} == Vector2D{1.5, 4.5});
        CHECK(Vector2D{1, 1}/2 == Vector2D{0.5, 0.5});
    }


    TEST_CASE("Vector2D cross prod") {
        CHECK(crossProd({1, 1}, {2, 2}) == 0);
        CHECK(crossProd({1, 0}, {0, 1}) == 1);
        CHECK(crossProd({0, 1}, {1, 0}) == -1);
    }

}
