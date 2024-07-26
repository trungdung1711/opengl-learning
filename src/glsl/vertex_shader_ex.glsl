#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;

out vec4 my_col;

uniform float x_off;

void main()
{
    gl_Position = vec4(aPos.x + x_off,aPos.y,aPos.z,1.0);
    my_col = vec4(aCol,1.0);
}
