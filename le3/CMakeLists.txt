cmake_minimum_required(VERSION 3.11-3.25)

project(le3)

find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

add_library(
    le3 
    src/le3_application.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(le3 PRIVATE ${SDL2_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})
target_compile_features(le3 PUBLIC cxx_std_20)