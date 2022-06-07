#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 mNormal;


out vec3 normal;
out vec3 fragPostion;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    normal = mat3(transpose(inverse(model))) * mNormal;
    fragPostion = vec3(model * vec4(position, 1.0f));
    gl_Position = projection * view * vec4(fragPostion, 1.0);
}