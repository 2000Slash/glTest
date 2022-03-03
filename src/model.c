#include "model.h"
#include <stdlib.h>
#include <glad/glad.h>


Model* model_create(float vertices[], int nvertices, unsigned int indices[], int nindices) {
    Model* model = malloc(sizeof(Model));
    glGenVertexArrays(1, (&model->vao));
    glGenBuffers(1, (&model->vbo));
    glGenBuffers(1, (&model->ebo));

    model_bind(model);

    glBufferData(GL_ARRAY_BUFFER, nvertices, vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, nindices, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    model->nvertices = nvertices;

    return model;
}

void model_free(Model* model) {
    glDeleteVertexArrays(1, &(model->vao));
    glDeleteBuffers(1, &(model->vbo));
    glDeleteBuffers(1, &(model->ebo));
}

void model_bind(Model* model) {
    glBindVertexArray(model->vao);
    glBindBuffer(GL_ARRAY_BUFFER, model->vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->ebo);
}

void model_render(Model* model) {
    model_bind(model);
    glDrawElements(GL_TRIANGLES, model->nvertices, GL_UNSIGNED_INT, 0);
}
