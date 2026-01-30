#include <stdexcept>
#include <string>
#include <array>
#include <utility>
#include "rwmicro/grow.hpp"

namespace rwmicro {

    void grow(Grid &grid, std::size_t targetMass, unsigned int seed) {
        const std::size_t nx = grid.nx();
        const std::size_t ny = grid.ny();

        if (targetMass > nx * ny) {
            throw std::invalid_argument("targetMass (" + std::to_string(targetMass) + ") must be in the range [0," + std::to_string(nx * ny) + "].");
        }

        grid.clear();

        const std::array<std::pair<int, int>, 4> steps = {{
            {-1, 0},
            {1, 0},
            {0, -1},
            {0, 1}
        }};

        std::mt19937 gen(seed);

        // std::uniform_int_distribution is not portably defined across compilers.
        // Use modulo on the standardized mt19937 engine to guarantee 
        // bit-perfect results across Mac, Windows, and Linux.
        auto randomInt = [&](std::size_t limit) -> int { 
            return static_cast<int>(gen() % static_cast<unsigned int>(limit)); 
        };

        int i = randomInt(nx - 1);
        int j = randomInt(ny - 1);

        std::size_t mass = 0;

        while (mass < targetMass) {
            if (grid(i, j) == 0) {
                grid(i, j) = 1;
                mass++;
            }

            const std::size_t randomIndex = static_cast<std::size_t>(randomInt(steps.size() - 1));
            const auto &[dx, dy] = steps[randomIndex];

            i += dx;
            j += dy;
        }
    }

} // namespace rwmicro
