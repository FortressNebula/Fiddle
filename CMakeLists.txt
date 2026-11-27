cmake_minimum_required(VERSION 3.20)
project(Fiddle C)

set(CMAKE_C_STANDARD 11)
set(
    SOURCES
    src/components/components.c
    src/components/renderables.c
    src/engine.c
    src/graphics/shaders.c
)

find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
# add_library(Fiddle STATIC
#     ${SOURCES}
# )
add_executable(Fiddle
    ~/opengl/libs/glad.c
    main.c
    ${SOURCES}
)

target_include_directories(Fiddle PRIVATE "~/opengl/include")
target_link_directories(Fiddle PRIVATE "~/opengl/libs")

target_link_libraries(Fiddle
    glfw
)