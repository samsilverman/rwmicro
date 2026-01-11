#include <catch2/catch_test_macros.hpp>
#include "rwmicro/grid.hpp"
#include "rwmicro/has_valid_boundary.hpp"

using namespace rwmicro;

TEST_CASE("rwmicro: Test hasValidBoundary", "[rwmicro]") {    
    SECTION("Valid boundary") {
        // 010
        // 101
        // 010
        Grid grid(3, 3);
        grid(0, 1) = 1;
        grid(2, 1) = 1;
        grid(1, 0) = 1;
        grid(1, 2) = 1;

        REQUIRE(hasValidBoundary(grid) == true);
    }

    SECTION("Valid boundary - corners") {
        // 001
        // 000
        // 100
        Grid grid(3, 3);
        grid(0, 0) = 1;
        grid(2, 2) = 1;

        REQUIRE(hasValidBoundary(grid) == true);
    }

    SECTION("false") {
        // 000
        // 101
        // 010
        Grid grid(3, 3);
        grid(0, 1) = 1;
        grid(2, 1) = 1;
        grid(1, 0) = 1;

        REQUIRE(hasValidBoundary(grid) == false);
    }
}
