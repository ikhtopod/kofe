#version 460 core

struct MVP {
    mat4 model;
    mat4 view;
    mat4 projection;
};

const uint ATTRIB_POSITION = 0;
const uint ATTRIB_TEXTURE = 1;

layout (location = ATTRIB_POSITION) in vec3 aPos;
layout (location = ATTRIB_TEXTURE) in vec2 aTexture;

uniform MVP mvp;
uniform mat4 transform;

out vec2 textureCoordinates;

void main() {
    gl_Position = mvp.projection * mvp.view * mvp.model * transform * vec4(aPos.xyz, 1.f);
    textureCoordinates = aTexture;
}
