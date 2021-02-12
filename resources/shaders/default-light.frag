#version 460 core

struct Material {
    vec4 color;
};

uniform Material material;

out vec4 FragColor;

void main() {
    FragColor = material.color;
}
