#include "line.h"
#include "cglm/types.h"
#include <stdlib.h>
#include <glad/glad.h>
#include "shader.h"

Line* line_create(vec3* start, vec3* end) {
    float vertices[] = {
        *start[0], *start[1], *start[2],
        *end[0], *end[1], *end[2]
    };
    Line* line = malloc(sizeof(Line));

    glGenVertexArrays(1, &line->vao);
    glGenBuffers(1, &line->vbo);

    glBindVertexArray(line->vao);
    glBindBuffer(GL_ARRAY_BUFFER, line->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return line;
}


void line_render(Line* line, int shader) {
    mat4 model_mat;
    glm_mat4_identity(model_mat);
    shader_bind_mat4(shader, model_mat, "model");
    glUseProgram(shader);
    glBindVertexArray(line->vao);
    glDrawArrays(GL_LINES, 0, 2);
}
