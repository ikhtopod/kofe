#version 460 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct PointLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

const int MAX_POINT_LIGHTS = 6;

uniform Material material;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform vec3 cameraPosition;

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

void main() {
    const vec3 NORM = normalize(Normal);

    vec3 result = vec3(0.0f);

    for (int i = 0; i < MAX_POINT_LIGHTS; i++) {
        PointLight pointLight = pointLights[i];

        vec3 ambient = pointLight.ambient * material.ambient;

        vec3 lightDirection = normalize(pointLight.position - FragPos);
        float diff = max(dot(NORM, lightDirection), 0.0f);
        vec3 diffuse = pointLight.diffuse * (diff * material.diffuse);

        vec3 viewDirection = normalize(cameraPosition - FragPos);
        // Reflection vector along the normal axis
        vec3 reflectDirection = reflect(-lightDirection, NORM);
        float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
        vec3 specular = pointLight.specular * (spec * material.specular);

        result += ambient + diffuse + specular;
    }

    FragColor = vec4(result, 1.0f);
}
