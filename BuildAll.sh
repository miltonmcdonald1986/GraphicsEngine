#!/bin/bash

# Set vcpkg directory
vcpkgDir="$VCPKG_ROOT"

# Remove build directory
rm -rf build

# Export g++-13 as the compiler
export CC=gcc-13
export CXX=g++-13

# Build Debug
cmake -S . -B build -G "Ninja" -DCMAKE_TOOLCHAIN_FILE="$vcpkgDir/scripts/buildsystems/vcpkg.cmake" -DCMAKE_BUILD_TYPE=Debug
cmake --build build --config Debug

# Build Release
cmake -S . -B build -G "Ninja" -DCMAKE_TOOLCHAIN_FILE="$vcpkgDir/scripts/buildsystems/vcpkg.cmake" -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
