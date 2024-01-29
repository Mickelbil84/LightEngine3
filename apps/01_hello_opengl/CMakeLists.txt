project(01-hello-opengl)

find_package(GLEW REQUIRED)
find_package(Lua REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS} ${LUA_INCLUDE_DIR})

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE le3)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)