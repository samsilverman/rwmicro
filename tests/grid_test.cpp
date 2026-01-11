#include <stdexcept>
#include <string>
#include <sstream>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>
#include "rwmicro/grid.hpp"

using namespace rwmicro;

TEST_CASE("rwmicro::Grid: Test initalization", "[rwmicro]") {    
    SECTION("Invalid dimensions") {
        REQUIRE_THROWS_AS(Grid(0, 3), std::invalid_argument);
        REQUIRE_THROWS_AS(Grid(2, 0), std::invalid_argument);
    }
}

TEST_CASE("rwmicro::Grid: Test nx", "[rwmicro]") {    
    Grid grid(2, 3);

    REQUIRE(grid.nx() == 2);
}

TEST_CASE("rwmicro::Grid: Test ny", "[rwmicro]") {    
    Grid grid(2, 3);

    REQUIRE(grid.ny() == 3);
}

TEST_CASE("rwmicro::Grid: Test clear", "[rwmicro]") {    
    Grid grid(2, 3);
    grid(0, 0) = 1;

    grid.clear();

    REQUIRE(grid(0, 0) == 0);
}

TEST_CASE("rwmicro::Grid: Test operator()", "[rwmicro]") {    
    Grid grid(2, 3);

    REQUIRE(grid(0, 1) == 0);

    grid(0, 1) = 1;

    REQUIRE(grid(0, 1) == 1);

    // Periodic wrapping
    REQUIRE(grid(2, 1) == 1);
    REQUIRE(grid(-2, 1) == 1);
    REQUIRE(grid(0, 4) == 1);
    REQUIRE(grid(0, -2) == 1);
    REQUIRE(grid(2, -2) == 1);
    REQUIRE(grid(2, 4) == 1);
    REQUIRE(grid(-2, -2) == 1);
    REQUIRE(grid(-2, 4) == 1);
}

TEST_CASE("rwmicro::Grid: Test bitString", "[rwmicro]") {    
    Grid grid(2, 3);
    grid(0, 1) = 1;
    grid(1, 0) = 1;
    grid(0, 2) = 1;
    grid(1, 2) = 1;

    std::string expected;

    // Header: nx
    // columns=2 as 32‑bit little‑endian → 0x02 0x00 0x00 0x00
    expected.push_back(char{0x02});
    expected.push_back(char{0x00});
    expected.push_back(char{0x00});
    expected.push_back(char{0x00});

    // Header: ny
    // rows=3 as 32‑bit little‑endian → 0x03 0x00 0x00 0x00
    expected.push_back(char{0x03});
    expected.push_back(char{0x00});
    expected.push_back(char{0x00});
    expected.push_back(char{0x00});

    // Data
    // Bits (column-major):
    // index: 5 4 3 2 1 0
    // value: 1 0 1 1 1 0 → 0b00101110 = 0x2E
    expected.push_back(char{0x2E});

    REQUIRE(grid.bitString() == expected);
}

TEST_CASE("rwmicro::Grid: Test operator<<", "[rwmicro]") {    
    Grid grid(2, 3);
    grid(0, 1) = 1;
    grid(1, 0) = 1;
    grid(0, 2) = 1;
    grid(1, 2) = 1;

    std::ostringstream oss;
    oss << grid;

    std::string expected = "1 1\n"
                           "1 0\n"
                           "0 1";

    REQUIRE(oss.str() == expected);
}
