cmake_minimum_required(VERSION 3.0)
project(VehicularBlast)

set(VEHICULAR_BLAST_SOURCES
    src/gui/Window.cpp
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glad/cmake)
glad_add_library(glad STATIC API gl:core=3.3)

set(GLFW_BUILD_DOCS OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_EXAMPLES OFF)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glfw)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/cgltf)

add_executable(VehicularBlast src/main.cpp ${VEHICULAR_BLAST_SOURCES})
target_link_libraries(VehicularBlast glad glfw cgltf)
