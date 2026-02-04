project(le3 VERSION ${LE3_VERSION})
set(namespace le3)

find_package(fmt REQUIRED)
find_package(Lua REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED)
find_package(assimp REQUIRED)
find_package(Bullet REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(ZLIB REQUIRED)
find_package(cpr REQUIRED)

if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    set(BUILD_SHARED_LIBS TRUE)
    string(APPEND CMAKE_C_FLAGS " /MP$ENV{MSVC_PARALLEL}")
    string(APPEND CMAKE_CXX_FLAGS " /MP$ENV{MSVC_PARALLEL}")
    set(LE3_PLATFROM_SPECIFIC_LIBS "")
elseif(APPLE)
    find_library(COREFOUNDATION_FRAMEWORK CoreFoundation)
    set(LE3_PLATFROM_SPECIFIC_LIBS ${COREFOUNDATION_FRAMEWORK})
elseif(UNIX AND NOT APPLE)
    find_package(PkgConfig REQUIRED)
    pkg_search_module(UUID REQUIRED uuid)
    set(LE3_PLATFROM_SPECIFIC_LIBS ${UUID_LIBRARIES})
else()
    set(LE3_PLATFROM_SPECIFIC_LIBS "")
endif()

include_directories(${LUA_INCLUDE_DIR} ${BULLET_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/../third-party/stb)
include_directories(${PROJECT_SOURCE_DIR}/../third-party/imgui)
include_directories(${PROJECT_SOURCE_DIR}/../third-party/stduuid/include)
include_directories(${PROJECT_SOURCE_DIR}/../third-party/gzip-hpp/include)


add_library(${PROJECT_NAME} SHARED)

if (NOT DEFINED LUA_LIBRARIES)
    set(LUA_LIBRARIES lua::lua)
endif()

set(public_headers
)

target_sources(${PROJECT_NAME} PRIVATE
    src/algorithms/le3_bsp.cpp

    src/core/le3_application.cpp
    src/core/le3_asset_manager.cpp
    src/core/le3_config.cpp
    src/core/le3_dat_archive.cpp
    src/core/le3_dat_filesystem.cpp
    src/core/le3_editor_manager.cpp
    src/core/le3_engine_systems.cpp
    src/core/le3_event_manager.cpp
    src/core/le3_object.cpp
    src/core/le3_scene_manager.cpp
    src/core/le3_scene_root.cpp
    src/core/le3_scene.cpp
    src/core/le3_simple_demo.cpp
    src/core/le3_transform.cpp

    src/graphics/le3_animation.cpp
    src/graphics/le3_camera.cpp
    src/graphics/le3_draw_queue.cpp
    src/graphics/le3_framebuffer.cpp
    src/graphics/le3_geometry.cpp
    src/graphics/le3_light_manager.cpp
    src/graphics/le3_light.cpp
    src/graphics/le3_material.cpp
    src/graphics/le3_model.cpp
    src/graphics/le3_point_cloud.cpp
    src/graphics/le3_primitives.cpp
    src/graphics/le3_shader.cpp
    src/graphics/le3_skeleton.cpp
    src/graphics/le3_sprite.cpp
    src/graphics/le3_texture.cpp
    src/graphics/le3_visual_debug.cpp

    src/networking/le3_network_spinner.cpp
    src/networking/le3_networking.cpp

    src/physics/le3_collider_info.cpp
    src/physics/le3_physics_manager.cpp
    src/physics/le3_physics.cpp

    src/scripting/le3_script_bindings.cpp
    src/scripting/le3_script_object.cpp
    src/scripting/le3_script_system.cpp
    src/scripting/le3_serialization.cpp

    src/gameplay/le3_playerstart.cpp

    src/tools/le3_tool_pkg.cpp

    src/ui/le3_imgui_utils.cpp

    src/utils/le3_assimp.cpp
    src/utils/le3_gizmo.cpp
    src/utils/le3_math_utils.cpp


    src/bindings/le3_binding_imgui.cpp
    src/bindings/le3_binding_scene.cpp
    src/bindings/le3_binding_shader.cpp
    src/bindings/le3_binding_texture.cpp
    src/bindings/le3_binding_material.cpp
    src/bindings/le3_binding_geometry.cpp
    src/bindings/le3_binding_object.cpp
    src/bindings/le3_binding_transform.cpp
    src/bindings/le3_binding_physics_component.cpp
    src/bindings/le3_binding_scene_root.cpp
    src/bindings/le3_binding_model.cpp
    src/bindings/le3_binding_input.cpp
    src/bindings/le3_binding_drawable_object.cpp
    src/bindings/le3_binding_camera.cpp
    src/bindings/le3_binding_primitives.cpp
    src/bindings/le3_binding_light.cpp
    src/bindings/le3_binding_engine_config.cpp
    src/bindings/le3_binding_engine_state.cpp
    src/bindings/le3_binding_asset_manager.cpp
    src/bindings/le3_binding_script_object.cpp
    src/bindings/le3_binding_visual_debug.cpp
    src/bindings/le3_binding_point_cloud.cpp
    src/bindings/le3_binding_sprite.cpp
    src/bindings/le3_binding_playerstart.cpp
    src/bindings/le3_binding_event_manager.cpp

    ${PROJECT_SOURCE_DIR}/../third-party/imgui/imgui.cpp
    ${PROJECT_SOURCE_DIR}/../third-party/imgui/imgui_demo.cpp
    ${PROJECT_SOURCE_DIR}/../third-party/imgui/imgui_draw.cpp
    ${PROJECT_SOURCE_DIR}/../third-party/imgui/imgui_tables.cpp
    ${PROJECT_SOURCE_DIR}/../third-party/imgui/imgui_widgets.cpp
    ${PROJECT_SOURCE_DIR}/../third-party/imgui/misc/cpp/imgui_stdlib.cpp
    ${PROJECT_SOURCE_DIR}/../third-party/imgui/backends/imgui_impl_sdl2.cpp
    ${PROJECT_SOURCE_DIR}/../third-party/imgui/backends/imgui_impl_opengl3.cpp
)
target_include_directories(${PROJECT_NAME} PUBLIC 
    # ${PROJECT_SOURCE_DIR}/include
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/le3>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_link_libraries(${PROJECT_NAME} PRIVATE 
    fmt::fmt cpr::cpr SDL2::SDL2 GLEW::GLEW glm::glm assimp::assimp 
    ${LUA_LIBRARIES} ${ZLIB_LIBRARIES} ${BULLET_LIBRARIES} ${LE3_PLATFROM_SPECIFIC_LIBS})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

# Auto generate lua bindings
add_custom_target(
    gen_annotations ALL
    COMMAND python ${PROJECT_SOURCE_DIR}/../tools/gen_annotations/gen_annotations.py ${CMAKE_CURRENT_SOURCE_DIR}/annotations.lua ${CMAKE_CURRENT_SOURCE_DIR}/src/bindings
    BYPRODUCTS annotations.lua
    COMMENT "Auto generate lua bindings"
)
add_dependencies(${PROJECT_NAME} gen_annotations)


#############
# Installer
#############

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    EXPORT "${PROJECT_NAME}Targets"
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# generate and install export file
install(EXPORT "${PROJECT_NAME}Targets"
    FILE "${PROJECT_NAME}Targets.cmake"
    NAMESPACE ${namespace}::
    DESTINATION cmake
)

include(CMakePackageConfigHelpers)

# generate the version file for the config file
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION "${version}"
    COMPATIBILITY AnyNewerVersion
)
# create config file
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION cmake
)
# install config files
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION cmake
)