cmake_minimum_required(VERSION 3.0)
project(VehicularBlast)

set(VEHICULAR_BLAST_SOURCES
    src/engine/Entity.cpp
    src/engine/EntityRenderer.cpp
    src/engine/Game.cpp
    src/engine/MainMenu.cpp
    src/engine/Map.cpp
    src/engine/MapSelection.cpp
    src/engine/SkyboxRenderer.cpp
    src/engine/VehicleSelection.cpp
    src/engine/World.cpp
    src/gfx/Mesh.cpp
    src/gfx/Rect.cpp
    src/gfx/Shader.cpp
    src/gfx/ShaderProgram.cpp
    src/gui/Window.cpp
    src/io/Keyboard.cpp
    src/io/MeshBank.cpp
    src/io/MeshFile.cpp
    src/pbf/map_pbf.c
)

add_subdirectory(thirdparty/bullet)
add_subdirectory(thirdparty/draco)
add_subdirectory(thirdparty/glad)
add_subdirectory(thirdparty/glfw)
add_subdirectory(thirdparty/glm)
add_subdirectory(thirdparty/gltfsdk)
add_subdirectory(thirdparty/pbtools)

add_executable(VehicularBlast src/main.cpp ${VEHICULAR_BLAST_SOURCES})
set_target_properties(VehicularBlast PROPERTIES C_STANDARD 11 CXX_STANDARD 11)

target_include_directories(VehicularBlast PRIVATE include)
target_link_libraries(VehicularBlast glm glad glfw gltfsdk draco pbtools BulletCollision BulletDynamics LinearMath)
