$vcpkgDir = $env:VCPKG_ROOT

#Remove build directory
Remove-Item -Path "build" -Recurse -Force

# Build Debug
cmake -S . -B build -G "Visual Studio 17 2022" -DCMAKE_TOOLCHAIN_FILE="$vcpkgDir\scripts\buildsystems\vcpkg.cmake"
cmake --build build --config Debug

# Build Release
cmake -S . -B build -G "Visual Studio 17 2022" -DCMAKE_TOOLCHAIN_FILE="$vcpkgDir\scripts\buildsystems\vcpkg.cmake"
cmake --build build --config Release