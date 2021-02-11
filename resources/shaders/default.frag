#version 460 core

struct Material {
    vec4 objectColor;
};

uniform sampler2D textureObject;
uniform Material material;

in vec2 textureCoordinates;

out vec4 FragColor;

void main() {
    FragColor = material.objectColor * texture(textureObject, textureCoordinates);
}
