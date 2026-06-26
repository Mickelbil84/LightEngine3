cmake_minimum_required(VERSION 3.16)

# Before anything else, use vcpkg with Windows systems
if (WIN32)
    set(CMAKE_TOOLCHAIN_FILE $ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake CACHE STRING "")
endif()


##########################
# Default compile options
##########################

if (NOT DEFINED LE3_WITH_DEMOS) 
    set (LE3_WITH_DEMOS false) 
endif()

if (NOT DEFINED LE3_WITH_EDITOR)
    set (LE3_WITH_EDITOR true)
endif()

if (NOT DEFINED LE3_WITH_GAME)
    set (LE3_WITH_GAME true)
endif()

##########################



set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

if (WIN32)
    add_compile_options(/bigobj)
    add_compile_options(/Zc:preprocessor)
    add_compile_options(/wd5105 /wd4244 /wd4305 /wd4267 /wd4068 /wd4018 /wd4312 /wd4146 /wd4101)
endif ()

# Disable -Wdeprecated-volatile from glm
if (NOT WIN32)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-volatile")
endif()

set(LE3_VERSION 0.2)

project(
    LightEngine3
    VERSION ${LE3_VERSION}
    DESCRIPTION "Lightweight C++ OpenGL toolkit for various purposes"
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_subdirectory(le3)
add_subdirectory(le3game)
add_subdirectory(apps)
add_subdirectory(editor)
add_subdirectory(tools)

if (WIN32)
    # MSVC is a multi-config generator, so the actual binaries land in a
    # per-configuration subdirectory (e.g. bin/Release/pkg-resources.exe)
    add_custom_target(
        pkg-resources-tgt ALL
        COMMAND
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/pkg-resources.exe ${CMAKE_CURRENT_SOURCE_DIR}/resources ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>

        DEPENDS pkg-resources le3
    )

    # Also package all example dirs
    file(GLOB EXAMPLE_DIRS RELATIVE
        "${CMAKE_CURRENT_SOURCE_DIR}/examples"
        "${CMAKE_CURRENT_SOURCE_DIR}/examples/*")

    foreach(EXAMPLE_DIR ${EXAMPLE_DIRS})
        if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/examples/${EXAMPLE_DIR}")
            add_custom_target(
                pkg-resources-tgt-examples-${EXAMPLE_DIR} ALL
                COMMAND
                    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/pkg-resources.exe ${CMAKE_CURRENT_SOURCE_DIR}/examples/${EXAMPLE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/examples/${EXAMPLE_DIR}

                DEPENDS pkg-resources le3
            )
        endif()
    endforeach()
else()
    add_custom_target(
        pkg-resources-tgt ALL
        COMMAND 
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/pkg-resources ${CMAKE_CURRENT_SOURCE_DIR}/resources ${CMAKE_SOURCE_DIR}/bin

        DEPENDS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/pkg-resources 
    )


    # Also package all example dirs
    file(GLOB EXAMPLE_DIRS RELATIVE
        "${CMAKE_CURRENT_SOURCE_DIR}/examples"
        "${CMAKE_CURRENT_SOURCE_DIR}/examples/*")

    foreach(EXAMPLE_DIR ${EXAMPLE_DIRS})
        if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/examples/${EXAMPLE_DIR}")
            add_custom_target(
                pkg-resources-tgt-examples-${EXAMPLE_DIR} ALL
                COMMAND 
                    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/pkg-resources ${CMAKE_CURRENT_SOURCE_DIR}/examples/${EXAMPLE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/examples/${EXAMPLE_DIR}

                DEPENDS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/pkg-resources 
            )
        endif()
    endforeach()
endif()