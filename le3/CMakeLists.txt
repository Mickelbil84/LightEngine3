cmake_minimum_required(VERSION 3.11-3.25)

project(le3)

find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(Bullet REQUIRED)
find_package(Cereal REQUIRED)
include_directories(
    ${SDL2_INCLUDE_DIRS} 
    ${GLEW_INCLUDE_DIRS} 
    ${GLM_INCLUDE_DIRS} 
    ${ASSIMP_INCLUDE_DIRS} 
    ${BULLET_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/../thirdparty/include)

add_library(
    le3 
    src/le3_application.cpp
    src/le3_shader.cpp
    src/le3_print.cpp
    src/le3_vertex.cpp
    src/le3_mesh.cpp
    src/le3_primitives.cpp
    src/le3_object.cpp
    src/le3_camera.cpp
    src/le3_texture.cpp
    src/le3_material.cpp
    src/le3_scene_root.cpp
    src/le3_static_mesh.cpp
    src/le3_asset_manager.cpp
    src/le3_scene_manager.cpp
    src/le3_physics.cpp
    src/le3_visual_debug.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(
    le3 PRIVATE 
    ${SDL2_LIBRARIES} 
    ${GLEW_LIBRARIES} 
    ${OPENGL_LIBRARIES} 
    ${ASSIMP_LIBRARIES} 
    ${BULLET_LIBRARIES} 
    GLEW::glew assimp::assimp
    PUBLIC
    cereal::cereal)
target_compile_features(le3 PUBLIC cxx_std_20)