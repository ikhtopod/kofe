#version 460 core

struct MVP {
    mat4 model;
    mat4 view;
    mat4 projection;
};

const uint ATTRIB_POSITION = 0;
const uint ATTRIB_NORMAL = 1;
const uint ATTRIB_TEXTURE = 2;

layout (location = ATTRIB_POSITION) in vec3 aPosition;
layout (location = ATTRIB_NORMAL) in vec3 aNormal;
layout (location = ATTRIB_TEXTURE) in vec2 aTexture;

uniform MVP mvp;
uniform mat4 transform;

out vec3 FragPos;
out vec3 Normal;

void main() {
    gl_Position = mvp.projection * mvp.view * mvp.model * transform * vec4(aPosition.xyz, 1.0f);
    FragPos = vec3(mvp.model * transform * vec4(aPosition.xyz, 1.0f));
    // Adjust aNormal to the transformed aPosition
    Normal = mat3(transpose(inverse(mvp.model * transform))) * aNormal;
}
