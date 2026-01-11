#include <filesystem>
#include <fstream>
#include <stdexcept>
#include "rwmicro/save.hpp"

namespace rwmicro {

    void save(const Grid &grid, const std::string &file) {
        if (std::filesystem::path(file).extension() != ".csv") {
            throw std::invalid_argument("File extension must be \".csv\".");
        }

        std::ofstream ofs(file, std::ios::trunc | std::ios::binary);
        if (!ofs.is_open()) {
            throw std::runtime_error("Could not open " + file + " for writing.");
        }

        std::string line;
        // Digits + commas
        line.reserve(2 * grid.nx() - 1);
        
        const int nx = static_cast<int>(grid.nx());
        const int ny = static_cast<int>(grid.ny());

        for (int j = ny - 1; j >= 0; --j) {
            line.clear();

            for (int i = 0; i < nx; ++i) {
                char cell = '0';

                if (grid(i, j) == 1) {
                    cell = '1';
                }

                line.push_back(cell);

                if (i + 1 < nx) {
                    line.push_back(',');
                }
            }

            line.push_back('\n');

            ofs.write(line.data(), static_cast<std::ptrdiff_t>(line.size()));
        }
    }

} // namespace rwmicro
