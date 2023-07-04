cmake_minimum_required(VERSION 3.0)
project(VehicularBlast)

set(VEHICULAR_BLAST_SOURCES
    src/gfx/Mesh.cpp
    src/gfx/shader/Shader.cpp
    src/gfx/shader/ShaderProgram.cpp
    src/gui/Window.cpp
    src/io/Keyboard.cpp
    src/io/MeshBank.cpp
    src/io/MeshFile.cpp
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glm)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glad/cmake)
glad_add_library(glad STATIC API gl:core=3.3)

set(GLFW_BUILD_DOCS OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_EXAMPLES OFF)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glfw)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/cgltf)

set(DRACO_GLTF_BITSTREAM ON CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/draco)
get_target_property(DRACO_INCLUDE_DIRECTORIES draco INCLUDE_DIRECTORIES)

add_executable(VehicularBlast src/main.cpp ${VEHICULAR_BLAST_SOURCES})
set_target_properties(VehicularBlast PROPERTIES C_STANDARD 11 CXX_STANDARD 11)

target_link_libraries(VehicularBlast glm glad glfw cgltf draco)
target_include_directories(VehicularBlast PRIVATE ${DRACO_INCLUDE_DIRECTORIES})
