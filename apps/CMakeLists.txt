find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

add_subdirectory(00_lua_playground)
add_subdirectory(01_hello_opengl)