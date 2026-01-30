#include <stdexcept>
#include <string>
#include <sstream>
#include <catch2/catch_test_macros.hpp>
#include "rwmicro/grid.hpp"
#include "rwmicro/grow.hpp"

using namespace rwmicro;

TEST_CASE("rwmicro: Test grow", "[rwmicro]") {
    Grid grid(3, 4);

    SECTION("No errors") {
        grow(grid, 6, 1234);

        std::ostringstream oss;
        oss << grid;

        std::string expected = "1 0 0\n"
                               "1 1 1\n"
                               "0 0 0\n"
                               "1 1 0";

        REQUIRE(oss.str() == expected);
    }

    SECTION("No errors - targetMass=0") {
        grow(grid, 0, 1234);

        std::ostringstream oss;
        oss << grid;

        std::string expected = "0 0 0\n"
                               "0 0 0\n"
                               "0 0 0\n"
                               "0 0 0";

        REQUIRE(oss.str() == expected);
    }

    SECTION("No errors - targetMass=number of cells") {
        grow(grid, 12, 1234);

        std::ostringstream oss;
        oss << grid;

        std::string expected = "1 1 1\n"
                               "1 1 1\n"
                               "1 1 1\n"
                               "1 1 1";

        REQUIRE(oss.str() == expected);
    }

    SECTION("Invalid targetMass") {
        REQUIRE_THROWS_AS(grow(grid, 13), std::invalid_argument);
    }
}
