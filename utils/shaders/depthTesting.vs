#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

layout (std140) uniform Matrices   //uniform 缓冲对象，名称为Matrices
{
  mat4 view;
  mat4 projection;
};
uniform mat4 model;


void main()
{  
    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
}