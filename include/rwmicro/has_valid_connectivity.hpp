#pragma once

#include "rwmicro/grid.hpp"

namespace rwmicro {

    /**
     * @brief Check whether the filled cells of a binary grid, tiled 2×2, form a single connected component.
     *
     * This function tiles the input binary grid into a 2×2 version and performs a breadth-first search with
     * periodic wrapping. The grid is said to have valid connectivity if, in this tiled 2×2 domain, all filled
     * (1) cells belong to a single connected component.
     *
     * @param[in] grid Binary grid.
     *
     * @returns `true` if all filled cells are connected in the 2×2 tiled domain, `false` otherwise.
     */
    bool hasValidConnectivity(const Grid &grid) noexcept;

} // namespace rwmicro
