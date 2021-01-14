#version 460 core

uniform sampler2D textureObject;

in vec2 textureCoordinates;

out vec4 FragColor;

void main() {
    FragColor = texture(textureObject, textureCoordinates);
}
