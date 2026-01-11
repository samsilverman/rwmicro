#pragma once

#include <string>
#include "rwmicro/grid.hpp"

namespace rwmicro {

    /**
     * @brief Save a binary grid to a CSV file.
     *
     * The output file is created or overwritten if it already exists. Parent
     * directories are created automatically.
     * 
     * @param[in] grid Binary grid.
     * @param[in] file Path to the CSV file.
     *
     * @throws std::invalid_argument if the `file` extension is not `.csv`.
     * @throws std::runtime_error if the `file` cannot be opened.
     */
    void save(const Grid& grid, const std::string& file);

} // namespace rwmicro
