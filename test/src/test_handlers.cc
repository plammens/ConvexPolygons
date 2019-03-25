#include<doctest.h>
#include "handlers.h"
#include "errors.h"


TEST_SUITE("handlers") {
    
    TEST_CASE("unknown command") {
        PolygonMap testMap;

        CHECK_THROWS_AS(getCommandHandler("pripprò"), UnknownCommand);
    }
    
}
