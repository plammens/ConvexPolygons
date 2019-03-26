#include <doctest.h>
#include "details/handlers.h"
#include "errors.h"


TEST_SUITE("handlers") {
    
    TEST_CASE("unknown command") {
        CHECK_THROWS_AS(getCommandHandler("pripprò"), UnknownCommand);
    }
    
}
