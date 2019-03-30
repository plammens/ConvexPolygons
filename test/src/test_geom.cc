#include <doctest.h>
#include <vector>
#include "geom.h"


typedef std::vector<Point> Points;



TEST_SUITE("geom") {

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

    TEST_CASE("comparisons") {
        SUBCASE("xCoord") {
            CHECK(PointComp::xCoord({0, 0}, {1, 0}));
            CHECK(not PointComp::xCoord({1, 0}, {0, 0}));
            CHECK(PointComp::xCoord({0, 0}, {0, 1}));
            CHECK(not PointComp::xCoord({0, 0}, {0, 0}));
        }

        SUBCASE("yAngle") {
            PointComp::yAngle comp({0, 0});

            CHECK(comp({0, 1}, {0, -1}));
            CHECK(not comp({0, -1}, {0, 1}));
            CHECK(comp({0, 1}, {0, 2}));
            CHECK(comp({0, 1}, {1, -0.5}));
            CHECK(not comp({0, 0}, {0, 0}));
            CHECK(comp({0, 1}, {1, 0}));
            CHECK(comp({1, -0.5}, {1, -1}));
        }
    }


    TEST_CASE("barycenter") {
        Points points;

        CHECK(barycenter(points = {{0, 0}, {1, 1}}) == Point{0.5, 0.5});
        CHECK(barycenter(points = {{0, 0}, {0, 1}, {1, 1}, {1, 0}}) == Point{0.5, 0.5});
        CHECK(barycenter(points = {{0, 0}, {-1, 0}}) == Point{-0.5, 0});
    }

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
