#include "rwmicro/validate.hpp"
#include "rwmicro/has_valid_boundary.hpp"
#include "rwmicro/has_valid_connectivity.hpp"

namespace rwmicro {

    bool validate(const Grid& grid) noexcept {
        if (!hasValidBoundary(grid)) {
            return false;
        }
        if (!hasValidConnectivity(grid)) {
            return false;
        }

        return true;
    }

} // namespace rwmicro
