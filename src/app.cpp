#include "GLEW/glew.h"
#include "GLFW/glfw3.h"
#include "util/util.h"
#include "callback/callback.h"
#include "util/Shader.h"
#include "image-reader/stb_image.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>
#include <string>
#include <cmath>
#include <thread>
#include <chrono>
int main(void)
{
    /**
     * Seting up for the window
     * Use the Glew for dynamically link the opengl
     */
    GLFWwindow* window;
    if (!glfwInit())
        return -1;
    window = glfwCreateWindow(800, 800, "OpenGl", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    if(glewInit() != GLEW_OK)
    {
        std:: cerr << "Error with GLEW\n";
    }
    glViewport(0,0,800,800);
    glfwSetFramebufferSizeCallback(window,&framebuffer_size_callback);
    /**
     * Hardware's specifications
     * Setting stb library to flip the image 
     */
    std:: cout << "Version: "<<glGetString(GL_VERSION)<<'\n';
    int n;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &n);
    std::cout << "Maximum nr of vertex attributes supported: " << n << '\n';
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS,&n);
    std::cout <<"Number of texture uints: " << n << '\n';
    stbi_set_flip_vertically_on_load(true); 


    /**
     * Use of glm
     */
    glm::vec4 vec(1.0f,0.0f,0.0f,1.0f);
    glm::mat4 trans(glm::mat4(1.0f));
    /*Build a translation vector to move (1,1,0)*/
    trans = glm::translate(trans,glm::vec3(1.0f,1.0f,0.0f));
    vec = trans * vec;
    std::cout << vec.x << " " << vec.y << " " << vec.z << '\n';

    /**
     * The loop for rendering
     */
    while (!glfwWindowShouldClose(window))
    {
        util::processInput(window);
        /* Render here */
        glClearColor(0.5f,0.5f,0.5f,0.1f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}