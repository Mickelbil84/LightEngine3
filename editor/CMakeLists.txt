project(le3editor)

find_package(fmt REQUIRED)
find_package(GLEW REQUIRED)
find_package(Lua REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(assimp REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS} ${LUA_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/third-party/imgui)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

if (NOT DEFINED LUA_LIBRARIES)
    set(LUA_LIBRARIES lua::lua)
endif()

add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/le3ed_logic.cpp
    src/le3ed_editor_systems.cpp

    src/components/le3ed_gui.cpp
    src/components/le3ed_scenes.cpp
    src/components/le3ed_hotkeys.cpp

    src/widgets/le3ed_toolbar.cpp
    src/widgets/le3ed_toolbox.cpp
    src/widgets/le3ed_tab_scene.cpp
    src/widgets/le3ed_tab_assets.cpp
    src/widgets/le3ed_tab_content.cpp
    src/widgets/le3ed_sidepanel_top.cpp
    src/widgets/le3ed_toolbar_button.cpp
    src/widgets/le3ed_properties_panel.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE le3 fmt::fmt glm::glm assimp::assimp ${LUA_LIBRARIES})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
