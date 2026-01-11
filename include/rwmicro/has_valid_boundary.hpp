#pragma once

#include "rwmicro/grid.hpp"

namespace rwmicro {

    /**
     * @brief Check whether a binary grid has at least one filled cell on each boundary.
     *
     * This function inspects the four outer boundaries (top row, bottom row, left
     * column, and right column) and returns true only if each boundary contains at
     * least one filled (1) cell.
     *
     * @param[in] grid Binary grid.
     *
     * @returns `true` if each boundary has at least one filled cell, `false` otherwise.
     */
    bool hasValidBoundary(const Grid &grid) noexcept;

} // namespace rwmicro
