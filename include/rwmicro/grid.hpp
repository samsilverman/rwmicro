#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>
#include <string>
#include <ostream>

namespace rwmicro {

    /**
     * @brief 2D binary grid.
     *
     * This class represents a fixed-size 2D Cartesian grid storing binary
     * values. The grid is stored in a contiguous, column-major layout and
     * supports periodic (wrap-around) indexing.
     *
     */
    class Grid {
    public:
        /**
         * @brief Constructs a grid.
         *
         * @param[in] nx Number of columns.
         * @param[in] ny Number of rows.
         *
         * @throws std::invalid_argument if `nx` is zero.
         * @throws std::invalid_argument if `ny` is zero.
         */
        Grid(std::size_t nx, std::size_t ny);

        /// @brief Number of columns.
        std::size_t nx() const noexcept;

        /// @brief Number of rows.
        std::size_t ny() const noexcept;

        /// @brief Clears the grid.
        void clear() noexcept;

        /**
         * @brief Mutable access to a grid entry.
         *
         * @param[in] i Column index.
         * @param[in] j Row index.
         *
         * @note Supports periodic (wrap-around) indexing.
         */
        uint8_t &operator()(int i, int j) noexcept;

        /**
         * @brief Read-only access to a grid entry.
         *
         * @param[in] i Column index.
         * @param[in] j Row index.
         *
         * @note Supports periodic (wrap-around) indexing.
         */
        uint8_t operator()(int i, int j) const noexcept;

        /**
         * @brief Textual bit-string representation of the grid.
         *
         * This function encodes a (n,m) grid into a byte string
         * containing a 32-bit header for the dimensions followed
         * by a packed bitfield representation of the entries.
         *
         * Layout:
         *
         * - Bytes [0...3] : 32‑bit little‑endian encoding of n.
         *
         * - Bytes [4...7] : 32‑bit little‑endian encoding of m.
         *
         * - Bytes [8...] : ceil(n*m/8) bytes packing the grid entries
         * in column-major order, one bit per cell. Entry (i,j) is mapped
         * to bit (i*m+j)%8 of byte (i*m+j)/8.
         */
        std::string bitString() const noexcept;

    private:
        /// @brief Number of columns.
        const std::size_t nx_;

        /// @brief Number of rows.
        const std::size_t ny_;

        /// @brief Flattened grid data.
        std::vector<std::uint8_t> data_;

        /**
         * @brief Map 2D indices to their cooresponding flattened index.
         *
         * @param i Column index.
         * @param j Row index.
         *
         * @returns Flattened index.
         *
         * @note Supports periodic (wrap-around) indexing.
         */
        std::size_t index_(int i, int j) const noexcept;
    };

    /// @brief Stream insertion operator for Grid.
    std::ostream &operator<<(std::ostream &os, const Grid &grid);

} // namespace name
