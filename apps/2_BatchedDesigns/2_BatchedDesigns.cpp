/**
 * @brief Command-line tool for generating a batch of valid microstructures.
 * 
 * This program generates a batch of `numSamples` random-walk microstructures
 * of size `nx`x`ny`. For each sample, a target mass is drawn at random, and
 * the generator attempts to produce a valid microstructure up to `retries`
 * times. If all attempts fail, a new random mass is drawn and the process
 * repeats until a valid sample is obtained.
 *
 * All generated microstructures are written to CSV files under:
 * 
 *      `/path/to/apps/microstructures/#.csv`
 * 
 * This program may be compiled with OpenMP to enable parallel generation.
 *
 * @param nx Number of grid cells in the x-direction.
 * @param ny Number of grid cells in the y-direction.
 * @param numSamples Number of samples.
 * @param retries  Number of attempts per mass before incrementing (default: 100).
 * @param seed RNG seed (default: random).
 *
 * Usage:
 *      $ 2_BatchedDesigns <nx> <ny> <numSamples> [retries] [seed]
 *
 * Example:
 *      $ 2_BatchedDesigns 10 10 50 100 1234
 *      [==================================================] 100% (100/100)
 *      Saved to /path/to/folder/microstructures.
 */
#include <cstddef>
#include <iostream>
#include <string>
#include <random>
#include <filesystem>
#include <vector>
#include <unordered_set>
#ifdef _OPENMP
#include <omp.h>
#endif
#include <rwmicro/rwmicro.hpp>

static void printProgress(int done, int total) {
    const int barWidth = 50;
    const float ratio = static_cast<float>(done) / static_cast<float>(total);
    const int position = static_cast<int>(static_cast<float>(barWidth) * ratio);

    // Return to start of line
    std::cout << "\r[";
    for (int i = 0; i < barWidth; ++i) {
        if (i < position) {
            std::cout << "=";
        }
        else if (i == position) {
            std::cout << ">";
        }
        else {
            std::cout << " ";
        }
    }
    std::cout << "] " << int(ratio * 100.0f)
              << "% (" << done << "/" << total << ")"
              << std::flush;
}

int main(int argc, char *argv[]) {
    if (argc < 5 || argc > 6) {
        std::cerr << "Usage: " << argv[0] << " <nx> <ny> <numSamples> [retries] [seed]\n";
        return 1;
    }

    std::size_t nx;
    std::size_t ny;
    std::size_t numSamples;
    std::size_t retries = 100;
    unsigned int seed = std::random_device{}();

    try {
        nx = std::stoul(argv[1]);
        ny = std::stoul(argv[2]);
        numSamples = std::stoul(argv[3]);

        if (argc > 3) {
            retries = std::stoul(argv[4]);
        }
        if (argc > 4) {
            seed = static_cast<unsigned int>(std::stoul(argv[5]));
        }
    }
    catch (const std::invalid_argument &e) {
        std::cerr << "2_BatchedDesignss: Invalid argument: " << e.what() << std::endl;
        return 1;
    }

    if (nx == 0) {
        std::cerr << "2_BatchedDesigns: nx must be nonzero.\n";
    }
    if (ny == 0) {
        std::cerr << "2_BatchedDesigns: ny must be nonzero.\n";
    }
    if (retries == 0) {
        std::cerr << "2_BatchedDesigns: retries must be nonzero.\n";
    }

    const auto folder = std::filesystem::path(__FILE__).parent_path() / "microstructures";

    if (std::filesystem::exists(folder)) {
        std::filesystem::remove_all(folder);
    }
    std::filesystem::create_directories(folder);

    // actual valid mass range
    const std::size_t minMass = nx + ny - 1;
    const std::size_t maxMass = nx * ny;

    std::mt19937 genMain(seed);

    // Each sample gets a unique seed for its mass distribution sampling
    std::vector<unsigned int> seeds(numSamples);
    for (std::size_t sample = 0; sample < numSamples; ++sample) {
        seeds[sample] = genMain();
    }

    std::uniform_int_distribution<std::size_t> massDistribution(minMass, maxMass);

    std::unordered_set<std::string> seen;

    int completed = 0;

#ifdef _OPENMP
#ifdef DEFAULT_OMP_NUM_THREADS
    omp_set_num_threads(DEFAULT_OMP_NUM_THREADS);
#endif
    #pragma omp parallel for schedule(dynamic, 1) if (numSamples > 1)
#endif
    for (std::size_t sample = 0; sample < numSamples; ++sample) {
        std::mt19937 gen(seeds[sample]);

        rwmicro::Grid grid(nx, ny);

        bool success = false;

        while (!success) {
            const std::size_t mass = massDistribution(gen);

            for (std::size_t attempt = 0; attempt < retries && !success; ++attempt) {
                const unsigned int subseed = gen();

                grid.clear();
                rwmicro::grow(grid, mass, subseed);

                if (rwmicro::validate(grid) == false) {
                    continue;
                }

                const auto key = grid.bitString();

                bool hasNotSeen;
#ifdef _OPENMP
                #pragma omp critical
#endif
                hasNotSeen = seen.insert(key).second;

                if (hasNotSeen) {
                    success = true;
                }
            }
        }

#ifdef _OPENMP
        #pragma omp atomic
#endif
        completed += 1;

        const auto file = folder / (std::to_string(sample + 1) + ".csv");
        rwmicro::save(grid, file.string());

#ifdef _OPENMP
        #pragma omp critical
#endif
        printProgress(completed, static_cast<int>(numSamples));
    }

    std::cout << std::endl;

    return 0;
}
