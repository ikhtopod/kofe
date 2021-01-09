#version 460 core

uniform sampler2D firstTextureObject;
uniform sampler2D secondTextureObjects;

in vec2 textureCoordinates;

out vec4 FragColor;

void main() {
    FragColor = mix(texture(firstTextureObject, textureCoordinates), texture(secondTextureObjects, textureCoordinates), .2f);
}
