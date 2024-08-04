if (LE3_WITH_DEMOS)
    project(00-playground)

    find_package(fmt REQUIRED)
    find_package(Lua REQUIRED)
    find_package(assimp REQUIRED)
    find_package(glm CONFIG REQUIRED)

    include_directories(
        ${LUA_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS}
    )

    if (NOT DEFINED LUA_LIBRARIES)
        set(LUA_LIBRARIES lua::lua)
    endif()

    add_executable(${PROJECT_NAME} main.cpp)
    target_link_libraries(${PROJECT_NAME} PRIVATE le3 fmt::fmt ${LUA_LIBRARIES} assimp::assimp glm::glm)
    target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
endif()