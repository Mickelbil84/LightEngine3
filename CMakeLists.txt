cmake_minimum_required(VERSION 3.16)

##########################
# Default compile options
##########################

if (NOT DEFINED LE3_WITH_DEMOS) 
    set (LE3_WITH_DEMOS true) 
endif()

##########################



set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)

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
add_subdirectory(apps)
add_subdirectory(editor)
add_subdirectory(tools)

# Copy the resources directory to the build 
# (NOTE: since we package all resources at build time, this is now obsolete)
# if (WIN32)
# add_custom_target(
#     copy_resources ALL
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#         ${CMAKE_CURRENT_SOURCE_DIR}/resources
#         ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/resources
# )
# else()
# add_custom_target(
#     copy_resources ALL
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#         ${CMAKE_CURRENT_SOURCE_DIR}/resources
#         ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources
# )
# endif()



if (WIN32)
#     # add_custom_target(
#     #     pkg-resources-tgt ALL
#     #     COMMAND 
#     #         ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/pkg-resources.exe ${CMAKE_CURRENT_SOURCE_DIR}/resources ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>

#     #     DEPENDS 
#     #         ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}\\$<CONFIG>\\pkg-resources.exe
#     #         ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}\\$<CONFIG>\\le3.dll
#     # )
#     # add_custom_command(
#     #     TARGET pkg_resources
#     #     POST_BUILD
#     #     COMMAND 
#     #         ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/pkg-resources.exe ${CMAKE_CURRENT_SOURCE_DIR}/resources ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>
#     # )
else()
    add_custom_target(
        pkg-resources-tgt ALL
        COMMAND 
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/pkg-resources ${CMAKE_CURRENT_SOURCE_DIR}/resources ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}

        DEPENDS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/pkg-resources 
    )
endif()