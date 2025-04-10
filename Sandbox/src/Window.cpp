#include "Window.h"

#include "GLFW/glfw3.h"

auto InitializeGLFW() -> GLFWwindow*
{
    // Initialize the GLFW library.
    if (glfwInit() == GLFW_FALSE)
        return nullptr;

    // Set hints for the next call to glfwCreateWindow.

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    if (glfwGetError(nullptr) != GLFW_NO_ERROR)
    {
        glfwTerminate();
        return nullptr;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    if (glfwGetError(nullptr) != GLFW_NO_ERROR)
    {
        glfwTerminate();
        return nullptr;
    }

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if (glfwGetError(nullptr) != GLFW_NO_ERROR)
    {
        glfwTerminate();
        return nullptr;
    }

    // Create a window and its associated OpenGL context.
    auto pWindow = glfwCreateWindow(800, 600, "Graphics Engine Sandbox", NULL, NULL);
    if (!pWindow)
    {
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(pWindow);
    if (glfwGetError(nullptr) != GLFW_NO_ERROR)
    {
        glfwDestroyWindow(pWindow);
        glfwTerminate();
        return nullptr;
    }

    glfwSwapInterval(1);
    if (glfwGetError(nullptr) != GLFW_NO_ERROR)
    {
        glfwDestroyWindow(pWindow);
        glfwTerminate();
        return nullptr;
    }

    glfwSetFramebufferSizeCallback(pWindow, OnFramebufferSize);

    return pWindow;
}

auto OnFramebufferSize(GLFWwindow* /*window*/, int /*width*/, int /*height*/) -> void
{
    // TODO: make the graphics engine do this!
    // glViewport(0, 0, width, height);
}

auto TerminateGLFW(GLFWwindow* pWindow) -> void
{
    if (pWindow)
        glfwDestroyWindow(pWindow);

    glfwTerminate();
}
