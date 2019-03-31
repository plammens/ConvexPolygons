#include <doctest.h>
#include <sstream>
#include "io-commands.h"
#include "errors.h"


TEST_SUITE("io commands") {

    TEST_CASE("PolygonMap") {
        ConvexPolygon pol({{0, 0}});
        PolygonMap testMap;
        testMap["p1"] = pol; testMap["p2"];

        SUBCASE("getPolygon") {
            CHECK_THROWS_AS(getPolygon("p3", testMap), error::UndefinedID);
            CHECK(getPolygon("p1", testMap) == pol);
            CHECK(getPolygon("p2", testMap) == ConvexPolygon());
        }
        SUBCASE("getPolygons") {
            CHECK_NOTHROW(getPolygons({"p3", "p3", "p3"}, testMap));
            CHECK_THROWS_AS(getPolygons({"p3"}, testMap).front(), error::UndefinedID);
            CHECK(getPolygons({"p1"}, testMap).front() == pol);
        }
    }

    TEST_CASE("read") {
        PolygonMap testMap;
		
        std::istringstream iss1("p1 0 0");
        readAndSavePolygon(iss1, testMap);
        CHECK(testMap["p1"] == ConvexPolygon({{0, 0}}));

        std::istringstream iss2("1 1");
        readAndSavePolygon(iss2, testMap, "p1");
        CHECK(testMap["p1"] == ConvexPolygon({{1, 1}}));
    }

    TEST_CASE("print") {
        ConvexPolygon pol({{0, 0}});

        std::ostringstream oss;
        printPolygon("p1", pol, oss);
        CHECK(oss.str() == "p1 0.000 0.000\n");
    }

}
