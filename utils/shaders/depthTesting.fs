#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture1;


float near = 0.1; 
float far  = 100.0;
float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));    
}

void main()
{ 
    //    FragColor = vec4(vec3(gl_FragCoord.z), 1.0);
    FragColor = texture(texture1, TexCoords);
    // FragColor = vec4(vec3(pow(gl_FragCoord.z, 20)), 1.0); // 不使用pow函数会看起来全白
    // float depth = LinearizeDepth(gl_FragCoord.z) / far; // 为了演示除以 far
    // FragColor = vec4(vec3(depth), 1.0);

}
