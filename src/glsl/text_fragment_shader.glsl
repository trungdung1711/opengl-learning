#version 330 core

in vec4 vertexColour;
in vec2 texCoord;
out vec4 frCol;

uniform sampler2D myTexture;

void main()
{
    frCol = texture(myTexture,texCoord);
}