#include <queue>
#include <utility>
#include <array>
#include "rwmicro/has_valid_connectivity.hpp"

namespace rwmicro {

    bool hasValidConnectivity(const Grid &grid) noexcept {
        const int nx = static_cast<int>(grid.nx());
        const int ny = static_cast<int>(grid.ny());

        int mass = 0;
        std::queue<std::pair<int, int>> queue;
        Grid tiled(2 * grid.nx(), 2 * grid.ny());

        for (int i = 0; i < nx; ++i) {
            for (int j = 0; j < ny; ++j) {
                if (grid(i, j) == 1) {
                    mass++;

                    // Starting point for BFS is first visited filled cell
                    if (queue.empty()) {
                        queue.push({i, j});
                    }

                    // Fill tiled grid
                    tiled(i, j) = 1;
                    tiled(i + nx, j) = 1;
                    tiled(i + nx, j + ny) = 1;
                    tiled(i, j + ny) = 1;
                }
            }
        }

        if (mass == 0) {
            return false;
        }

        // BFS
        int numVisited = 0;

        Grid visited(tiled.nx(), tiled.ny());

        const std::array<std::pair<int, int>, 4> steps = {{
            {-1, 0},
            {1, 0},
            {0, -1},
            {0, 1}
        }};

        while (!queue.empty()) {
            auto [i, j] = queue.front();
            queue.pop();

            if (visited(i, j) == 0) {
                visited(i, j) = 1;
                numVisited++;
            }

            for (const auto &[di, dj] : steps) {
                const int iNext = i + di;
                const int jNext = j + dj;

                if (visited(iNext, jNext) == 0 && tiled(iNext, jNext) == 1) {
                    queue.push({iNext, jNext});
                }
            }
        }

        return numVisited == 4 * mass;
    }

} // namespace rwmicro
