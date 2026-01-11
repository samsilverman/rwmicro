#pragma once

#include "rwmicro/grid.hpp"

namespace rwmicro {

    /**
     * @brief Check whether a binary grid is valid.
     * 
     * A valid grid passes the following checks:
     * 
     * - `hasValidBoundary()`
     * 
     * - `hasValidConnectivity()`
     * 
     * @param[in] grid Binary grid.
     * 
     * @returns `true` if `grid` is valid, `false` otherwise.
     */
    bool validate(const Grid& grid) noexcept;

} // namespace rwmicro
