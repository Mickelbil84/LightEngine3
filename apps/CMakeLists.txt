cmake_minimum_required(VERSION 3.11-3.25)

project(main)

find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)
find_package(Bullet REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${BULLET_INCLUDE_DIRS})
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
target_link_libraries(01_hello_opengl PRIVATE le3 GLEW::glew ${BULLET_LIBRARIES})
target_compile_features(01_hello_opengl PUBLIC cxx_std_20)

add_executable(
    02_moving_car
    demos/02_moving_car.cpp
)
target_link_libraries(02_moving_car PRIVATE le3 GLEW::glew ${BULLET_LIBRARIES})
target_compile_features(02_moving_car PUBLIC cxx_std_20)

add_executable(
    03_ps1_shooter
    demos/03_ps1_shooter.cpp
)
target_link_libraries(03_ps1_shooter PRIVATE le3 GLEW::glew ${BULLET_LIBRARIES})
target_compile_features(03_ps1_shooter PUBLIC cxx_std_20)

add_executable(
    04_lighting
    demos/04_lighting.cpp
)
target_link_libraries(04_lighting PRIVATE le3 GLEW::glew ${BULLET_LIBRARIES})
target_compile_features(04_lighting PUBLIC cxx_std_20)