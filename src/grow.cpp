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
        std::uniform_int_distribution<std::size_t> step_distribution(0, steps.size() - 1);
        std::uniform_int_distribution<> x_distribution(0, static_cast<int>(nx) - 1);
        std::uniform_int_distribution<> y_distribution(0, static_cast<int>(ny) - 1);

        int i = x_distribution(gen);
        int j = y_distribution(gen);

        std::size_t mass = 0;

        while (mass < targetMass) {
            if (grid(i, j) == 0) {
                grid(i, j) = 1;
                mass++;
            }

            const auto &[dx, dy] = steps[step_distribution(gen)];

            i += dx;
            j += dy;
        }
    }

} // namespace rwmicro
