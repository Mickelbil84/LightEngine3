find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

add_subdirectory(00_playground)
add_subdirectory(01_hello_opengl)
add_subdirectory(02_moving_car)
add_subdirectory(03_racing_shooter)