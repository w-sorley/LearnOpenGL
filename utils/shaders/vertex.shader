#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
out vec3 Normal;
out vec3 objectPos;

uniform mat4 model;
void main()
{
    gl_Position = model * vec4(aPos, 1.0);
    Normal = aNormal;
    objectPos = vec3(model * vec4(aPos, 1.0));
}