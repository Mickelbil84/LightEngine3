if (LE3_WITH_EDITOR)
    project(le3editor)

    find_package(fmt REQUIRED)
    find_package(GLEW REQUIRED)
    find_package(Lua REQUIRED)
    find_package(glm CONFIG REQUIRED)
    find_package(assimp REQUIRED)
    include_directories(${GLEW_INCLUDE_DIRS} ${LUA_INCLUDE_DIR})
    include_directories(${CMAKE_SOURCE_DIR}/third-party/imgui)
    include_directories(${CMAKE_SOURCE_DIR}/third-party/imgui-filebrowser)
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


    add_executable(${PROJECT_NAME} 
        src/main.cpp
        src/le3ed_cache.cpp
        src/le3ed_logic.cpp
        src/le3ed_project.cpp
        src/le3ed_editor_systems.cpp
        src/le3ed_project_browser.cpp

        src/components/le3ed_gui.cpp
        src/components/le3ed_scenes.cpp
        src/components/le3ed_hotkeys.cpp
        src/components/le3ed_scripts.cpp
        src/components/le3ed_wintitle.cpp

        src/widgets/le3ed_popup.cpp
        src/widgets/le3ed_toolbar.cpp
        src/widgets/le3ed_toolbox.cpp
        src/widgets/le3ed_tab_scene.cpp
        src/widgets/le3ed_tab_assets.cpp
        src/widgets/le3ed_tab_content.cpp
        src/widgets/le3ed_sidepanel_top.cpp
        src/widgets/le3ed_settings_panel.cpp
        src/widgets/le3ed_toolbar_button.cpp
        src/widgets/le3ed_properties_panel.cpp

        src/widgets/popups/le3ed_pop_add_mesh.cpp
        src/widgets/popups/le3ed_pop_add_shader.cpp
        src/widgets/popups/le3ed_pop_add_texture.cpp
        src/widgets/popups/le3ed_pop_add_material.cpp
        src/widgets/popups/le3ed_pop_load_scene.cpp
        src/widgets/popups/le3ed_pop_save_scene.cpp

        src/commands/le3ed_com_add_mesh.cpp
        src/commands/le3ed_com_delete_mesh.cpp
        src/commands/le3ed_com_add_shader.cpp
        src/commands/le3ed_com_delete_shader.cpp
        src/commands/le3ed_com_add_texture.cpp
        src/commands/le3ed_com_delete_texture.cpp
        src/commands/le3ed_com_add_material.cpp
        src/commands/le3ed_com_delete_material.cpp
        src/commands/le3ed_com_reparent.cpp
        src/commands/le3ed_com_duplicate.cpp
        src/commands/le3ed_com_delete_objects.cpp
        src/commands/le3ed_com_property_change.cpp
    )
    target_link_libraries(${PROJECT_NAME} PRIVATE le3 fmt::fmt glm::glm assimp::assimp ${LUA_LIBRARIES} ${frameworks})
    target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
endif()