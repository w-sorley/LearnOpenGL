#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 Position;

uniform samplerCube skybox;
uniform vec3 cameraPos;

void main()
{ 
    // 计算发射倒影
    // vec3 viewDir = normalize(Position - cameraPos);
    // vec3 reflectDir = reflect(viewDir, normalize(Normal)); 
    // vec4 textureColor  = texture(skybox, reflectDir);

    // 计算折射
    // float ratio = 1.0/1.52;
    // vec3 viewDir = normalize(Position - cameraPos);
    // vec3 refractDir = refract(viewDir, normalize(Normal), ratio);
    // vec4 textureColor  = texture(skybox, refractDir);
    // if (gl_FragCoord.x < 300)
    //     FragColor = vec4(1.0, 0.0, 0.0, 0.5);
    // else 
    //     FragColor = vec4(0.0, 1.0, 0.0, 0.5);
    if (gl_FrontFacing)
        FragColor = vec4(1.0, 0.0, 0.0, 0.5);
    else 
        FragColor = vec4(0.0, 1.0, 0.0, 0.5);
}
