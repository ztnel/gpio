# Lib GPIO

[![ci](https://github.com/ztnel/gpio/actions/workflows/ci.yml/badge.svg)](https://github.com/ztnel/gpio/actions/workflows/ci.yml) [![codecov](https://codecov.io/gh/ztnel/gpio/branch/master/graph/badge.svg?token=A5AXOKI5ZX)](https://codecov.io/gh/ztnel/gpio)

Modified: 2022-01

Lightweight rpi gpio peripheral drivers.

## Build
Build the library
```bash
cmake -S . -B build
cd build
make -j
```
## Development
For test build tools pass `CMAKE_BUILD_TYPE=Debug`:
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cd build
make -j
```
