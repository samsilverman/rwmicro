#include <stdexcept>
#include <algorithm>
#include "rwmicro/grid.hpp"

namespace rwmicro {

    Grid::Grid(std::size_t nx, std::size_t ny)
        : nx_(nx), ny_(ny) {
        if (nx_ == 0) {
            throw std::invalid_argument("nx must be positive.");
        }
        if (ny_ == 0) {
            throw std::invalid_argument("ny must be positive.");
        }

        data_.assign(nx_ * ny_, uint8_t{0});
    }

    std::size_t Grid::nx() const noexcept {
        return nx_;
    }

    std::size_t Grid::ny() const noexcept {
        return ny_;
    }

    void Grid::clear() noexcept {
        std::fill(data_.begin(), data_.end(), 0);
    }

    uint8_t &Grid::operator()(int i, int j) noexcept {
        return data_[index_(i, j)];
    }

    uint8_t Grid::operator()(int i, int j) const noexcept {
        return data_[index_(i, j)];
    }

    std::size_t Grid::index_(int i, int j) const noexcept {
        const int nx = static_cast<int>(nx_);
        const int ny = static_cast<int>(ny_);

        // Periodic wrap
        i = (i % nx + nx) % nx;
        j = (j % ny + ny) % ny;

        return static_cast<std::size_t>(j + ny * i);
    }

    std::string Grid::bitString() const noexcept {
        const uint32_t nx = static_cast<uint32_t>(nx_);
        const uint32_t ny = static_cast<uint32_t>(ny_);
        const uint32_t numBits = nx * ny;

        // Round up to nearest byte
        const uint32_t numBytes = (numBits + 7) / 8;

        std::string out;
        out.reserve(8 + numBytes);

        // Write grid dimensions in little‑endian form
        for (int byte = 0; byte < 4; ++byte) {
            out.push_back(static_cast<char>((nx >> (8 * byte)) & 0xFF));
        }

        for (int byte = 0; byte < 4; ++byte) {
            out.push_back(static_cast<char>((ny >> (8 * byte)) & 0xFF));
        }

        // Write grid data
        out.append(numBytes, '\0');

        for (std::size_t i = 0; i < data_.size(); ++i) {
            if (data_[i] == 1) {
                // Update byte of memory (bitwise or) w/ grid bit in correct location
                out[8 + (i / 8)] |= static_cast<char>(1u << (i % 8));
            }
        }

        return out;
    }

    std::ostream &operator<<(std::ostream &os, const Grid &grid) {
        const int nx = static_cast<int>(grid.nx());
        const int ny = static_cast<int>(grid.ny());

        for (int j = ny - 1; j >= 0; --j) {
            for (int i = 0; i < nx; ++i) {
                char cell = '0';

                if (grid(i, j) == 1) {
                    cell = '1';
                }

                os << cell;

                if (i < nx - 1) {
                    os << " ";
                }
            }

            if (j > 0) {
                os << "\n";
            }
        }

        return os;
    }

} // namespace rwmicro
