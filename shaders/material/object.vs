#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 mNormal;

out vec3 worldPos;
out vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(position, 1.0f);
    worldPos = vec3(model * vec4(position, 1.0f));
    // 法线矩阵 = 模型矩阵左上角的逆矩阵的转置矩阵
    normal = mat3(transpose(inverse(model))) * mNormal;
}

