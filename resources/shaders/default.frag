#version 460 core

struct Material {
    vec4 color;
};

struct Light {
    vec3 position;
    vec4 color;
};

const int MAX_POINT_LIGHTS = 6;

uniform sampler2D textureObject;
uniform Material material;
uniform Light pointLights[MAX_POINT_LIGHTS];

in vec3 FragPos;
in vec3 Normal;
in vec2 textureCoordinates;

out vec4 FragColor;

void main() {
    vec3 norm = normalize(Normal);

    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * pointLights[0].color.xyz;

    vec3 lightDirection = normalize(pointLights[0].position - FragPos);
    vec3 diffuse = max(dot(norm, lightDirection), 0.0f) * pointLights[0].color.xyz;

    vec3 result = (ambient + diffuse) * material.color.xyz;

    FragColor = vec4(result, 1.0f) * texture(textureObject, textureCoordinates);
}
