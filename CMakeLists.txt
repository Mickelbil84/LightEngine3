cmake_minimum_required(VERSION 3.11-3.25)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)

if (WIN32)
  add_compile_options(/bigobj)
endif ()

set(LE3_VERSION 0.2)

project(
    LightEngine3
    VERSION ${LE3_VERSION}
    DESCRIPTION "Lightweight C++ OpenGL toolkit for various purposes"
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_subdirectory(le3)
add_subdirectory(apps)
add_subdirectory(editor)

# Copy the resources directory to the build
if (WIN32)
add_custom_target(
    copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/resources
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/resources
)
else()
add_custom_target(
    copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/resources
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources
)
endif()
