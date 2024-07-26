#version 330 core

in vec4 vertexColour;
out vec4 frCol;

void main()
{
    frCol = vec4(vertexColour);
}