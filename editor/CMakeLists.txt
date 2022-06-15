cmake_minimum_required(VERSION 3.11-3.25)

project(editor)

find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)
find_package(wxWidgets REQUIRED COMPONENTS net core base aui propgrid gl)
include_directories(${SDL2_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS})
include(${wxWidgets_USE_FILE})

link_libraries(${GLEW_LIBRARIES})

add_executable(
    editor
    ui/noname.cpp
    src/editor_main.cpp
    src/editor_glpanel.cpp
    src/editor.cpp
)
target_include_directories(editor PUBLIC ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/ui)
target_link_libraries(editor PRIVATE le3 GLEW::glew ${wxWidgets_LIBRARIES})
target_compile_features(editor PUBLIC cxx_std_20)
set_target_properties(editor PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)