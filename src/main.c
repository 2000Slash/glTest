#include "window.h"
#include "shader.h"
#include <GL/glext.h>
#include <GLFW/glfw3.h>
#include <cglm/affine.h>
#include <cglm/types.h>
#include <cglm/mat4.h>
#include <cglm/vec3.h>
#include <cglm/cglm.h>
#include <cglm/cam.h>
#include "camera.h"

int main(void)
{
    GLFWwindow* window = initialize_window();

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

    int vao;
    glGenVertexArrays(1, (GLuint*)&vao);
    glBindVertexArray(vao);

    int vbo, ebo;
    glGenBuffers(1,  (GLuint*)&vbo);
    glGenBuffers(1,  (GLuint*)&ebo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0); 
    
    int program = shader_create();

    Camera* cam = camera_create();
    vec3 cam_pos = {-5.f, 0.f, 0.f};
    printf("Cam target: %f, %f, %f\n", cam->target[0], cam->target[1], cam->target[2]);
    glm_vec3_copy(cam_pos, cam->pos);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor((float)glfwGetTime(), 0.3f, 0.3f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(program);

        mat4 model;
        glm_mat4_identity(model);
        vec3 rot = {0.5f, 1.f, 0};
        glm_rotate(model, (float)glfwGetTime() * glm_rad(50.f), rot);

        mat4* view = camera_view(cam);

        mat4 projection;
        glm_perspective(glm_rad(45.0f), 800.f / 600.f, 0.1f, 100.f, projection);

        shader_bind_mat4(program, model, "model");
        shader_bind_mat4(program, *view, "view");
        shader_bind_mat4(program, projection, "projection");

        free(view);
        glBindVertexArray(vao);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        GLenum err;
        while((err = glGetError()) != GL_NO_ERROR)
        {
            printf("Error: %d\n", err);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    free(cam);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
