cmake_minimum_required(VERSION 3.10)
project(Game_programming)

set(CMAKE_CXX_STANDARD 17)

add_executable(Game_programming main.cpp Game.cpp Game.h Actor.cpp Actor.h Math.h Component.cpp Component.h Math.cpp VertexArray.cpp VertexArray.h Shader.cpp Shader.h MoveComponent.cpp MoveComponent.h Mesh.cpp Mesh.h Texture.cpp Texture.h)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

find_package(GLEW 2.1 REQUIRED)
include_directories($(GLEW_INCLUDE_DIRS))

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} GLU GL GLEW /usr/local/lib/libSOIL.a)