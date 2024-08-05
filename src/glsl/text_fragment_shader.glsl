#version 330 core

in vec4 vertexColour;
in vec2 texCoord;
out vec4 frCol;

uniform sampler2D myTexture;
uniform sampler2D myTexture_1;
uniform float mixVal;

void main()
{
    frCol = mix (texture(myTexture,texCoord),texture(myTexture_1,texCoord),mixVal);
}