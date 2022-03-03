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
#include "pane.h"
#include "block.h"
#include "line.h"
#include "math.h"

int main(void)
{
    GLFWwindow* window = initialize_window();
    
    int program = shader_create("line.fragment");

    Camera* cam = camera_create();
    vec3 cam_pos = {0.f, 1.f, -5.f};
    glm_vec3_copy(cam_pos, cam->pos);

    //Pane* pane = pane_create();
    //Block* block = block_create();

    vec3 start = {-1.f, -1.f, -1.f};
    vec3 end = {1.f, 1.f, 1.f};

    Line* line = line_create(&start, &end);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(program);

        mat4* view = camera_view(cam);
        vec3 up = {0, 1.f, 0};
        glm_rotate(*view, (float)glfwGetTime() * glm_rad(90.f), up);

        mat4 projection;
        glm_perspective(glm_rad(45.0f), 800.f / 600.f, 0.1f, 100.f, projection);

        shader_bind_mat4(program, *view, "view");
        shader_bind_mat4(program, projection, "projection");
        shader_bind_float(program, (float)glfwGetTime(), "time");
        free(view);

        //pane_render(pane, program);
        //block_render(block, program);

        line_render(line, program);

        GLenum err;
        while((err = glGetError()) != GL_NO_ERROR) {
            printf("Error: %d\n", err);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    free(cam);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
