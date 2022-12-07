#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aTexCoord;
out vec3 TexColor;

uniform mat4 model;
uniform vec3 lightColor;
void main()
{
    gl_Position = model * vec4(aPos, 1.0);
TexColor = lightColor;
}