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

if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    set(BUILD_SHARED_LIBS TRUE)
endif()

include_directories(${LUA_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/../third-party/stb)
include_directories(${PROJECT_SOURCE_DIR}/../third-party/imgui)
include_directories(${PROJECT_SOURCE_DIR}/../third-party/gzip-hpp/include)


add_library(${PROJECT_NAME} SHARED)

if (NOT DEFINED LUA_LIBRARIES)
    set(LUA_LIBRARIES lua::lua)
endif()

set(public_headers
)

target_sources(${PROJECT_NAME} PRIVATE
    src/le3_application.cpp
    src/le3_shader.cpp
    src/le3_scene.cpp
    src/le3_geometry.cpp
    src/le3_material.cpp
    src/le3_model.cpp
    src/le3_transform.cpp
    src/le3_primitives.cpp
    src/le3_camera.cpp
    src/le3_object.cpp
    src/le3_light.cpp
    src/le3_scene_root.cpp
    src/le3_draw_queue.cpp
    src/le3_assimp.cpp
    src/le3_texture.cpp
    src/le3_dat_archive.cpp
    src/le3_dat_filesystem.cpp
    src/le3_light_manager.cpp
    src/le3_framebuffer.cpp
    src/le3_imgui_utils.cpp
    src/le3_asset_manager.cpp
    src/le3_visual_debug.cpp
    src/le3_skeleton.cpp
    src/le3_animation.cpp
    src/le3_script_object.cpp
    src/le3_engine_systems.cpp
    src/le3_point_cloud.cpp
    src/le3_bsp.cpp
    src/le3_simple_demo.cpp
    src/le3_gizmo.cpp
    src/le3_scene_manager.cpp
    src/le3_math_utils.cpp

    src/le3_script_system.cpp
    src/le3_script_bindings.cpp
    src/bindings/le3_binding_scene.cpp
    src/bindings/le3_binding_shader.cpp
    src/bindings/le3_binding_texture.cpp
    src/bindings/le3_binding_material.cpp
    src/bindings/le3_binding_geometry.cpp
    src/bindings/le3_binding_object.cpp
    src/bindings/le3_binding_transform.cpp
    src/bindings/le3_binding_scene_root.cpp
    src/bindings/le3_binding_model.cpp
    src/bindings/le3_binding_input.cpp
    src/bindings/le3_binding_drawable_object.cpp
    src/bindings/le3_binding_camera.cpp
    src/bindings/le3_binding_primitives.cpp
    src/bindings/le3_binding_light.cpp
    src/bindings/le3_binding_engine_config.cpp
    src/bindings/le3_binding_asset_manager.cpp
    src/bindings/le3_binding_script_object.cpp
    src/bindings/le3_binding_visual_debug.cpp
    src/bindings/le3_binding_point_cloud.cpp

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
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt SDL2::SDL2 GLEW::GLEW glm::glm assimp::assimp ${LUA_LIBRARIES} ${ZLIB_LIBRARIES})
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