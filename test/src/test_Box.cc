#include <doctest.h>
#include "class/Box.h"


TEST_SUITE("Box") {

    TEST_CASE ("bbox operations") {
        SUBCASE("bottomLeft") {
            CHECK(bottomLeft({0, 0}, {1, 1}) == Point{0, 0});
            CHECK(bottomLeft({0, 1}, {1, 0}) == Point{0, 0});
            CHECK(bottomLeft({0, 1}, {0, 2}) == Point{0, 1});
            CHECK(bottomLeft({1, 0}, {0, 1}) == Point{0, 0});
        }
        SUBCASE ("upperRight") {
            CHECK(upperRight({0, 0}, {1, 1}) == Point{1, 1});
            CHECK(upperRight({0, 1}, {1, 0}) == Point{1, 1});
            CHECK(upperRight({0, 1}, {0, 2}) == Point{0, 2});
            CHECK(upperRight({1, 0}, {0, 1}) == Point{1, 1});
        }
    }


    TEST_CASE("constructor") {
        SUBCASE("normal") {
            Box box({0, 0}, {1, 1});
            CHECK(box.SW() == Point{0, 0});
            CHECK(box.NE() == Point{1, 1});
            CHECK(box.SE() == Point{1, 0});
            CHECK(box.NW() == Point{0, 1});
        }
        SUBCASE("reversed") {
            Box box({1, 1}, {0, 0});
            CHECK(box.SW() == Point{0, 0});
            CHECK(box.NE() == Point{1, 1});
            CHECK(box.SE() == Point{1, 0});
            CHECK(box.NW() == Point{0, 1});
        }
    }

}
