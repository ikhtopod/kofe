#version 460 core

struct Material {
    vec4 color;
};

uniform sampler2D textureObject;
uniform Material material;

in vec3 Normal;
in vec2 textureCoordinates;

out vec4 FragColor;

void main() {
    FragColor = material.color * texture(textureObject, textureCoordinates);
}
