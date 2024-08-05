#include "GLEW/glew.h"
#include "GLFW/glfw3.h"
#include "util/util.h"
#include "callback/callback.h"
#include "util/Shader.h"
#include "image-reader/stb_image.h"

#include <iostream>
#include <string>
#include <cmath>
#include <thread>
#include <chrono>
int main(void)
{
    /**
     * Seting up for the window
     */
    GLFWwindow* window;
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    /* Create a windowed mode window and its OpenGL context */
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
     * Code for Opengl rendering
     */
    std:: cout << "Version: "<<glGetString(GL_VERSION)<<'\n';
    int n;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &n);
    std::cout << "Maximum nr of vertex attributes supported: " << n << '\n';


    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS,&n);
    std::cout <<"Number of texture uints: " << n << '\n';

    stbi_set_flip_vertically_on_load(true); 

    float text_vertices[]
    {
        /*   position   */ /*   colour    */  /*texture coor */
        0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
       -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
       -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f
    };


    GLuint text_indices[]
    {
        0, 1, 2,
        0, 3, 2
    };


    /**
     * Use of the new version of shader object
     */
    util::Shader s3{"../src/glsl/text_vertex_shader.glsl","../src/glsl/text_fragment_shader.glsl"};
    /**
     * Information for retangle for texture
     */
    GLuint text_vao;
    GLuint text_vbo;
    GLuint text_ebo;
    glGenVertexArrays(1,&text_vao);
    glGenBuffers(1,&text_vbo);
    glGenBuffers(1,&text_ebo);

    glBindVertexArray(text_vao);
    glBindBuffer(GL_ARRAY_BUFFER,text_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,text_ebo);

    glBufferData(GL_ARRAY_BUFFER,sizeof(text_vertices),text_vertices,GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(text_indices),text_indices,GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 3));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 6));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);
    

    /**
     * Load the texture and show the texture's information
     * Use of the texture
     */
    int w,h,nColourChannels;
    unsigned char* data {stbi_load("../textures/t0.jpg", &w, &h, &nColourChannels,0)};
    std::cout << "width: " << w << '\n';
    std::cout << "height: " << h << '\n';
    std::cout << "nColourChannels: " << nColourChannels << '\n';

    /* first texture*/
    GLuint texture;
    glGenTextures(1,&texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,w,h,0,GL_RGB,GL_UNSIGNED_BYTE,(void*)data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cerr << "Failed to load the texture\n";
        return -1;
    }


    /**Second texture */
    unsigned char* data_1 {stbi_load("../textures/t4.png", &w, &h, &nColourChannels,0)};
    std::cout << "width: " << w << '\n';
    std::cout << "height: " << h << '\n';
    std::cout << "nColourChannels: " << nColourChannels << '\n';

    GLuint texture_1;
    glGenTextures(1,&texture_1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D,texture_1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    if (data_1)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)data_1);
        glGenerateMipmap(GL_TEXTURE_2D);
    }


    unsigned char* data_2 {stbi_load("../textures/t2.png", &w, &h, &nColourChannels,0)};
    std::cout << "width: " << w << '\n';
    std::cout << "height: " << h << '\n';
    std::cout << "nColourChannels: " << nColourChannels << '\n';

    GLuint texture_2;
    glGenTextures(1,&texture_2);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D,texture_2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    if (data_2)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)data_2);
        glGenerateMipmap(GL_TEXTURE_2D);
    }


    unsigned char* data_3 {stbi_load("../textures/t3.png", &w, &h, &nColourChannels,0)};
    std::cout << "width: " << w << '\n';
    std::cout << "height: " << h << '\n';
    std::cout << "nColourChannels: " << nColourChannels << '\n';

    GLuint texture_3;
    glGenTextures(1,&texture_3);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D,texture_3);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    if (data_3)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)data_3);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    float mixVal {0.5f};

    while (!glfwWindowShouldClose(window))
    {
        util::processInput(window, mixVal);
        /* Render here */
        glClearColor(0.5f,0.5f,0.5f,0.1f);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(text_vao);
        s3.use();
        /**
         * To use the texture in the unit 0
         */
        s3.setInt("myTexture",2);
        s3.setInt("myTexture_1",3);
        s3.setFloat("mixVal",mixVal);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteTextures(1,&texture);
    glDeleteTextures(1,&texture_1);
    glDeleteTextures(1,&texture_2);
    glDeleteTextures(1,&texture_3);

    stbi_image_free(data);
    stbi_image_free(data_1);
    stbi_image_free(data_2);
    stbi_image_free(data_3);

    glDeleteBuffers(1,&text_vbo);
    glDeleteBuffers(1,&text_ebo);
    glDeleteVertexArrays(1,&text_vao);

    glfwTerminate();
    return 0;
}