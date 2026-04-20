This repository used to learn base vulkan concepts :

* Vulkan 1.4 as a baseline
* Dynamic rendering instead of render passes
* Timeline semaphores
* [Slang](https://shader-slang.org/) as the primary shading language
* [Vulkan-Hpp](https://github.com/KhronosGroup/Vulkan-Hpp) with [RAII](https://en.wikipedia.org/wiki/Resource_acquisition_is_initialization)

The repository is organized into several important directories:
* `scripts/` - Contains utility scripts, including dependency installation scripts
* `src/` - Contains all source code

## Installation Dependencies

### Windows

Run the following command to install dependencies on Windows `scripts\install_dependencies_windows.bat`

This script uses vcpkg to install the required dependencies, including:
* GLFW, GLM, tinyobjloader, stb

You will also need to install the Vulkan SDK separately from https://vulkan.lunarg.com/.

---

The origina source: https://github.com/KhronosGroup/Vulkan-Tutorial
