project(le3 VERSION ${LE3_VERSION})
set(namespace le3)

find_package(fmt REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED)
find_package(assimp REQUIRED)
find_package(Bullet REQUIRED)
find_package(glm CONFIG REQUIRED)

if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    set(BUILD_SHARED_LIBS TRUE)
endif()

include_directories(${CMAKE_SOURCE_DIR}/third-party/stb)
include_directories(${CMAKE_SOURCE_DIR}/third-party/imgui)

add_library(${PROJECT_NAME} SHARED)

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
    src/le3_scene_root.cpp
    src/le3_draw_queue.cpp

    ${CMAKE_SOURCE_DIR}/third-party/imgui/imgui.cpp
    ${CMAKE_SOURCE_DIR}/third-party/imgui/imgui_demo.cpp
    ${CMAKE_SOURCE_DIR}/third-party/imgui/imgui_draw.cpp
    ${CMAKE_SOURCE_DIR}/third-party/imgui/imgui_tables.cpp
    ${CMAKE_SOURCE_DIR}/third-party/imgui/imgui_widgets.cpp
    ${CMAKE_SOURCE_DIR}/third-party/imgui/misc/cpp/imgui_stdlib.cpp
    ${CMAKE_SOURCE_DIR}/third-party/imgui/backends/imgui_impl_sdl2.cpp
    ${CMAKE_SOURCE_DIR}/third-party/imgui/backends/imgui_impl_opengl3.cpp
)
target_include_directories(${PROJECT_NAME} PUBLIC 
    # ${PROJECT_SOURCE_DIR}/include
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt SDL2::SDL2 GLEW::GLEW glm::glm)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)


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