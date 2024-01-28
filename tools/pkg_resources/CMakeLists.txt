project("pkg-resources" VERSION 0.1)

find_package(fmt REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${GLEW_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE le3 fmt::fmt)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

