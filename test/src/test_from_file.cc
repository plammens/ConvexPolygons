#include <doctest.h>
#include "io-commands.h"
#include "details/handlers.h"


TEST_SUITE("from file") {

    TEST_CASE("circle rot") {
        PolygonMap testMap;
        include("test/text/circle-rot.txt", testMap, true);
        bool found = testMap.count("circ") and testMap.count("circ-rot");
        REQUIRE(found);

        ConvexPolygon &circ = getPolygon("circ", testMap);
        ConvexPolygon &circ_rot = getPolygon("circ-rot", testMap);
        ConvexPolygon its = intersection(circ, circ_rot);

        CHECK(its.vertexCount() == 200000);
    }

}
