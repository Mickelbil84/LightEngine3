project(01-hello-opengl)

find_package(GLEW REQUIRED)
find_package(glm CONFIG REQUIRED)

include_directories(${GLEW_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE le3 glm::glm)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)