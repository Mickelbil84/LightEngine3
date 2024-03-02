[![Build](https://github.com/Mickelbil84/LightEngine3/actions/workflows/cmake-multi-platform.yml/badge.svg)](https://github.com/Mickelbil84/LightEngine3/actions/workflows/cmake-multi-platform.yml)
 [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://github.com/Mickelbil84/LightEngine3/blob/master/LICENSE)


# Welcome to the LightEngine3 repository! #

![Screenshot](<https://raw.githubusercontent.com/Mickelbil84/LightEngine3/master/docs/screenshots/Screenshot 2024-03-03 at 1.17.31.png>)

## Introduction

LightEngine3 is a lightweight OpenGL rendering engine (which also contains some elements of a game engine),
and should be used for rapid development of experimental projects as well as games.

This framework is built mostly on SDL2 and glew.


### Why 3? What happened to 1 and 2?

LightEngine is a long dream of mine, and I have tackled it many times in the last 10 years- each time (hopefully) wiser than the previous.
Every iteration, after looking at the last attempt from previous years in disgust, I decided to begin from scratch and rewrite 
the entire framework. During my MSc degree I decided to once again tackle this project, this time with more robust building process
via CMake, and developing a library (and not just an executable) from the outset, so that the framework could also be used in external projects.
Also the first game engine I have seriously learned was the Unreal Engine 3 hence the name "LightEngine3" has a nice, familiar sound (at least for me).

Even this new version, V2, is a (once again) re-write of LightEngine, made during my PhD. With even better CMake integration, Lua bindings and better framework, utilizing smart pointers and RAII. 

## Installation and Usage

TODO: Write detailed installation guide.
Installation is done simply with CMake.

### Installation for Windows

1. Install vcpkg: https://vcpkg.io/en/index.html
2. Install CMake: https://cmake.org/download/
3. Recommended: Install Visual Studio Code with the "C/C++ Extension Pack" as an IDE
4. Set the CMAKE toolchain to vcpkg:
    1. In Visual Studio Code, press: Ctrl + Shift + P and type: "Preferences: Open Settings (JSON)"
    2. Append to the JSON file the follwing (replace {vcpkg_install_path} with your actual install path): `"cmake.configureSettings": { "CMAKE_TOOLCHAIN_FILE": "{vcpkg_install_path}/scripts/buildsystems/vcpkg.cmake" }}`
    3. If exists, delete the project's build folder
5. Run: `vcpkg install sdl2:x64-windows`
6. Run: `vcpkg install glew:x64-windows`
7. Run: `vcpkg install glm:x64-windows`
8. Run: `vcpkg install assimp:x64-windows`
9. Run: `vcpkg install wxwidgets:x64-windows`
10. Run: `vcpkg install bullet3:x64-windows`
11. Run: `vcpkg install fmt:x64-windows`
11. Run: `vcpkg install cereal:x64-windows`

### Installation for MacOS (Tested in Intel and Apple Silicon, Monterey 12.4)

1. Make sure that you have the "Command Line Tools for XCode" installed: https://developer.apple.com/download/all/ (for the AppleClang compiler)
2. Install Homebrew: https://brew.sh
3. Install CMake: https://cmake.org/download/
4. Recommended: Install Visual Studio Code with the "C/C++ Extension Pack" as an IDE
5. Run: `brew install sdl2`
6. Run: `brew install glew`
7. Run: `brew install glm`
8. Run: `brew install assimp`
9. Run: `brew install wxwidgets` [No longer required]
10. Run: `brew install bullet` [No longer required]
11. Run: `brew install fmt`
12. Run: `brew install cxxopts`

NOTE: To ignore glm's CMake warning, you need to edit glmConfig.cmake in glm installation to increase CMake version to 3.6.
(This is also a recent [as of January 2024] commit on glm's repository from July 2023).

### Things to remember when binding LE3 types to Lua

* Declare `LOPEN_DECLARE(LE3Classname);`` in `le3_script_bindings.h`
* Add `REGISTER(LE3Classname);` in `le3_script_bindings.cpp`
* Add a new file `src/bindings/le3_binding_XXX.cpp` and implement `LIB(LE3Classname)` (and the binding functions)
* Add `src/bindings/le3_binding_XXX.cpp` the the le3 `CMakeLists.txt`
* If applicable, add serialization code in `resources/engine/scripts/bindings` 
* Also add the class to `load_scene.lua`)

Annotations are auto-generated during build!

## Acknowledgments

Car model: [link](https://sketchfab.com/3d-models/free-concept-car-025-public-domain-cc0-e3a65443d3e44c33b594cec591c01c05)