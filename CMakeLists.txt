cmake_minimum_required(VERSION 3.11-3.25)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)

project(
    LightEngine
    VERSION 0.1
    DESCRIPTION "Lightweight C++ OpenGL toolkit for various purposes"
)

add_subdirectory(le3)
add_subdirectory(apps)
add_subdirectory(editor)