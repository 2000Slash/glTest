#include "window.h"

GLFWwindow *initialize_window()
{
    /* Initialize the library */
    if (!glfwInit())
        return NULL;

    GLFWwindow *window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return NULL;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD");
        return NULL;
    }

    glViewport(0, 0, 800, 600);
    glEnable(GL_DEPTH_TEST);
    return window;
}
