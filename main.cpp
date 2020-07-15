#include "glad/glad.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "Callbacks.h"

#include "Objects/Object.h"
#include "Objects/ObjectSphere.h"
#include "Objects/ObjectCircle.h"
#include "Objects/ObjectRectangle.h"

bool IMGUI_ON;

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

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
    ImGui::StyleColorsDark();
    IMGUI_ON = true;

    float rotationX = 0.0f;
    float rotationY = 0.0f;
    float rotationZ = 0.0f;

    float speedX = 0.0f;
    bool autoRotationX = false;

    float speedY = 0.0f;
    bool autoRotationY = false;

    float speedZ = 0.0f;
    bool autoRotationZ = false;

    std::vector<Object> objectsVector;
    objectsVector.push_back(ObjectSphere(0.5f, 0.5f, 0.0f, 0.5f, 30, 30, 0xf542e6, true));
    objectsVector.push_back(ObjectSphere(-1.0f, -1.2f, 0.0f, 0.5f, 30, 30, 0xf542e6, true));
    //objectsVector.push_back(ObjectCircle(0.0f, 0.0f, 0.0f, 0.5f, 30, 0xf542e6, true));
    //objectsVector.push_back(ObjectRectangle(-0.8f, -0.2f, -0.8f, 0.2f, -0.4f, 0.2f, -0.4f, -0.2f, 0.0f, 0xf542e6, 0xf542e6, 0xf542e6, 0xf542e6, false));
    //objectsVector.push_back(ObjectRectangle(-0.8f, -0.2f, -0.8f, 0.2f, -0.4f, 0.2f, -0.4f, -0.2f, 0.0f, 0xeb311c, 0xeb311c, 0xeb311c, 0xeb311c, false));
    

    while (!glfwWindowShouldClose(window))
    {
        if (IMGUI_ON)
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            //////////////////////////////////////////
            // ImGui window definition
            ImGui::Checkbox("Auto Rotation X", &autoRotationX);
            ImGui::SameLine();
            ImGui::SliderFloat("Auto Rotation Speed X", &speedX, 0.0f, 1000.0f);

            ImGui::Checkbox("Auto Rotation Y", &autoRotationY);
            ImGui::SameLine();
            ImGui::SliderFloat("Auto Rotation Speed Y", &speedY, 0.0f, 1000.0f);

            ImGui::Checkbox("Auto Rotation Z", &autoRotationZ);
            ImGui::SameLine();
            ImGui::SliderFloat("Auto Rotation Speed Z", &speedZ, 0.0f, 1000.0f);

            ImGui::NewLine();

            ImGui::SliderFloat("Manual Rotation X", &rotationX, 0.0f, 360.0f);
            ImGui::SliderFloat("Manual Rotation Y", &rotationY, 0.0f, 360.0f);
            ImGui::SliderFloat("Manual Rotation Z", &rotationZ, 0.0f, 360.0f);
            //////////////////////////////////////////
        }
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

        /*if (autoRotationX)
        {
            glRotatef((float)glfwGetTime() * speedX, 1.0f, 0.0f, 0.0f);
        }
        if(autoRotationY)
        {
            glRotatef((float)glfwGetTime() * speedY, 0.0f, 1.0f, 0.0f);
        }
        if (autoRotationZ)
        {
            glRotatef((float)glfwGetTime() * speedZ, 0.0f, 0.0f, 1.0f);
        }

        if(!(autoRotationX || autoRotationY || autoRotationZ))
        {
            glRotatef(rotationX, 1.0f, 0.0f, 0.0f);
            glRotatef(rotationY, 0.0f, 1.0f, 0.0f);
            glRotatef(rotationZ, 0.0f, 0.0f, 1.0f);
        }*/
        
        for (auto& object : objectsVector)
        {
            //object.setRotation(0, 0, (float)glfwGetTime() * 50);
            object.display();
        }

        if (IMGUI_ON)
        {
            // Render ImGui
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
}