cmake_minimum_required(VERSION 3.0)
project(VehicularBlast)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glad/cmake)
glad_add_library(glad STATIC API gl:core=3.3)

set(GLFW_BUILD_DOCS OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_EXAMPLES OFF)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glfw)

add_executable(VehicularBlast src/main.cpp)
target_link_libraries(VehicularBlast glad glfw)
