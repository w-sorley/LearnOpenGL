#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_difffuse1;
uniform sampler2D texture_specular1;

void main()
{    
    FragColor =  texture(texture_difffuse1, TexCoords) + texture(texture_specular1, TexCoords);
    // FragColor = vec4(1.0, 0.0, 0.0, 0.8);
}