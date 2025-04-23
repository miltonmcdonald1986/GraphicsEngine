# GraphicsEngine
GraphicsEngine is a simple graphics engine written in C++ using OpenGL.

# Installation and Setup
## Windows
1. Install [Visual Studio](https://visualstudio.microsoft.com/) with the Desktop development with C++ workload.
2. Clone the *GraphicsEngine* repository.
```cmd
git clone --recurse-submodules https://github.com/miltonmcdonald1986/GraphicsEngine.git
```
3. Open *Developer Command Prompt for VS 2022*
4. Navigate to the root of the cloned *GraphicsEngine* repository.
5. Configure using CMake, choosing a preset of your choice. For example, for a debug configuration use:
```cmd
cmake --preset "Debug Windows"
```
6. Build the project.
```cmd
cmake --build --preset "Debug Windows"
```
7. To run a sandbox program with examples, navigate to `build\bin` and run the executable.
```cmd
Sandbox.exe
```

## Linux
