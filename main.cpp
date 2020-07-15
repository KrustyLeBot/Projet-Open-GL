#include "glad/glad.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "glm/glm.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "Callbacks.h"
#include "Camera/Camera.h"
#include "Objects/Object.h"
#include "Objects/ObjectSphere.h"
#include "Objects/ObjectCircle.h"
#include "Objects/ObjectRectangle.h"
#include "Objects/ObjectOBJ.h"

bool IMGUI_ON = true;
bool rotation = false;
GLfloat camPosStep = 0.1f;
GLfloat camRotStep = 10.0f;
GLfloat camPosX = 0.0f;
GLfloat camPosY = 0.0f;
GLfloat camPosZ = 0.0f;
GLfloat camRotX = 0.0f;
GLfloat camRotY = 0.0f;
GLfloat camRotZ = 0.0f;

int main(void)
{
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) exit(EXIT_FAILURE);
    window = glfwCreateWindow(1280, 1280, "Proto OpenGl", NULL, NULL);
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

    Camera camera = Camera();

    std::vector<Object> objectsVector;
    //objectsVector.push_back(ObjectSphere(0.5f, 0.5f, 0.9f, 0.2f, 30, 30, 0xf542e6, true));
    //objectsVector.push_back(ObjectSphere(0.0f, 0.0f, 0.2f, 0.1f, 30, 30, 0x30d13b, true));
    //objectsVector.push_back(ObjectCircle(0.0f, 0.0f, 99.9999f, 0.5f, 30, 0xf542e6, false));
    //objectsVector.push_back(ObjectCircle(-0.3f, 0.3f, 1.f, 0.5f, 30, 0xeb311c, false));
    //objectsVector.push_back(ObjectRectangle(-0.8f, -0.2f, -0.8f, 0.2f, -0.4f, 0.2f, -0.4f, -0.2f, 0.0f, 0xeb311c, 0xeb311c, 0xeb311c, 0xeb311c, false));
    //ObjectOBJ test = ObjectOBJ("test.obj", 0xeb311c, true); 
    //ObjectOBJ test = ObjectOBJ("char.obj", 0xeb311c, true);
    ObjectOBJ test = ObjectOBJ("bugatti.obj", 0xeb311c, true);
    test.setScale(0.1f, 0.1f, 0.1f);
    objectsVector.push_back(test);
    
    while (!glfwWindowShouldClose(window))
    {
        if (IMGUI_ON)
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            //////////////////////////////////////////
            // ImGui window definition
            ImGui::Checkbox("Checked -> Rotation, Unchecked -> Position", &rotation);
            ImGui::NewLine();
            ImGui::SliderFloat("Cam Slide Pos X", &camPosX, -2.0f, 2.0f);
            ImGui::SliderFloat("Cam Slide Pos Y", &camPosY, -2.0f, 2.0f);
            ImGui::SliderFloat("Cam Slide Pos Z", &camPosZ, -2.0f, 2.0f);
            ImGui::SliderFloat("Cam Slide Rot X", &camRotX, 0.0f, 360.0f);
            ImGui::SliderFloat("Cam Slide Rot Y", &camRotY, 0.0f, 360.0f);
            ImGui::SliderFloat("Cam Slide Rot Z", &camRotZ, 0.0f, 360.0f);
            //////////////////////////////////////////
        }
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float)height;
        glViewport(0, 0, width, height);
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        

        // Move camera
        camera.lookAt(camRotX, camRotY, camRotZ);
        camera.setPosition(camPosX, camPosY, camPosZ);

        // Draw all objects
        for (auto& object : objectsVector)
        {
            //object.setRotation((float)glfwGetTime() * 50, 0, 0);
            object.display();
        }

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

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

