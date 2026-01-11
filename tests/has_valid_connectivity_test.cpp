#include <catch2/catch_test_macros.hpp>
#include "rwmicro/grid.hpp"
#include "rwmicro/has_valid_connectivity.hpp"

using namespace rwmicro;

TEST_CASE("rwmicro: Test hasValidConnectivity", "[rwmicro]") {    
    SECTION("Valid") {
        // 1111
        // 1110
        // 0011
        // 1001
        Grid grid(4, 4);
        grid(0, 0) = 1;
        grid(3, 0) = 1;
        grid(2, 1) = 1;
        grid(3, 1) = 1;
        grid(0, 2) = 1;
        grid(1, 2) = 1;
        grid(2, 2) = 1;
        grid(0, 3) = 1;
        grid(1, 3) = 1;
        grid(2, 3) = 1;
        grid(3, 3) = 1;

        REQUIRE(hasValidConnectivity(grid) == true);
    }

    SECTION("Invalid") {
        // 0111
        // 1110
        // 0011
        // 1001
        Grid grid(4, 4);
        grid(0, 0) = 1;
        grid(3, 0) = 1;
        grid(2, 1) = 1;
        grid(3, 1) = 1;
        grid(0, 2) = 1;
        grid(1, 2) = 1;
        grid(2, 2) = 1;
        grid(1, 3) = 1;
        grid(2, 3) = 1;
        grid(3, 3) = 1;

        REQUIRE(hasValidConnectivity(grid) == false);
    }
}
