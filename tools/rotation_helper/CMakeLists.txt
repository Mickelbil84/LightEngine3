project("rotation-helper" VERSION 0.1)

find_package(fmt REQUIRED)
find_package(GLEW REQUIRED)
find_package(cxxopts REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(assimp REQUIRED)
find_package(Lua REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS} ${LUA_INCLUDE_DIR})

if (NOT DEFINED LUA_LIBRARIES)
    set(LUA_LIBRARIES lua::lua)
endif()

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE le3 fmt::fmt glm::glm assimp::assimp cxxopts::cxxopts ${LUA_LIBRARIES})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

