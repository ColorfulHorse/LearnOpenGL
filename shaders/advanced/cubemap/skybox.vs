#version 330 core
layout(location = 0) in vec3 position;

out vec3 texCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    texCoords = position;
    vec4 pos = projection * view * model * vec4(position, 1.0f);
    // 让z和w永远为1.0，保证片段在所有片段后面
    gl_Position = pos.xyww;
}