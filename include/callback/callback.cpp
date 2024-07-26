#include "GLFW/glfw3.h"
#include "callback/callback.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  