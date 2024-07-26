#include "GLEW/glew.h"
#include "GLFW/glfw3.h"
#include "util/util.h"
#include "callback/callback.h"
#include "util/Shader.h"
#include "image-reader/stb_image.h"

#include <iostream>
#include <string>
#include <cmath>
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
    window = glfwCreateWindow(800, 800, "My first OpenGl", NULL, NULL);
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
    
    
    float vertices_reg[]
    {
         0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
         0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f
    };


    GLuint indices[]
    {
        0,1,3,
        1,2,3
    };


    float vertices_ex[]
    {
        0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
       -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    };


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
    util::Shader s1{"D:/trungdung/C++/OpenGL/src/glsl/vertex_shader.glsl","D:/trungdung/C++/OpenGL/src/glsl/fragment_shader.glsl"};
    util::Shader s2{"D:/trungdung/C++/OpenGL/src/glsl/vertex_shader_ex.glsl","D:/trungdung/C++/OpenGL/src/glsl/fragment_shader_ex.glsl"};
    util::Shader s3{"../src/glsl/text_vertex_shader.glsl","../src/glsl/text_fragment_shader.glsl"};
    /**
     * Tell openGL how to interpret the vertex data using attribute pointer
     * Enable the vertex attribute to get the arguments
     * Ready for the graphics pipeline
     */


    /**
     * Use VAO to remember all the settings of VBO
     * Generate a VAO
     * Bind the VAO to the openGL context
     * Also give openGL, VAO how to interpret the vertex data
     * Every configuring of the VBO -> stored inside the VAO for later use
     */
    // GLuint VAO;
    // glGenVertexArrays(1,&VAO);
    // glBindVertexArray(VAO);
    // /**
    //  * Get the ID for the VBO
    //  * Return the ID for this buffer
    //  * Bind this buffer with the GL_ARRAY_BUFFER
    //  * Transmit the data to the GPU's memory
    //  */
    // unsigned int VBO;
    // glGenBuffers(1,&VBO);
    // glBindBuffer(GL_ARRAY_BUFFER,VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices,GL_STATIC_DRAW);
    // glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(float)*3,(void*)0);
    // glEnableVertexAttribArray(0);

    // glBindVertexArray(0);

    // GLuint vao[2];
    // glGenVertexArrays(2,vao);

    // GLuint vbo[2];
    // glGenBuffers(2,vbo);

    // glBindVertexArray(vao[0]);

    // glBindBuffer(GL_ARRAY_BUFFER,vbo[0]);
    // glBufferData(GL_ARRAY_BUFFER,sizeof(vertices_A),vertices_A,GL_STATIC_DRAW);
    // glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(float)*3,(void*)0);
    // glEnableVertexAttribArray(0);

    // glBindVertexArray(0);

    // glBindVertexArray(vao[1]);

    // glBindBuffer(GL_ARRAY_BUFFER,vbo[1]);
    // glBufferData(GL_ARRAY_BUFFER,sizeof(vertices_B),vertices_B,GL_STATIC_DRAW);
    // glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(float)*3,(void*)0);
    // glEnableVertexAttribArray(0);

    // glBindVertexArray(0);

    GLuint new_vao;
    glGenVertexArrays(1,&new_vao);
    glBindVertexArray(new_vao);
    /**
     * vertex buffer object
     */
    GLuint new_vbo;
    glGenBuffers(1,&new_vbo);
    /**
     * element buffer object
     */
    GLuint ebo;
    glGenBuffers(1,&ebo);

    glBindBuffer(GL_ARRAY_BUFFER,new_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);

    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices_reg),vertices_reg,GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

    /*Configure how shader extract the data from VBO*/
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6 * sizeof(float),(void*)0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6 * sizeof(float),(void*)(sizeof(float) * 3));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    
    /**
     * exercises
     */
    GLuint ex_vao;
    glGenVertexArrays(1,&ex_vao);
    GLuint ex_vbo;
    glGenBuffers(1,&ex_vbo);

    glBindVertexArray(ex_vao);
    glBindBuffer(GL_ARRAY_BUFFER,ex_vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices_ex),vertices_ex,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,false,6 * sizeof(float),(void*)0);
    glVertexAttribPointer(1,3,GL_FLOAT,false,6 * sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);


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
    unsigned char* data {stbi_load("../textures/t1.jpg", &w, &h, &nColourChannels,0)};
    std::cout << "width: " << w << '\n';
    std::cout << "height: " << h << '\n';
    std::cout << "nColourChannels: " << nColourChannels << '\n';

    GLuint texture;
    glGenTextures(1,&texture);
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
    glBindTexture(GL_TEXTURE_2D, 0);


    /**Second texture */
    unsigned char* data_1 {stbi_load("../textures/t2.png", &w, &h, &nColourChannels,0)};
    std::cout << "width: " << w << '\n';
    std::cout << "height: " << h << '\n';
    std::cout << "nColourChannels: " << nColourChannels << '\n';

    GLuint texture_1;
    glGenTextures(1,&texture_1);
    glBindTexture(GL_TEXTURE_2D,texture_1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    if (data_1)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, (void*)data_1);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    glBindTexture(GL_TEXTURE_2D, 0);

    while (!glfwWindowShouldClose(window))
    {
        util::processInput(window);
        /* Render here */
        glClearColor(0.5f,0.5f,0.5f,0.1f);
        glClear(GL_COLOR_BUFFER_BIT);

        // float time = glfwGetTime();
        // float red = (std:: sin(time) + 1) / 2;
        // GLint location = glGetUniformLocation(shaderProgram,"ourColour");
        /**
         * Only changed when the shader is active
         * Set the active program
         * Changed the value of the uniform variable
         */
        //glUseProgram(shaderProgram);
        // glUniform4f(location,red,0.0f,0.0f,1.0f);
        //float time = glfwGetTime();
        //float value = std::sin(time)*1/2;
        //s2.use();
        //s2.setFloat("x_off",value);
        //s2.setFloat("y_off",value);
        glBindVertexArray(text_vao);
        s3.use();
        glBindTexture(GL_TEXTURE_2D, texture);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // glUseProgram(shaderProgram);
        // glBindVertexArray(vao[0]);
        // glDrawArrays(GL_TRIANGLES,0,3);


        // glBindVertexArray(vao[1]);
        // glDrawArrays(GL_TRIANGLES,0,3);
        /* Poll for and process events */

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(1,&new_vbo);
    glDeleteBuffers(1,&ebo);
    glDeleteVertexArrays(1,&new_vao);

    glDeleteBuffers(1,&ex_vbo);
    glDeleteVertexArrays(1,&ex_vao);

    glDeleteTextures(1,&texture);

    stbi_image_free(data);

    glfwTerminate();
    return 0;
}