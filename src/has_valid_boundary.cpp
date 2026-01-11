#include "rwmicro/has_valid_boundary.hpp"

namespace rwmicro {

    bool hasValidBoundary(const Grid &grid) noexcept {
        const int nx = static_cast<int>(grid.nx());
        const int ny = static_cast<int>(grid.ny());

        bool hasBottom = false;
        bool hasTop = false;
        bool hasLeft = false;
        bool hasRight = false;

        // Top/bottom checks
        for (int i = 0; i < nx; ++i) {
            if (grid(i, 0) == 1) {
                hasBottom = true;
            }
            if (grid(i, ny - 1) == 1) {
                hasTop = true;
            }
        }

        // Left/right checks
        for (int j = 0; j < ny; ++j) {
            if (grid(0, j) == 1) {
                hasLeft = true;
            }
            if (grid(nx - 1, j) == 1) {
                hasRight = true;
            }
        }

        return hasBottom && hasTop && hasLeft && hasRight;
    }

} // namespace rwmicro
