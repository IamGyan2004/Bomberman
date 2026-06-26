cmake_minimum_required(VERSION 3.16)
project(Bomberman CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SDL2 REQUIRED COMPONENTS SDL2)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(Bomberman
    src/main.cpp
    src/game.cpp
    src/game.h
    src/renderer.cpp
    src/renderer.h
    src/level.cpp
    src/level.h
)

target_link_libraries(Bomberman PRIVATE ${SDL2_LIBRARIES})

target_compile_definitions(Bomberman PRIVATE USE_SDL2)
