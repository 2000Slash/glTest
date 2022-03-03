cmake_minimum_required(VERSION 3.10)

# set the project name
project(glTest)
add_executable(glTest src/glad.c src/main.c src/window.c src/shader.c src/camera.c src/model.c src/block.c src/pane.c)

target_include_directories(glTest PRIVATE "include")
target_link_libraries(glTest glfw dl m)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/shader/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)


# add the executable
