cmake_minimum_required(VERSION 3.10)
project(penance LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
find_package(SDL2 REQUIRED)
find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)

#imgui
add_library(imgui STATIC
    external/imgui/imgui.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_tables.cpp
    external/imgui/imgui_widgets.cpp
    external/imgui/backends/imgui_impl_sdl2.cpp
    external/imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
    external/imgui
    external/imgui/backends
)

target_link_libraries(imgui PUBLIC
    ${SDL2_LIBRARIES}
    OpenGL::GL
)

# Executable
add_executable(penance
    src/main.cpp
    src/shader.cpp
    src/mesh.cpp
    src/transform.cpp
    src/glad.c
)

# Include paths
target_include_directories(penance PRIVATE
    include
    ${SDL2_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(penance PRIVATE
    glm::glm
    ${SDL2_LIBRARIES}
    OpenGL::GL
    imgui
)

