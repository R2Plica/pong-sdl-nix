cmake_minimum_required(VERSION 3.25.3)
project(pong-sdl-nix)
set(CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS 20)
set(CMAKE_CXX_COMPILER_ID clang)
set(CMAKE_CXX_COMPILER_VERSION 12.3.0)
find_package(SDL2 REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${imgui_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})
add_executable(pong-sdl-nix main.cpp)


target_link_libraries(
  pong-sdl-nix
  ${SDL2_LIBRARIES}
  glfw
  OpenGL::GL
)
