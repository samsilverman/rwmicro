#pragma once

#include <cstddef>
#include <random>
#include "rwmicro/grid.hpp"

namespace rwmicro {

    /**
     * @brief Grow a microstructure via a random walk.
     *
     * This function performs a random walk on a binary grid,
     * filling cells until the number of filled cells reaches
     * `targetMass`. Each step moves the walker to one of the
     * four axis-aligned neighbors, with wrapping at the domain
     * boundaries. Grid entries are 1 (filled) or 0 (empty).
     *
     * A fixed seed may be provided for reproducibility.
     *
     * @param[in,out] grid Binary grid.
     * @param[in] ny Number of grid cells in the y-direction.
     * @param[in] targetMass Target number of filled cells.
     * @param[in] seed RNG seed (optional).
     *
     * @returns A binary grid representing the generated
     * microstructure.
     *
     * @throws `std::invalid_argument` if `targetMass` is larger than the number of `grid` cells.
     *
     * @note The generated microstructure might be invalid and should be
     * verified with `validate()`.
     */
    void grow(Grid &grid, std::size_t targetMass, unsigned int seed = std::random_device{}());

} // namespace rwmicro
