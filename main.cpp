#include "glad/glad.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include <stdlib.h>
#include <stdio.h>
#include "callbacks.h"
#include "DrawForms.h"


int main(void)
{
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) exit(EXIT_FAILURE);
    window = glfwCreateWindow(640, 640, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    gladLoadGL();
    glfwSetKeyCallback(window, key_callback);
    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float)height;
        glViewport(0, 0, width, height);
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        glRotatef((float)glfwGetTime() * 10.f, (float)glfwGetTime() * 50.f, 0.f, 1.f);

        /*drawRectangle
        (
            -0.5f, -0.5f, 0.f,
            -0.5f, 0.5f, 0.f,
            0.5f, 0.5f, 0.f,
            0.5f, -0.5f, 0.f,

            0xf5aa42,
            0x42f545,
            0xf542e6,
            0x3840d9,
            true
        );*/

        drawSphere(0.0f, 0.0f, 0.0f, 0.5f, 200, 200, 0xf542e6, true);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
}
