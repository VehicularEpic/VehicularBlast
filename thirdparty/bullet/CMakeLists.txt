set(BUILD_EXTRAS OFF CACHE BOOL "" FORCE)
set(BUILD_CPU_DEMOS OFF CACHE BOOL "" FORCE)
set(BUILD_OPENGL3_DEMOS OFF CACHE BOOL "" FORCE)
set(BUILD_BULLET2_DEMOS OFF CACHE BOOL "" FORCE)
set(BUILD_UNIT_TESTS OFF CACHE BOOL "" FORCE)
set(BUILD_BULLET3 OFF CACHE BOOL "" FORCE)

set(USE_MSVC_RUNTIME_LIBRARY_DLL ON CACHE BOOL "Use MSVC dynamic linking for Bullet" FORCE)
add_subdirectory(bullet3)

set(BULLET_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bullet3/src)

add_library(Bullet INTERFACE)
target_include_directories(Bullet INTERFACE ${BULLET_INCLUDE_DIR})
target_link_libraries(Bullet INTERFACE BulletCollision BulletDynamics LinearMath)
