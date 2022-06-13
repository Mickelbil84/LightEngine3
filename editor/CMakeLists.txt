cmake_minimum_required(VERSION 3.11-3.25)

project(main)

find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)
find_package(wxWidgets REQUIRED COMPONENTS net core base)
include_directories(${SDL2_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS})
include(${wxWidgets_USE_FILE})

link_libraries(${GLEW_LIBRARIES})

add_executable(
    editor
    editor.cpp
    noname.cpp
)
target_link_libraries(editor PRIVATE le3 GLEW::glew ${wxWidgets_LIBRARIES})
target_compile_features(editor PUBLIC cxx_std_20)
set_target_properties(editor PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)