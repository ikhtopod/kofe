#version 460 core

const uint ATTRIB_POSITION = 0;
const uint ATTRIB_TEXTURE = 1;

layout (location = ATTRIB_POSITION) in vec3 aPos;
layout (location = ATTRIB_TEXTURE) in vec2 aTexture;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 textureCoordinates;

void main() {
    gl_Position = projection * view * model * vec4(aPos.xyz, 1.f);
    textureCoordinates = aTexture;
}
