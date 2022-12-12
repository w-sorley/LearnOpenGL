#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;
    // vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

out vec4 FragColor;
in vec3 Normal;
in vec3 objectPos;
in vec2 TexCoords;

uniform vec3 objectColor;
uniform vec3 viewPos;
uniform Material material;
uniform Light light;
void main()
{
    // 环境光
    vec3 ambient = vec3(texture(material.diffuse, TexCoords)) * light.ambient;

    // 漫反射
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - objectPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3  diffuse = light.diffuse * (diff * vec3(texture(material.diffuse, TexCoords)));

    // 镜面反射
    vec3 viewDir = normalize(viewPos - objectPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * vec3(texture(material.specular, TexCoords)));

    // 衰减
    float distance = length(light.position - objectPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    diffuse *= attenuation;
    ambient *= attenuation;
    specular *= attenuation;

    vec3 result = diffuse + ambient + specular;
    FragColor = vec4(result, 1.0);
}