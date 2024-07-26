#include "util/util.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
void util::processInput(GLFWwindow * window)
{
    if (glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window,true);
    }
}