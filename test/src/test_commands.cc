#include <doctest.h>
#include <sstream>
#include "commands.h"
#include "errors.h"


TEST_SUITE("IO commands") {

    TEST_CASE("PolygonMap") {
        ConvexPolygon pol({{0, 0}});
        PolygonMap testMap;
        testMap["p1"] = pol; testMap["p2"];

        SUBCASE("getPolygon") {
            CHECK_THROWS_AS(getPolygon("p3", testMap), UndefinedID);
            CHECK(getPolygon("p1", testMap) == pol);
            CHECK(getPolygon("p2", testMap) == ConvexPolygon());
        }
        SUBCASE("getPolygons") {
            CHECK_NOTHROW(getPolygons({"p3", "p3", "p3"}, testMap));
            CHECK_THROWS_AS(getPolygons({"p3"}, testMap).front(), UndefinedID);
            CHECK(getPolygons({"p1"}, testMap).front() == pol);
        }
    }

    TEST_CASE("read") {
        PolygonMap testMap;

        istringstream iss("p1 0 0");
        readAndSavePolygon(iss, testMap);
        CHECK(testMap["p1"] == ConvexPolygon({{0, 0}}));

        iss = istringstream("1 1");
        readAndSavePolygon(iss, testMap, "p1");
        CHECK(testMap["p1"] == ConvexPolygon({{1, 1}}));
    }

    TEST_CASE("print") {
        ConvexPolygon pol({{0, 0}});

        std::ostringstream oss;
        printPolygon("p1", pol, oss);
        CHECK(oss.str() == "p1 0.000 0.000\n");
    }

}
