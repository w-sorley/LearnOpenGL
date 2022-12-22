#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out V_OUT {
  vec3 Normal;
  vec3 Position;
} vs_out;


layout (std140) uniform Matrices   //uniform 缓冲对象，名称为Matrices
{
  mat4 view;
  mat4 projection;
};
uniform mat4 model;


void main()
{   vs_out.Normal = mat3(transpose(inverse(model))) * aNormal;
    vs_out.Position = vec3(model * vec4(aPos, 1.0));
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    gl_PointSize = gl_Position.z * 100;

}