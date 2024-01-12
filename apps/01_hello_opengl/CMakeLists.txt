project(01-hello-opengl)

include_directories(${CMAKE_SOURCE_DIR}/le3/include)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE le3)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)