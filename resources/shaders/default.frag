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
uniform vec3 cameraPosition;

in vec3 FragPos;
in vec3 Normal;
in vec2 textureCoordinates;

out vec4 FragColor;

void main() {
    vec3 norm = normalize(Normal);

    vec3 result = vec3(0.0f);

    for (int i = 0; i < MAX_POINT_LIGHTS; i++) {
        Light pointLight = pointLights[i];

        float ambientStrength = 0.1f;
        vec3 ambient = ambientStrength * pointLight.color.xyz;

        vec3 lightDirection = normalize(pointLight.position - FragPos);
        vec3 diffuse = max(dot(norm, lightDirection), 0.0f) * pointLight.color.xyz;

        float specularStrength = 0.5f;
        float specularShininess = 32.0f;
        vec3 viewDirection = normalize(cameraPosition - FragPos);
        // Reflection vector along the normal axis
        vec3 reflectDirection = reflect(-lightDirection, norm);
        float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), specularShininess);
        vec3 specular = specularStrength * spec * pointLight.color.xyz;

        result += ambient + diffuse + specular;
    }

    result *= material.color.xyz;

    FragColor = vec4(result, 1.0f) * texture(textureObject, textureCoordinates);
}
