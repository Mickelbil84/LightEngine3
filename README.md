# Welcome to the LightEngine3 repository! #

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

## Installation and Usage

TODO: Write detailed installation guide.
Installation is done simply with CMake.

### Installation for MacOS (Tested in Intel, Monterey 12.4)

1. Make sure that you have the "Command Line Tools for XCode" installed: https://developer.apple.com/download/all/ (for the AppleClang compiler)
2. Install Homebrew: https://brew.sh
3. Install CMake: https://cmake.org/download/
4. Recommended: Install Visual Studio Code with the "C/C++ Extension Pack" as an IDE
5. Run: `brew install sdl2`
6. Run: `brew install glew`
7. Run: `brew install glm`
8. Run: `brew install assimp`