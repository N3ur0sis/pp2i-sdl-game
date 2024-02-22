#version 330 core
out vec4 FragColor;

in vec3 colorOut;

void main()
{
   FragColor = vec4(colorOut, 1.0f);
}