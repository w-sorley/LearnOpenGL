#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TextureDir;

uniform mat4 projection;
uniform mat4 view;
void main() {
    vec4 pos = projection * view * vec4(aPos, 1.0);
    TextureDir = aPos;
    gl_Position  = pos.xyww; // z分量永远为最大值1.0
}