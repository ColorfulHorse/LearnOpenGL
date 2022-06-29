#version 330 core
layout(location = 0) in vec3 mPosition;
layout(location = 2) in vec2 mTexCoord;
layout(location = 3) in mat4 mModel;

out vec2 texCoord;

uniform mat4 view;
uniform mat4 projection;

void main() {
    texCoord = mTexCoord;
    gl_Position = projection * view * mModel * vec4(mPosition, 1.0);
}