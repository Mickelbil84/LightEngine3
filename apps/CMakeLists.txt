cmake_minimum_required(VERSION 3.11-3.25)

project(main)

find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})

add_executable(
    main
    main.cpp
)
target_link_libraries(main PRIVATE le3 GLEW::glew)
target_compile_features(main PUBLIC cxx_std_20)

add_executable(
    01_hello_opengl
    demos/01_hello_opengl.cpp
)
target_link_libraries(01_hello_opengl PRIVATE le3 GLEW::glew)
target_compile_features(01_hello_opengl PUBLIC cxx_std_20)

add_executable(
    02_moving_car
    demos/02_moving_car.cpp
)
target_link_libraries(02_moving_car PRIVATE le3 GLEW::glew)
target_compile_features(02_moving_car PUBLIC cxx_std_20)