#version 330 core
layout(location = 0) in vec3 mPosition;
layout(location = 2) in vec2 mTexCoord;

out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    texCoord = mTexCoord;
    gl_Position = projection * view * model * vec4(mPosition, 1.0);
}