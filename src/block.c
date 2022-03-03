#include "block.h"
#include <cglm/cglm.h>
#include <cglm/vec3.h>
#include <stdio.h>
#include <GLFW/glfw3.h>
#include "shader.h"

static Model* model = NULL;

Block* block_create() {
    Block* block = malloc(sizeof(Block));
    glm_vec3_zero(block->position);
    return block;
}

void block_render(Block* block, int shader) {
    mat4 model_mat;
    glm_mat4_identity(model_mat);
    glm_translate(model_mat, block->position);
    shader_bind_mat4(shader, model_mat, "model");
    model_render(block_model());
}

static void initialize_model() {
    float vertices[] = {
        0.5f,  0.5f, 0.5f,  // 0 top right
        0.5f, -0.5f, 0.5f,  // 1 bottom right
        -0.5f, -0.5f, 0.5f,  // 2 bottom left
        -0.5f,  0.5f, 0.5f,   // 3 top left
                              //
         0.5f,  0.5f, -0.5f,  // 4 top right
        0.5f, -0.5f, -0.5f,  // 5 bottom right
        -0.5f, -0.5f, -0.5f,  // 6 bottom left
        -0.5f,  0.5f, -0.5f   // 7 top left

    };
    unsigned int indices[] = {
        3, 0, 1,
        2, 3, 1,
        4, 7, 5,
        6, 5, 7,
        0, 4, 5,
        0, 1, 5,
        3, 2, 6,
        6, 7, 3,
        0, 3, 4,
        7, 3, 4,
        1, 2, 6,
        5, 6, 1
    };

    model = model_create(vertices, sizeof(vertices), indices, sizeof(indices));
}

Model* block_model() {
    if (model == NULL) {
        initialize_model();
    }
    return model;
}
