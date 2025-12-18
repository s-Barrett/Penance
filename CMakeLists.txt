cmake_minimum_required(VERSION 3.10)
project(penance)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} include)

add_executable(penance
    src/main.cpp
    src/shader.cpp
    src/mesh.cpp
    src/glad.c
)

target_link_libraries(penance ${SDL2_LIBRARIES} GL)

