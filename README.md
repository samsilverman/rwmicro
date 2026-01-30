# rwmicro

[![Report a Bug](https://img.shields.io/static/v1.svg?label=🐛&message=Report%20a%20Bug&color=red)](https://github.com/samsilverman/rwmicro/issues)
[![Request a Feature](https://img.shields.io/static/v1.svg?label=💡&message=Request%20a%20Feature&color=yellow)](https://github.com/samsilverman/rwmicro/issues)
[![Read the Paper](https://img.shields.io/static/v1.svg?label=DOI&message=10.1145/3745778.3766645&color=blue)](https://doi.org/10.1145/3745778.3766645)

[![MacOS Build Status](https://github.com/samsilverman/rwmicro/actions/workflows/macos-build.yml/badge.svg)](https://github.com/samsilverman/rwmicro/actions/workflows/macos-build.yml)
[![Ubuntu Build Status](https://github.com/samsilverman/rwmicro/actions/workflows/ubuntu-build.yml/badge.svg)](https://github.com/samsilverman/rwmicro/actions/workflows/ubuntu-build.yml)
[![Windows Build Status](https://github.com/samsilverman/rwmicro/actions/workflows/windows-build.yml/badge.svg)](https://github.com/samsilverman/rwmicro/actions/workflows/windows-build.yml)

![Teaser](https://github.com/samsilverman/rwmicro/blob/main/assets/images/teaser.svg)

`rwmicro` is a lightweight C++ library for generating *random-walk microstructures*—binary patterns created by a periodic random walk.

Random walk microstructures produce expressive, diverse, and always-connected material layouts that are ideal for metamaterial design and learning structure–property relationships. This library is used in our paper:

   >Samuel Silverman, Dylan Balter, Keith A. Brown, Emily Whiting  
   [*Random-Walk Microstructures for Differentiable Topology Optimization*](https://sam-silverman.com/assets/pdf/Silverman-RandomWalkMicrostructures.pdf)  
   Proceedings of the  ACM Symposium on Computational Fabrication (2025)

## Dependencies

- **C++17 or later**
- **Catch2 v3** (optional, for testing)
- **OpenMP** (optional, for example applications)

## Building

```bash
git clone https://github.com/samsilverman/rwmicro.git
cd rwmicro
mkdir build && cd build
cmake ..
make -j8
```

The recommended way to use `rwmicro` is to vendor it directly (e.g., as a git submodule) and add it to your build with:

```cmake
add_subdirectory("path/to/rwmicro")
target_link_libraries(your_target PRIVATE rwmicro)
```

### Library Compile Flags

| CMake Flag | Default | Description |
| - | - | - |
| `RWMICRO_BUILD_TESTS` | `OFF` | Build test suite. |
| `RWMICRO_BUILD_APPS` | `OFF` | Build command-line applications. |
| `RWMICRO_USE_OPENMP` | `OFF` | Enable OpenMP parallelism in command-line applications. |

These flags are set in the cmake line:

```bash
cmake .. -DRWMICRO_BUILD_APPS=ON ...
```

For convenience, a `build.sh` script is included for building with compile flags:

```bash
./build.sh
```

## Minimal Example

```cpp
#include <cstddef>
#include <iostream>
#include <rwmicro/rwmicro.hpp>

int main() {
    const std::size_t nx = 5;
    const std::size_t ny = 5;
    const std::size_t targetMass = 15;

    rwmicro::Grid grid(nx, ny);
    rwmicro::grow(grid, targetMass);
    const bool valid = rwmicro::validate(grid);

    std::cout << "Microstructure:\n" << grid << std::endl;
    std::cout << "Valid: " << valid << std::endl;

    rwmicro::save(grid, "microstructure.csv");

    return 0;
}
```

## Documentation

Documentation for all functions is provided through Doxygen-style docstrings. [Command-line tools](https://github.com/samsilverman/rwmicro/blob/main/apps/README.md) in `apps/` demonstrate complete example workflows.

## Applications

Build and run the provided command-line tools:

```bash
mkdir build && cd build
cmake -DRWMICRO_BUILD_APPS=ON ..
make -j8
./apps/<app_name>
```

See the apps [README](https://github.com/samsilverman/rwmicro/blob/main/apps/README.md) for more details.

## Tests

Build and run the test suite:

```bash
mkdir build && cd build
cmake -DRWMICRO_BUILD_TESTS=ON ..
make -j8
./tests/rwmicro_tests
```

## Contributing

Contribution guidelines are provided in [CONTRIBUTING.md](https://github.com/samsilverman/rwmicro/blob/main/CONTRIBUTING.md).

## Maintainers

- [Sam Silverman](https://github.com/samsilverman/) - [sssilver@bu.edu](mailto:sssilver@bu.edu)

## Citation

```text
@inproceedings{Silverman:2025:RandomWalkMicrostructures,
author = {Silverman, Samuel and Balter, Dylan and Brown, Keith A. and Whiting, Emily},
title = {Random-Walk Microstructures for Differentiable Topology Optimization},
year = {2025},
isbn = {9798400720345},
publisher = {Association for Computing Machinery},
address = {New York, NY, USA},
url = {https://doi.org/10.1145/3745778.3766645},
doi = {10.1145/3745778.3766645},
booktitle = {Proceedings of the ACM Symposium on Computational Fabrication},
articleno = {25},
numpages = {11},
keywords = {microstructures, random walks, inverse design, neural networks, homogenization},
location = {},
series = {SCF '25}
}
```

## License

Released under the [MIT License](https://github.com/samsilverman/rwmicro/blob/main/LICENSE).
