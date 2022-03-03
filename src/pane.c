#include "pane.h"
#include <cglm/cglm.h>
#include <cglm/vec3.h>
#include <stdio.h>
#include <GLFW/glfw3.h>
#include "shader.h"

static Model* model = NULL;

Pane* pane_create() {
    Pane* pane = malloc(sizeof(Pane));
    glm_vec3_zero(pane->position);
    return pane;
}

void pane_render(Pane* pane, int shader) {
    mat4 model_mat;
    glm_mat4_identity(model_mat);
    glm_translate(model_mat, pane->position);
    shader_bind_mat4(shader, model_mat, "model");
    model_render(pane_model());
}

static void initialize_model() {
    float vertices[] = {
        0.5f,  0.5f, 0,  // 0 top right
        0.5f, -0.5f, 0,  // 1 bottom right
        -0.5f, -0.5f, 0, // 2 bottom left
        -0.5f,  0.5f, 0  // 3 top left
    };
    unsigned int indices[] = {
        3, 0, 1,
        2, 3, 1
    };

    model = model_create(vertices, sizeof(vertices), indices, sizeof(indices));
}

Model* pane_model() {
    if (model == NULL) {
        initialize_model();
    }
    return model;
}
