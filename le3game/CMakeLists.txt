if (LE3_WITH_GAME)
    project(le3game)

    ########################################
    # Setup bootstrap macros and files
    ########################################
    set(LE3_GAME_DEFAULT_PROJECT "examples/platformer")
    set(LE3_GAME_DEFAULT_PROJECT_INITIAL_SCENE "bowling.lua")
    set(LE3_GAME_DEFAULT_PROJECT_ABSOLUTE "${CMAKE_SOURCE_DIR}/${LE3_GAME_DEFAULT_PROJECT}")

    set(LE3_GAME_BOOTSTRAP_FILE "bootstrap.lua")
    set(LE3_GAME_BOOTSTRAP_INPATH "${CMAKE_SOURCE_DIR}/${LE3_GAME_BOOTSTRAP_FILE}")
    set(LE3_GAME_BOOTSTRAP_OUTPATH "${CMAKE_SOURCE_DIR}/bin/${LE3_GAME_BOOTSTRAP_FILE}")
    add_compile_definitions(LE3_GAME_BOOTSTRAP_FILE="${LE3_GAME_BOOTSTRAP_FILE}")
    if (EXISTS ${LE3_GAME_BOOTSTRAP_INPATH})
        configure_file(${LE3_GAME_BOOTSTRAP_INPATH} ${LE3_GAME_BOOTSTRAP_OUTPATH}  COPYONLY)
    else()
        set(LE3_GAME_BOOSTRAP_CONTENT "\n\
            LE3GameConfig = {}\n\
            LE3GameConfig.ProjectPath = \"${LE3_GAME_DEFAULT_PROJECT_ABSOLUTE}\"\n\
            LE3GameConfig.InitialScene = \"${LE3_GAME_DEFAULT_PROJECT_INITIAL_SCENE}\"\n\
        ")
        string(REGEX REPLACE "\n[ \t]+" "\n" LE3_GAME_BOOSTRAP_CONTENT ${LE3_GAME_BOOSTRAP_CONTENT}) # Remove leading tabs after every newline
        string(REGEX REPLACE "^\n" "" LE3_GAME_BOOSTRAP_CONTENT ${LE3_GAME_BOOSTRAP_CONTENT}) # Remove the first empty line
        string(REGEX REPLACE "\n$" "" LE3_GAME_BOOSTRAP_CONTENT ${LE3_GAME_BOOSTRAP_CONTENT}) # Remove the last empty line
        file(CONFIGURE OUTPUT ${LE3_GAME_BOOTSTRAP_OUTPATH} CONTENT ${LE3_GAME_BOOSTRAP_CONTENT})
    endif()




    ########################################

    find_package(fmt REQUIRED)
    find_package(GLEW REQUIRED)
    find_package(Lua REQUIRED)
    find_package(glm CONFIG REQUIRED)
    find_package(assimp REQUIRED)
    include_directories(${GLEW_INCLUDE_DIRS} ${LUA_INCLUDE_DIR})
    include_directories(${CMAKE_SOURCE_DIR}/third-party/imgui)
    include_directories(${CMAKE_SOURCE_DIR}/third-party/native_message_box/include)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

    if (NOT DEFINED LUA_LIBRARIES)
        set(LUA_LIBRARIES lua::lua)
    endif()

    # Link against CoreFoundation on macOS, and gtk on Linux, for native_message_box
    if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        find_library(corefoundation_lib CoreFoundation)
        set(frameworks ${corefoundation_lib})
    elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
        find_package(PkgConfig REQUIRED)
        PKG_CHECK_MODULES( GTK REQUIRED gtk+-3.0 )
        INCLUDE_DIRECTORIES(${GTK_INCLUDE_DIRS})
        LINK_DIRECTORIES(${GTK_LIBRARY_DIRS})
        ADD_DEFINITIONS(${GTK_CFLAGS_OTHER})
        link_libraries( ${GTK_LIBRARIES} )
        set(frameworks  ${GTK_LIBRARIES})
    else() # MSVC
        set(frameworks)
        string(APPEND CMAKE_C_FLAGS " /MP$ENV{MSVC_PARALLEL}")
        string(APPEND CMAKE_CXX_FLAGS " /MP$ENV{MSVC_PARALLEL}")
    endif()

    add_executable(${PROJECT_NAME} src/main.cpp)
    target_link_libraries(${PROJECT_NAME} PRIVATE le3 fmt::fmt glm::glm assimp::assimp ${LUA_LIBRARIES} ${frameworks})
    target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
endif()