#include "util/util.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
void util::processInput(GLFWwindow * window, float& mixVal)
{
    if (glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window,true);
    }


    if (glfwGetKey(window,GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        mixVal+=0.0001f;
        if (mixVal >= 1.0f)
            mixVal = 1.0f;
    }


    if (glfwGetKey(window,GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        mixVal-=0.0001f;
        if (mixVal <= 0.0f)
            mixVal = 0.0f;
    }
}