[![Build Graphics Engine (ubuntu-latest, gcc)](https://github.com/miltonmcdonald1986/GraphicsEngine/actions/workflows/BuildGraphicsEngineGCC.yml/badge.svg)](https://github.com/miltonmcdonald1986/GraphicsEngine/actions/workflows/BuildGraphicsEngineGCC.yml)
[![Build Graphics Engine (ubuntu-latest, clang)](https://github.com/miltonmcdonald1986/GraphicsEngine/actions/workflows/BuildGraphicsEngineClang.yml/badge.svg)](https://github.com/miltonmcdonald1986/GraphicsEngine/actions/workflows/BuildGraphicsEngineClang.yml)
[![Cppcheck](https://github.com/miltonmcdonald1986/GraphicsEngine/actions/workflows/cppcheck.yml/badge.svg)](https://github.com/miltonmcdonald1986/GraphicsEngine/actions/workflows/cppcheck.yml)

# GraphicsEngine
GraphicsEngine is a simple, cross-platform graphics engine written in C++ using OpenGL.

# Setup
## Visual Studio 2022
Clone the repository and generate the project files.
```
git clone --recurse-submodules https://github.com/miltonmcdonald1986/GraphicsEngine.git
```

Navigate to the newly cloned directory.
```
cd GraphicsEngine
```

Generate the project files with cmake.
```
cmake -S . -B build
```

Open the `GraphicsEngine.sln` file in the newly created `build` directory.
Click on the ![Local Windows Debugger](https://github.com/user-attachments/assets/22cff59f-24af-4d5a-b2e7-e63fcfe5510a) button to build the projects and launch the Sandbox application.

## Linux
Clone the repository and generate the project files.
```
git clone --recurse-submodules https://github.com/miltonmcdonald1986/GraphicsEngine.git
```

Navigate to the newly cloned directory.
```
cd GraphicsEngine
```

Generate the project files with cmake.
```
cmake -S . -B build
```

Build the project with cmake.
```
cmake --build build
```

Navigate to the output dir
```
cd build/bin/
```

Then run the app
```
./Sandbox
```
