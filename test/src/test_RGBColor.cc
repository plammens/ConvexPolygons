#include <doctest.h>
#include "class/RGBColor.h"
#include "errors.h"


TEST_SUITE("RGBColor") {

    TEST_CASE("RGB validation") {
        RGBColor col;
        CHECK(col == RGBColor{0, 0, 0});

        CHECK_THROWS_AS(col.operator=({-1, 0, 0}), ValueError);
        CHECK_THROWS_AS(col.operator=({0, 0}), ValueError);
        CHECK_THROWS_AS(col.operator=({-1, 0, 0}), ValueError);

        col = {0.5, 0.2, 1};
        CHECK(col == RGBColor{0.5, 0.2, 1});
    }

};
