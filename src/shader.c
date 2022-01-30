#include "shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

int compileShader(GLenum shader_type, char* shader_file) {
    int shader = glCreateShader(shader_type);

    FILE* shader_source = fopen(shader_file, "r");
    fseek(shader_source, 0, SEEK_END);
    int size = ftell(shader_source)+1;
    rewind(shader_source);

    char* shader_source_string = malloc(size);
    fread(shader_source_string, size-1, 1, shader_source);
    shader_source_string[size-1] = '\0';

    glShaderSource(shader, 1, &shader_source_string, NULL);
    glCompileShader(shader);
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        printf("Error compiling shader: %s\n %s\n", shader_file, infoLog);
    }

    fclose(shader_source);
    free(shader_source_string);

    return shader;
}

void shader_bind_mat4(int program, mat4 mat, char* name) {
    glUseProgram(program);
    unsigned int transformLoc = glGetUniformLocation(program, name);
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, mat);

}

int shader_create() {
    int vertex = compileShader( GL_VERTEX_SHADER, "vertex.shader");
    int fragment = compileShader(GL_FRAGMENT_SHADER, "fragment.shader");

    int program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
    }
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    return program;
}
