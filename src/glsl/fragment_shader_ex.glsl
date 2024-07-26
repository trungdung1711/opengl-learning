#version 330 core

in vec4 my_col;
out vec4 frCol;

void main()
{
    frCol = vec4(my_col);
}