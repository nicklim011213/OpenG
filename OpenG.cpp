// OpenG1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <glad.h> 
#include <glfw3.h>
#include <iostream>
#include <errno.h>
#include <climits>
#include "ProjectFileHandler.h"
#include "Renderer.h"
#include "WorldData.h"

struct WindowSettings
{
    long WinX = 1920;
    long WinY = 1080;
    std::string WinTitle = "OpenG";
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void ValidateOptions(int argc, char* argv[], WindowSettings* WinSettings)
{
    if (argc == 2)
    {
        std::cout << "Default to 1920X1080 Assuming Argument is Title\n";
        WinSettings->WinTitle = argv[1];
    }
    else if (argc == 4)
    {
        long XArg = strtol(argv[1], nullptr, 10);
        if (errno != 0 || XArg > 1920 || XArg < 1)
        {
            XArg = 1920;
            errno = 0;
            std::cerr << "Width is invalid reverting to 1920 (Non-Fatal)\n";
        }
        WinSettings->WinX = XArg;

        long YArg = strtol(argv[2], nullptr, 10);
        if (errno != 0 || YArg > 1080 || YArg < 1)
        {
            YArg = 1080;
            errno = 0;
            std::cerr << "Height is invalid reverting to 1080 (Non-Fatal)\n";
        }
        WinSettings->WinY = YArg;

        WinSettings->WinTitle = argv[3];
    }
    else
    {
        std::cerr << "No Args or Invalid Args... Reverting to default 1920 X 1080 (Non-Fatal)\n";
    }
}

GLFWwindow* BuildWindow(WindowSettings* WinSettings)
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WinSettings->WinX, WinSettings->WinY, WinSettings->WinTitle.c_str(), NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glViewport(0, 0, WinSettings->WinX, WinSettings->WinY);

    return window;
}

int main(int argc, char* argv[])
{
    WindowSettings WinSettings;
    ValidateOptions(argc, argv, &WinSettings);
    GLFWwindow* window = BuildWindow(&WinSettings);

    // Create an item add it to a collection of items
    CompleteItem ExampleItem("MyItem1", { 0, 1, 0 });
    ItemCollection ItemCollection;
    ItemCollection.ItemList.push_back(ExampleItem);
    ItemCollection.DisplayItemList();

    json j{ExampleItem.UniqueID, ExampleItem.VertexIndex, ExampleItem.VertexList};
    std::ofstream Output("Out.json");
    Output << j;
    Output.close();

    Renderer Rendererinstance;

    Rendererinstance.RenderSetup(ItemCollection);

    while (!glfwWindowShouldClose(window))
    {
        Rendererinstance.RenderLoop(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return EXIT_SUCCESS;
}