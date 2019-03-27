#include <doctest.h>
#include "geom.h"


TEST_SUITE("geom") {

    TEST_CASE("intersect") {
        Segment s1 = {{0, 0}, {1, 1}},
                s2 = {{0, 1}, {1, 0}};

        IntersectResult solve = intersect(s1, s2);

        REQUIRE(solve.success);
        CHECK(solve.point == Point{0.5, 0.5});

        SUBCASE("degenerate") {
            Segment s3 = {{0, 0}, {1, 0}},
                    s4 = {{0, -1e-13}, {1, 1e-13}};

            IntersectResult solve = intersect(s3, s4);
            REQUIRE(solve.success);
            CHECK(solve.point == Point{0.5, 0});
        }
    }

    TEST_CASE("isInSegment") {
        Segment seg = {{0, 0}, {1, 0}};

        CHECK(isInSegment({0, 0}, seg));
        CHECK(isInSegment({1, 0}, seg));
        CHECK(not isInSegment({1 + 1e-12}, seg));
        CHECK(isInSegment({1 + 1e-13}, seg));
    }

}
