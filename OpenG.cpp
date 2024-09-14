// OpenG1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <glad.h> 
#include <glfw3.h>
#include <iostream>
#include <errno.h>
#include <climits>


struct WindowSettings
{
    unsigned int WinX = 1920;
    unsigned int WinY = 1080;
    std::string WinTitle = "OpenG";
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main(int argc, char* argv[])
{
    WindowSettings WinSettings;
    if (argc == 2)
    {
        std::cout << "Default to 1920X1080 Assuming Argument is Title\n";   
        WinSettings.WinTitle = argv[1];
    }
    else if (argc == 4)
    {
        unsigned int XArg = strtol(argv[1], nullptr, 10);
        if (errno != 0 || XArg > 1920)
        {
            XArg = 1920;
            errno = 0;
        }
        WinSettings.WinX = XArg;

        unsigned int YArg = strtol(argv[2], nullptr, 10);
        if (errno != 0 || YArg > 1080)
        {
            YArg = 1080;
            errno = 0;
        }
        WinSettings.WinY = YArg;

        WinSettings.WinTitle = argv[3];
    }
    else
    {
        std::cout << "No Args or Invalid Args... Reverting to default\n";
    }


    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WinSettings.WinX, WinSettings.WinY, WinSettings.WinTitle.c_str(), NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glViewport(0, 0, WinSettings.WinX, WinSettings.WinY);

    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}