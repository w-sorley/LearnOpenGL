#version 330 core

out vec4 FragColor;
in vec3 TexColor;

void main()
{
    FragColor = vec4(TexColor, 0.8);
}