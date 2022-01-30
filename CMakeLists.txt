cmake_minimum_required(VERSION 3.10)

# set the project name
project(Tutorial)
add_executable(Tutorial src/glad.c src/main.c src/window.c src/shader.c src/camera.c)

target_include_directories(Tutorial PRIVATE "include")
target_link_libraries(Tutorial glfw dl m)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/fragment.shader
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/vertex.shader
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

# add the executable
