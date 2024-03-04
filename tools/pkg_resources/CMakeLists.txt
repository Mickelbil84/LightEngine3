project("pkg-resources" VERSION 0.1)

find_package(fmt REQUIRED)
find_package(GLEW REQUIRED)
find_package(Lua REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(assimp REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS} ${LUA_INCLUDE_DIR})

if (NOT DEFINED LUA_LIBRARIES)
    set(LUA_LIBRARIES lua::lua)
endif()

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE le3 fmt::fmt glm::glm assimp::assimp ${LUA_LIBRARIES})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)


if (WIN32)
    add_custom_command(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND 
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/pkg-resources.exe ${PROJECT_SOURCE_DIR}/../../resources ${CMAKE_SOURCE_DIR}/bin/$<CONFIG>
    )
else()
    # add_custom_command(
    #     TARGET ${PROJECT_NAME}
    #     POST_BUILD
    #     COMMAND 
    #         ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/pkg-resources ${CMAKE_SOURCE_DIR}/resources ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    # )
endif()
