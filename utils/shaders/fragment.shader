#version 330 core

out vec4 FragColor;
in vec3 Normal;
in vec3 objectPos;

uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - objectPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3  diffuse = diff * lightColor;

    float specularStrength = 0.8;
    vec3 viewDir = normalize(viewPos - objectPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 132);
    vec3 specular = spec * specularStrength * lightColor;


    vec3 result = (diffuse + ambient + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}