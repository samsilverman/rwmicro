/**
 * @brief Command-line tool for generating a single valid microstructure.
 *
 * This program generates a random-walk microstructure of size `nx`x`ny`.
 * A target mass is drawn at random, and the generator attempts to produce
 * a valid microstructure up to `retries` times. If all attempts fail, a new
 * random mass is drawn and the process repeats until a valid sample is obtained.
 * 
 * The generated microstructure is written to CSV files under:
 * 
 *     `/path/to/apps/1_SingleDesign/output.csv`
 * 
 * If the output directory does not exist, it is created automatically.
 *
 * @param nx Number of grid cells in the x-direction.
 * @param ny Number of grid cells in the y-direction.
 * @param targetMass Target number of filled cells.
 * @param retries Number of attempts per mass before incrementing (default: 100).
 * @param seed RNG seed (default: random).
 *
 * Usage:
 *      $ 1_SingleDesign <nx> <ny> <targetMass> [retries] [seed]
 *
 * Example:
 *      $ 1_SingleDesign 10 10 30 100 1234
 *      Microstructure (mass=31):
 *      0 0 0 1 1 1 1 0 0 0
 *      0 0 0 0 0 1 1 0 0 0
 *      0 0 0 0 0 1 0 0 0 0
 *      0 0 0 0 0 1 0 0 0 0
 *      0 0 0 0 0 1 0 0 0 0
 *      0 0 0 0 1 1 1 0 0 0
 *      0 0 0 0 0 1 1 0 0 0
 *      1 0 0 0 0 1 1 1 1 1
 *      1 1 0 0 0 1 0 0 0 0
 *      1 1 1 1 1 1 0 0 0 1
 *      Saved to /path/to/apps/1_SingleDesign/output.csv.
 */
#include <cstddef>
#include <iostream>
#include <string>
#include <random>
#include <filesystem>
#include <rwmicro/rwmicro.hpp>

int main(int argc, char *argv[]) {
    if (argc < 4 || argc > 6) {
        std::cerr << "Usage: " << argv[0] << " <nx> <ny> [targetMass] [retries] [seed]\n";
        return 1;
    }

    std::size_t nx;
    std::size_t ny;
    std::size_t targetMass;
    std::size_t retries = 100;
    unsigned int seed = std::random_device{}();

    try {
        nx = std::stoul(argv[1]);
        ny = std::stoul(argv[2]);
        targetMass = std::stoul(argv[3]);

        if (argc > 3) {
            retries = std::stoul(argv[4]);
        }
        if (argc > 4) {
            seed = static_cast<unsigned int>(std::stoul(argv[5]));
        }
    }
    catch (const std::invalid_argument &e) {
        std::cerr << "1_SingleDesigns: Invalid argument: " << e.what() << std::endl;
        return 1;
    }

    if (nx == 0) {
        std::cerr << "1_SingleDesign: nx must be nonzero.\n";
    }
    if (ny == 0) {
        std::cerr << "1_SingleDesign: ny must be nonzero.\n";
    }
    if (targetMass == 0) {
        std::cerr << "1_SingleDesign: targetMass must be nonzero.\n";
    }

    // actual valid mass range
    const std::size_t minMass = nx + ny - 1;
    const std::size_t maxMass = nx * ny;

    if (targetMass > maxMass) {
        std::cerr << "1_SingleDesign: targetMass (" << targetMass << ") must not exceed total number of cells (" << maxMass << ").\n";
    }

    if (retries == 0) {
        std::cerr << "1_SingleDesign: retries must be nonzero.\n";
    }

    std::mt19937 gen(seed);
    const std::uniform_int_distribution<std::size_t> massDistribution(minMass, maxMass);

    // ignore targetMass < minMass to save time
    if (targetMass < minMass) {
        targetMass = minMass;
    }

    rwmicro::Grid grid(nx, ny);

    bool success = false;

    while (!success) {
        for (std::size_t attempt = 0; attempt < retries && !success; ++attempt) {
            const unsigned int subseed = gen();

            grid.clear();
            rwmicro::grow(grid, targetMass, subseed);
            success = rwmicro::validate(grid);
        }

        ++targetMass;
    }

    std::cout << "Microstructure (mass=" << targetMass << "):\n" << grid << std::endl;

    const auto file = std::filesystem::path(__FILE__).parent_path() / "output.csv";

    rwmicro::save(grid, file.string());

    std::cout << "Saved to " << file << std::endl;

    return 0;
}
