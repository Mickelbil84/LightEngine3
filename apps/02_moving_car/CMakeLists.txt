project(02-moving-car)

find_package(fmt REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE le3 fmt::fmt)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)