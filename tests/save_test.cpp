#include <filesystem>
#include <fstream>
#include <string>
#include <catch2/catch_test_macros.hpp>
#include "rwmicro/grid.hpp"
#include "rwmicro/save.hpp"

using namespace rwmicro;

TEST_CASE("rwmicro: Test save", "[rwmicro]") {   
    auto folder = std::filesystem::path(__FILE__).parent_path();

    Grid grid(2, 3);

    SECTION("No errors") {
        // 00
        // 01
        // 10
        grid(0, 0) = 1;
        grid(1, 1) = 1;

        auto file = folder / "output.csv";

        save(grid, file.string());

        REQUIRE(std::filesystem::exists(file));
        REQUIRE(std::filesystem::is_regular_file(file));

        std::ifstream ifs(file);

        std::string contents((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

        std::string expected = "0,0\n"
                               "0,1\n"
                               "1,0\n";

        REQUIRE(contents == expected);

        std::filesystem::remove(file);
    }

    SECTION("Invalid file extension") {
        auto file = folder / "output.png";

        REQUIRE_THROWS_AS(save(grid, file.string()), std::invalid_argument);
    }

    SECTION("Invalid file path") {
        auto file = folder / "NonExistentDir" / "output.csv";

        REQUIRE_THROWS_AS(save(grid, file.string()), std::runtime_error);
    }
}
