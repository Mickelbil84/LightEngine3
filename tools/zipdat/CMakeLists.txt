project("zipdat" VERSION 0.1)

find_package(fmt REQUIRED)
find_package(cxxopts REQUIRED)
find_package(ZLIB REQUIRED)

# Build miniz as a static library
set(MINIZ_SOURCE_DIR ${PROJECT_SOURCE_DIR}/../../third-party/miniz)
add_library(miniz_static STATIC
    ${MINIZ_SOURCE_DIR}/miniz.c
    ${MINIZ_SOURCE_DIR}/miniz_zip.c
    ${MINIZ_SOURCE_DIR}/miniz_tinfl.c
    ${MINIZ_SOURCE_DIR}/miniz_tdef.c
)
target_include_directories(miniz_static PUBLIC
    ${MINIZ_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)
target_compile_definitions(miniz_static PUBLIC MINIZ_STATIC_DEFINE)

# Generate export header for miniz
include(GenerateExportHeader)
generate_export_header(miniz_static BASE_NAME miniz EXPORT_FILE_NAME ${MINIZ_SOURCE_DIR}/miniz_export.h)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE le3 fmt::fmt cxxopts::cxxopts miniz_static ${ZLIB_LIBRARIES})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
