#include "window.h"
#include "shader.h"
#include <GL/glext.h>
#include <GLFW/glfw3.h>
#include <cglm/affine.h>
#include <cglm/types.h>
#include <cglm/mat4.h>
#include <cglm/vec3.h>
/*#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>*/
#include <cglm/cglm.h>
#include <cglm/cam.h>
#include "camera.h"

int main(void)
{
    GLFWwindow* window = initialize_window();

    /* Create a windowed mode window and its OpenGL context */


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
        0, 1, 5
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
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 
    
    int program = shader_create();

    Camera* cam = camera_create();
    vec3 cam_pos = {-3.f, 0.f, 0.f};
    glm_vec3_copy(cam_pos, cam->pos);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(program);

        /*glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::scale(trans, glm::vec3(1.5, 1.5, 1.5));
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0, 1.0, 0.0));*/

        /*vec3 scale = {1.5f, 1.5f, 1.5f};
        vec3 rotate = {0.f, 1.0f, 0.f};
        mat4 trans;
        glm_mat4_identity(trans);
        glm_scale(trans, scale);
        glm_rotate(trans, (float)glfwGetTime(), rotate);*/

        mat4 model;
        glm_mat4_identity(model);
        vec3 rot = {0.5f, 1.f, 0};
        glm_rotate(model, (float)glfwGetTime() * glm_rad(50.f), rot);

        //vec3 pos = cam->pos;

        mat4* view = camera_view(cam);

        mat4 projection;
        glm_perspective(glm_rad(45.0f), 800.f / 600.f, 0.1f, 100.f, projection);

        shader_bind_mat4(program, model, "model");
        shader_bind_mat4(program, *view, "view");
        shader_bind_mat4(program, projection, "projection");

        free(view);
        glBindVertexArray(vao);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
