#version 330 core
out vec4 FragColor;

uniform samplerCube skybox;
uniform vec3 cameraPos;

void main()
{ 
    // 计算折射
    FragColor = vec4(1.0, 0.0, 0.0, 1.0);

}
